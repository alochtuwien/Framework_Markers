//
// Created by aloch on 19.12.22.
//

#include "../../include/utils/visualization.hpp"

VisualizationController::VisualizationController(int width_new, int height_new) {
    width = width_new;
    height = height_new;

    ui_ptr = new Metavision::MTWindow("Active markers", width, height*2, Metavision::Window::RenderMode::BGR);
//    prod = new VisualizationProducer(width, height);
    ui_ptr->set_keyboard_callback([this](Metavision::UIKeyEvent key, int scancode, Metavision::UIAction action, int mods) {
        if (action == Metavision::UIAction::RELEASE && key == Metavision::UIKeyEvent::KEY_ESCAPE){
            to_close = true;
            return;
        }
        if (action == Metavision::UIAction::RELEASE && key == Metavision::UIKeyEvent::KEY_P){
            std::cout << "PAUSE" << std::endl;
            return;
        }

    });
    img = cv::Mat::zeros(height, width, CV_8UC1);
    output = cv::Mat::zeros(height, width, CV_8UC3);

    counts = cv::Mat::zeros(height, width, CV_8UC1);

    to_close = false;
    closed = false;

    period = (long long)1000000 / fps;
    accumulation_period = (long long)1000000 / accumulation_fps;
    cutoff = min_freq / accumulation_period;

}

[[noreturn]] void VisualizationController::runtimeLoop() {
    int i = 0;
    bool to_check = false;
    while(!to_close.load()){

        if (buffers.getBatch()){
            if (next_output_required_at == 0){
                next_output_required_at = buffers.current_batch.first->front()->t + period;
                std::cout << "First ts " << next_output_required_at << std::endl;
            }
            if (next_output_required_at < buffers.current_batch.first->back()->t){
                to_check = true;
            }

            if (buffers.current_batch.first->back()->t > (next_output_required_at - accumulation_period))
            {
                for (const Metavision::Event2d* ev : *buffers.current_batch.first) {
                    if (ev->t > (next_output_required_at - accumulation_period)) {
                        img.at<uint8_t>(ev->y, ev->x) = 255;
                        counts.at<uint8_t>(ev->y, ev->x) += 1;
                        if (ev->t > next_output_required_at) {
                            next_output_required_at += period;


                            cv::SimpleBlobDetector::Params params;

                            params.filterByArea = true;
                            params.minArea = 5;
                            params.minDistBetweenBlobs = 1;
                            params.filterByCircularity = false;
                            params.filterByColor = false;
                            params.filterByConvexity = false;
                            params.filterByInertia = false;

                            cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);


                            std::vector<cv::KeyPoint> keypoints;


                            auto start = std::chrono::high_resolution_clock::now();

                            cv::threshold(counts, counts,  cutoff, 255,  cv::THRESH_BINARY);
                            detector->detect(counts, keypoints);

                            auto stop = std::chrono::high_resolution_clock::now();
                            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
                            std::cout << "Time taken by function: "
                                 << duration.count() << " microseconds" << std::endl;

                            getOutput();

                            cv::drawKeypoints(counts, keypoints, counts, cv::Scalar(0,0,255));
                            cv::Mat matF;
                            matF.push_back(output);
                            matF.push_back(counts);
                            ui_ptr->show_async(matF);
                            Metavision::EventLoop::poll_and_dispatch();

                            resetState();
                        }

                    }
                }
            }
        }
        else {
            ui_ptr->set_close_flag();
            closed = true;
            to_close = true;
        }
    }
    ui_ptr->set_close_flag();
    usleep(100);
    closed = true;

}

void VisualizationController::start() {
    if(buffers.input_buffer != nullptr){
        thread_ptr = new boost::thread(&VisualizationController::runtimeLoop, this);
    }
}


void VisualizationController::getOutput() {
    cv::cvtColor(img, output, cv::COLOR_GRAY2BGR);
//    cv::normalize(counts, counts, 0, 255, cv::NORM_MINMAX);
    cv::cvtColor(counts, counts, cv::COLOR_GRAY2BGR);

}

void VisualizationController::resetState(){
    img = cv::Mat::zeros(height, width, CV_8UC1);
    output = cv::Mat::zeros(height, width, CV_8UC3);
    counts = cv::Mat::zeros(height, width, CV_8UC1);
}

bool VisualizationController::isFinished() {
    return closed.load();
}




