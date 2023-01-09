//
// Created by aloch on 19.12.22.
//

#ifndef FRAMEWORK_MARKERS_BUFFERS_HPP
#define FRAMEWORK_MARKERS_BUFFERS_HPP

#include "types.hpp"
#include <chrono>
#define QUEUE_SIZE 1024

class Buffers {
public:
    Queue* getOutputBuffer();
    Queue* getInputBuffer(){return input_buffer;};
    void setInputBuffer(Queue* input){input_buffer = input;};
    bool getBatch();

    void sendBatch(EventBatch batch);

    EventBatch current_batch;

    Queue* input_buffer;
    std::vector<Queue*> output_buffers;
};


#endif //FRAMEWORK_MARKERS_BUFFERS_HPP
