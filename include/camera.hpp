//
// Created by aloch on 15.12.22.
//

#ifndef FRAMEWORK_MARKERS_CAMERA_HPP
#define FRAMEWORK_MARKERS_CAMERA_HPP

#include "utils/options.hpp"
#include <metavision/sdk/driver/camera.h>
#include <metavision/hal/facilities/i_trigger_in.h>

class Camera {
public:
    Camera(Utils::Options::CameraSetup *setup);
    int width;
    int height;
private:
    Metavision::Camera camera_object;
    Metavision::Biases *biases;

    Eigen::Matrix3f camera_matrix_eigen;
    cv::Mat camera_matrix_cv;
    cv::Mat dist_coeffs;
};


#endif //FRAMEWORK_MARKERS_CAMERA_HPP
