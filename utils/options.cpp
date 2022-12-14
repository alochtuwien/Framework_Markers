//
// Created by aloch on 12.12.22.
//

#include <iostream>
#include "options.hpp"

Utils::Options::Parser::Parser(int argc, char **argv){

    std::string camera_config_filepath;
    std::string recording_filepath;
    std::string biases_filepath;

    general_opt = new po::options_description("General Options");
    general_opt->add_options()
            ("help,h", "Help screen")
            ("input_file,i", po::value<std::string>(&recording_filepath)->default_value(""), "Recording file (raw)")
            ("camera_config_file,c", po::value<std::string>(&camera_config_filepath)->required(), "config file (yaml)")
            ("biases_file,b", po::value<std::string>(&biases_filepath)->required(), "Biases file (bias)");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, *general_opt), vm);
    po::notify(vm);

    if (vm.count("help"))
        std::cout << *general_opt << '\n';


    //Camera config
    CameraSetup cam_config;

    if (vm["input_file"].as<std::string>() != ""){
        cam_config.is_recording = true;
        cam_config.file_path = vm["input_file"].as<std::string>();
    }

    YAML::Node config = YAML::LoadFile(vm["camera_config_file"].as<std::string>());

    std::vector<float> camera_matrix_vect = config["CameraMatrix"]["data"].as<std::vector<float>>();
    std::vector<float> dist_coeffs_vect = config["DistCoeff"]["data"].as<std::vector<float>>();
    int dist_coeffs_len = config["DistCoeff"]["len"].as<int>();

    assert((int)camera_matrix_vect.size() == 9);
    assert((int)dist_coeffs_vect.size() == dist_coeffs_len);

    //camera matrices
    cv::Mat camera_matrix = cv::Mat1f(3, 3);
    current_setup.cam_config.camera_matrix_cv = camera_matrix;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            current_setup.cam_config.camera_matrix_cv.at<float>(row, col) = camera_matrix_vect[row * 3 + col];
            current_setup.cam_config.camera_matrix_eigen(row, col) = camera_matrix_vect[row * 3 + col];
        }
    }
    //dist coeffs
    cv::Mat dist_coeffs = cv::Mat1f(1,5);
    current_setup.cam_config.dist_coeffs = dist_coeffs;

    for(std::vector<int>::size_type i = 0; i != dist_coeffs_vect.size(); i++){
        current_setup.cam_config.dist_coeffs.at<float>(0, i) = dist_coeffs_vect[i];
    }







    current_setup.cam_config = cam_config;




    delete general_opt;
}

const Utils::Options::CameraSetup &Utils::Options::Setup::getCamConfig() const {
    return cam_config;
}

void Utils::Options::Setup::setCamConfig(const Utils::Options::CameraSetup &camConfig) {
    cam_config = camConfig;
}

Utils::Options::CameraSetup::CameraSetup() {
    cv::Mat new_coeffs(5, 1, cv::DataType<double>::type);
    dist_coeffs = new_coeffs;
}
