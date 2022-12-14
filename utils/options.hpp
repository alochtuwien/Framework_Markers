//
// Created by aloch on 12.12.22.
//

#ifndef FRAMEWORK_MARKERS_OPTIONS_HPP
#define FRAMEWORK_MARKERS_OPTIONS_HPP

#include <boost/program_options.hpp>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include "yaml-cpp/yaml.h"

namespace po = boost::program_options;

namespace Utils::Options {
    class CameraSetup {
    public:
        CameraSetup();

    public:
        bool is_recording;
        std::string file_path;

        //Calibrations
        Eigen::Matrix3f camera_matrix_eigen;
        cv::Mat camera_matrix_cv;
        cv::Mat dist_coeffs; // Distortion vector


    };

    class Setup {
    public:
        CameraSetup cam_config;

        const CameraSetup &getCamConfig() const;

        void setCamConfig(const CameraSetup &camConfig);
    };

    class Parser {
    public:
        explicit Parser(int argc, char** argv);
        po::options_description *general_opt;
        Setup current_setup;
    };

}







#endif //FRAMEWORK_MARKERS_OPTIONS_HPP
