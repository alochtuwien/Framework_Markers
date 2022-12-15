//
// Created by aloch on 15.12.22.
//

#ifndef FRAMEWORK_MARKERS_CAMERA_HPP
#define FRAMEWORK_MARKERS_CAMERA_HPP

#include "utils/options.hpp"
#include <metavision/sdk/driver/camera.h>
#include <metavision/hal/facilities/i_trigger_in.h>
#include "event_reader.hpp"

class Camera {
public:
    Camera(Utils::Options::CameraSetup *setup);
    int width;
    int height;

    void initialize_camera();
    void start() {camera_object.start();};
private:
    Metavision::Camera camera_object;
    Metavision::Biases *biases;

    bool is_triggering_active = false;

    Eigen::Matrix3f camera_matrix_eigen;
    cv::Mat camera_matrix_cv;
    cv::Mat dist_coeffs;

    EventBufferReader reader;
    Queue *getOutputBuffer() {return reader.getOutputBuffer();};
};


#endif //FRAMEWORK_MARKERS_CAMERA_HPP
