//
// Created by aloch on 19.12.22.
//

#ifndef FRAMEWORK_MARKERS_VISUALIZATION_HPP
#define FRAMEWORK_MARKERS_VISUALIZATION_HPP

#include <metavision/sdk/ui/utils/mt_window.h>
#include <metavision/sdk/ui/utils/window.h>
#include <metavision/sdk/ui/utils/event_loop.h>

#include <boost/thread.hpp>
#include <atomic>

#include <opencv2/opencv.hpp>

#include "buffers.hpp"
#include "types.hpp"

//class VisualizationProducer {
//public:
//    VisualizationProducer(int width, int height);
//    void registerBatch(EventBatch *batch);
//    void reset_state();
//    cv::Mat getOutput();
//
//private:
//    int width;
//    int height;
//
//    cv::Mat img;
//    cv::Mat output;
//
//};

class VisualizationController {
public:
    VisualizationController(int width, int height);
    Buffers buffers;
    void start();

    void getOutput();
    void resetState();

    bool isFinished();


//    VisualizationProducer *prod;
private:
    int width;
    int height;

    std::atomic<bool> to_close;
    std::atomic<bool> closed;

    Metavision::MTWindow *ui_ptr;



    [[noreturn]] void runtimeLoop();

    float fps = 30;
    Metavision::timestamp period = 0;
    Metavision::timestamp next_output_required_at = 0;

    cv::Mat img;
    cv::Mat output;

    boost::thread *thread_ptr;
};



#endif //FRAMEWORK_MARKERS_VISUALIZATION_HPP
