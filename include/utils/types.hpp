//
// Created by aloch on 15.12.22.
//

#ifndef FRAMEWORK_MARKERS_TYPES_HPP
#define FRAMEWORK_MARKERS_TYPES_HPP

#include <metavision/sdk/base/events/event2d.h>
#include <readerwriterqueue/readerwriterqueue.h>
#include <memory>

typedef std::pair<std::shared_ptr<std::vector<const Metavision::Event2d*>>,
                        std::shared_ptr<std::vector<Metavision::Event2d>>> EventBatch;

typedef moodycamel::BlockingReaderWriterQueue<EventBatch> Queue;

#endif //FRAMEWORK_MARKERS_TYPES_HPP
