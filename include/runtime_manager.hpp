//
// Created by aloch on 05.01.23.
//

#ifndef FRAMEWORK_MARKERS_RUNTIME_MANAGER_HPP
#define FRAMEWORK_MARKERS_RUNTIME_MANAGER_HPP

#include "utils/buffers.hpp"
#include "utils/types.hpp"
#include "markers.hpp"
#include "detection_algorithm.hpp"
#include "camera.hpp"

class RuntimeManager {
public:
    RuntimeManager(MarkersManager &markers_manager, Camera *cam);
    Buffers buffers;

    MarkersManager* markers;

    DetectionAlgorithm* detector;

    void start();


};


#endif //FRAMEWORK_MARKERS_RUNTIME_MANAGER_HPP
