#include <iostream>

#include "utils/options.hpp"

int main(int argc, char *argv[]) {

    //Parse options
    Utils::Options::Parser parser(argc, argv);
    if (parser.current_setup.cam_config.is_recording){
        std::cout << "Using recording: " << parser.current_setup.cam_config.file_path << std::endl;
    }



    return 0;
}
