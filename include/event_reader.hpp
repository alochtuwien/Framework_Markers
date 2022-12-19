//
// Created by aloch on 15.12.22.
//

#ifndef FRAMEWORK_MARKERS_EVENT_READER_HPP
#define FRAMEWORK_MARKERS_EVENT_READER_HPP

#include <metavision/sdk/base/events/event2d.h>
#include <memory>
#include "utils/types.hpp"
#include "utils/buffers.hpp"
#include <algorithm>

class EventBufferReader {
public:
    EventBufferReader();

    Buffers buffers;

    //test
    void readEvents(const Metavision::Event2d *ev_begin, const Metavision::Event2d *ev_end);

private:
    [[noreturn]] void runtimeLoop();

    std::shared_ptr<std::vector<Metavision::Event2d>> input_evt_vector;
    std::shared_ptr<std::vector<const Metavision::Event2d*>> input_pointers_vector;
};



#endif //FRAMEWORK_MARKERS_EVENT_READER_HPP
