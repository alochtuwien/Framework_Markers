//
// Created by aloch on 19.12.22.
//

#include "../../include/utils/visualization.hpp"

VisualizationController::VisualizationController(int width_new, int height_new) {
    width = width_new;
    height = height_new;

    ui_ptr = new Metavision::MTWindow("Active markers", width, height, Metavision::Window::RenderMode::BGR);
    prod = new VisualizationProducer(width, height);
//    prod = new_producer;
}

[[noreturn]] void VisualizationController::runtimeLoop() {
    int i = 0;
    while(true){

        buffers.getBatch();
        if(i%3 == 0) {
            prod->reset_state();
            prod->registerBatch(&buffers.current_batch);
            auto out = prod->getOutput();
            ui_ptr->show_async(out);
            i = 0;
        }
        i++;

    }
}

void VisualizationController::start() {
    if(buffers.input_buffer != nullptr){

        thread_ptr = new boost::thread(&VisualizationController::runtimeLoop, this);
    }
}

VisualizationProducer::VisualizationProducer(int width_new, int height_new) {
    height = height_new;
    width = width_new;

    reset_state();
}

void VisualizationProducer::reset_state(){
    img = cv::Mat::zeros(height, width, CV_8UC1);
    output = cv::Mat::zeros(height, width, CV_8UC3);
}

void VisualizationProducer::registerBatch(EventBatch *batch) {
    for (const Metavision::Event2d* ev : *batch->first){
        img.at<uint8_t>(ev->y, ev->x) = 255;
    }
}

cv::Mat VisualizationProducer::getOutput() {
    cv::cvtColor(img, output, cv::COLOR_GRAY2BGR);
    return output;
}




