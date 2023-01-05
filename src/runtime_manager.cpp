//
// Created by aloch on 05.01.23.
//

#include "../include/runtime_manager.hpp"

RuntimeManager::RuntimeManager(MarkersManager &markers_manager, Camera *cam) {
    markers = &markers_manager;
    detector = new DetectionAlgorithm(cam->width, cam->height);
}

void RuntimeManager::start() {
    detector->buffers.setInputBuffer(buffers.getInputBuffer());
    detector->start();
}



