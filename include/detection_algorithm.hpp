//
// Created by aloch on 05.01.23.
//

#ifndef FRAMEWORK_MARKERS_DETECTION_ALGORITHM_HPP
#define FRAMEWORK_MARKERS_DETECTION_ALGORITHM_HPP

#include <opencv2/opencv.hpp>
#include "utils/buffers.hpp"
#include <boost/thread.hpp>

class DetectionAlgorithm {
public:
    DetectionAlgorithm(int width, int height);

    void start();
    Buffers buffers;

private:
    int camera_width;
    int camera_height;

    [[noreturn]] void runtimeLoop();
    void Detect();

    cv::Mat img;

    std::vector<cv::Point2f> cluster_centers;

    float fps = 1000;
    Metavision::timestamp period = 0;
    Metavision::timestamp next_output_required_at = 0;

    boost::thread *thread_ptr;

};


#endif //FRAMEWORK_MARKERS_DETECTION_ALGORITHM_HPP
