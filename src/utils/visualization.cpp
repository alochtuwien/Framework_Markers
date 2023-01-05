//
// Created by aloch on 19.12.22.
//

#include "../../include/utils/visualization.hpp"

VisualizationController::VisualizationController(int width_new, int height_new) {
    width = width_new;
    height = height_new;

    ui_ptr = new Metavision::MTWindow("Active markers", width, height, Metavision::Window::RenderMode::BGR);
//    prod = new VisualizationProducer(width, height);
    ui_ptr->set_keyboard_callback(dummyCallback);
    img = cv::Mat::zeros(height, width, CV_8UC1);
    output = cv::Mat::zeros(height, width, CV_8UC3);


    period = (long long)1000000 / fps;

}

[[noreturn]] void VisualizationController::runtimeLoop() {
    int i = 0;
    bool to_check = false;
    while(true){

        buffers.getBatch();
        if (next_output_required_at == 0){
            next_output_required_at = buffers.current_batch.first->front()->t + period;
            std::cout << "First ts " << next_output_required_at << std::endl;
        }
        if (next_output_required_at < buffers.current_batch.first->back()->t){
            to_check = true;
        }

        for (const Metavision::Event2d* ev : *buffers.current_batch.first){
            img.at<uint8_t>(ev->y, ev->x) += 1;
            if (to_check){
                if (ev->t > next_output_required_at){
                    next_output_required_at += period;
                    to_check=false;
                    getOutput();
                    ui_ptr->show_async(output);
                    resetState();
                }
            }
        }
    }
}

void VisualizationController::start() {
    if(buffers.input_buffer != nullptr){
        thread_ptr = new boost::thread(&VisualizationController::runtimeLoop, this);
    }
}

void VisualizationController::dummyCallback(Metavision::UIKeyEvent key,
                                            int flag,
                                            Metavision::UIAction action,
                                            int flag1) {
    std::cout << "Pressed key" << std::flush;
}

cv::Mat VisualizationController::getOutput() {
    cv::cvtColor(img, output, cv::COLOR_GRAY2BGR);
}

void VisualizationController::resetState(){
    img = cv::Mat::zeros(height, width, CV_8UC1);
    output = cv::Mat::zeros(height, width, CV_8UC3);
}



