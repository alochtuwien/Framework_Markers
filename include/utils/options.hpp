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
        bool is_recording = false;
        std::string file_path;
        std::string config_file_path;
        std::string biases_file;
        bool is_using_triggers = false;
        int triggers_channel;

        //Calibrations
        Eigen::Matrix3f camera_matrix_eigen;
        cv::Mat camera_matrix_cv;
        cv::Mat dist_coeffs; // Distortion vector
    };

    class MarkersSetup {
    public:
        std::vector<uint> ids;
        std::vector<std::vector<cv::Point3f>> coordinates;
        std::vector<std::vector<float>> frequencies;
    };

    class Setup {
    public:
        CameraSetup cam_config;
        MarkersSetup marker_config;

        MarkersSetup &getMarkerConfig();

        void setMarkerConfig(MarkersSetup &markerConfig);

        CameraSetup &getCamConfig();

        void setCamConfig(CameraSetup &camConfig);
    };

    class Parser {
    public:
        explicit Parser(int argc, char** argv);
        Setup current_setup;

    };

}







#endif //FRAMEWORK_MARKERS_OPTIONS_HPP
