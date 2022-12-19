//
// Created by aloch on 15.12.22.
//

#include "../include/event_reader.hpp"

EventBufferReader::EventBufferReader(){

}

void EventBufferReader::readEvents(const Metavision::Event2d *ev_begin, const Metavision::Event2d *ev_end) {
    input_evt_vector = std::make_shared<std::vector<Metavision::Event2d>>();
    input_pointers_vector = std::make_shared<std::vector<const Metavision::Event2d*>>();

    std::transform(ev_begin, ev_end,
                   std::back_inserter(*input_evt_vector), [](Metavision::Event2d e) { return e; });
    std::transform(input_evt_vector->begin(), input_evt_vector->end(),
                   std::back_inserter(*input_pointers_vector), [](const Metavision::Event2d& e) { return &e; });

    EventBatch output_pair;
    output_pair.first = input_pointers_vector;
    output_pair.second = input_evt_vector;
    buffers.sendBatch(output_pair);
}
