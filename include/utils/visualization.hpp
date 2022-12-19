//
// Created by aloch on 19.12.22.
//

#ifndef FRAMEWORK_MARKERS_VISUALIZATION_HPP
#define FRAMEWORK_MARKERS_VISUALIZATION_HPP

#include <metavision/sdk/ui/utils/mt_window.h>
#include <metavision/sdk/ui/utils/window.h>

#include <boost/thread.hpp>

#include <opencv2/opencv.hpp>

#include "buffers.hpp"
#include "types.hpp"

class VisualizationProducer {
public:
    VisualizationProducer(int width, int height);
    void registerBatch(EventBatch *batch);
    void reset_state();
    cv::Mat getOutput();

private:
    int width;
    int height;

    cv::Mat img;
    cv::Mat output;

};

class VisualizationController {
public:
    VisualizationController(int width, int height);
    Buffers buffers;
    void start();

    VisualizationProducer *prod;
private:
    int width;
    int height;

    Metavision::MTWindow *ui_ptr;

    [[noreturn]] void runtimeLoop();

    boost::thread *thread_ptr;
};



#endif //FRAMEWORK_MARKERS_VISUALIZATION_HPP
