//
// Created by aloch on 05.01.23.
//

#include "../include/detection_algorithm.hpp"

DetectionAlgorithm::DetectionAlgorithm(int width, int height) {
    camera_width = width;
    camera_height = height;

    img = cv::Mat::zeros(camera_height, camera_width, CV_8UC1);
    period = (long long)1000000 / fps;
}

std::vector<cv::Point2f> cluster(cv::Mat input, int cluster_cnt = 4, int max_cnt = 10, double epsilon = 1.0)
{
    cv::Mat labels;
    std::vector<cv::Point2f> centers;
    centers.clear();

//    cv::Mat binary_img = make_binary_image(input,0.33);
    std::vector<cv::Point2f> locations;   // output, locations of non-zero pixels
    cv::findNonZero(input, locations);


    double compactness = cv::kmeans(locations, cluster_cnt, labels,
                                    cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, max_cnt, epsilon),
                                    3, cv::KMEANS_PP_CENTERS, centers);

    return centers;
}


void DetectionAlgorithm::Detect(){
    cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE,
                                                cv::Size(2 * 4 + 1, 2 * 4 + 1),
                                                cv::Point(4, 4));
    // cv::erode(input, output, element);
    cv::morphologyEx(img, img, cv::MORPH_OPEN, element);
    int nonzero_cnt = cv::countNonZero(img);

    if (nonzero_cnt > 4)
    {
        cluster_centers = cluster(img);
//        std::cout << "found " << cluster_centers.size() << " clusters" << std::endl;

    }

}

[[noreturn]] void DetectionAlgorithm::runtimeLoop() {
    bool to_check = false;
    int i = 0;
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
            if (to_check){
                if (ev->t > next_output_required_at){
                    next_output_required_at += period;
                    to_check=false;
                    if (i%100 == 0){
//                        imwrite("/home/aloch/dump/png/" + std::to_string(i) + ".png", img);
                    }

                    i++;
//                    Detect();

                    img = cv::Mat::zeros(camera_height, camera_width, CV_8UC1);
                }
            }
            img.at<uint8_t>(ev->y, ev->x) += 1;
        }
    }
}

void DetectionAlgorithm::start() {
    if(buffers.input_buffer != nullptr){
        thread_ptr = new boost::thread(&DetectionAlgorithm::runtimeLoop, this);
    }
}
