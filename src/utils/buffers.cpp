//
// Created by aloch on 19.12.22.
//

#include "../../include/utils/buffers.hpp"

Queue* Buffers::getOutputBuffer() {
    output_buffers.push_back(Queue(QUEUE_SIZE));

    return &output_buffers.back();
}

void Buffers::getBatch() {
    if (input_buffer != nullptr){
        input_buffer->wait_dequeue(current_batch);
    }
    else{
        throw "Trying to read from buffer without initializing input buffer";
    }
}

void Buffers::sendBatch(EventBatch to_send) {
    for(auto buffer = output_buffers.begin(), end = output_buffers.end() ; buffer != end; ++buffer) {
        if(output_buffers.end() == buffer){
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



