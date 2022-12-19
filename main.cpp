#include <iostream>

#include "include/utils/options.hpp"
#include "include/camera.hpp"
#include "include/utils/visualization.hpp"
int main(int argc, char *argv[]) {

    //Parse options
    Utils::Options::Parser parser(argc, argv);

    if (parser.current_setup.cam_config.is_recording){
        std::cout << "Using recording: " << parser.current_setup.cam_config.file_path << std::endl;
    }
    else{
        std::cout << "Using camera with biases from: " << parser.current_setup.cam_config.biases_file << std::endl;
        std::cout << "Using camera config from: " << parser.current_setup.cam_config.config_file_path << std::endl;
    }

    Camera cam(&parser.current_setup.getCamConfig());
    cam.initialize_camera();

    std::cout << cam.width << " " << cam.height << std::endl;

    VisualizationController vis(cam.width, cam.height);
    vis.buffers.setInputBuffer(cam.reader.buffers.getOutputBuffer());

    cam.start();
    vis.start();



    while (true)
    {

    }


    return 0;
}
