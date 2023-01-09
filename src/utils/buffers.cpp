//
// Created by aloch on 19.12.22.
//

#include "../../include/utils/buffers.hpp"

Queue* Buffers::getOutputBuffer() {
    Queue *tmp = new Queue(1024);
    output_buffers.push_back(tmp);

    return tmp;
}

bool Buffers::getBatch() {

    if (input_buffer != nullptr){
        return input_buffer->wait_dequeue_timed(current_batch, std::chrono::milliseconds(5));
    }
    else{
        throw "Trying to read from buffer without initializing input buffer";
    }
}

void Buffers::sendBatch(EventBatch to_send) {
    for(auto *buffer : output_buffers) {
        if(output_buffers.back() == buffer){
            buffer->enqueue(to_send);
        }
        else{
            EventBatch tmp;
            tmp.second = to_send.second;
            tmp.first = std::make_shared<std::vector<const Metavision::Event2d*>>(*to_send.first);
            buffer->enqueue(tmp);
        }
    }
}



