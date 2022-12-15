cmake_minimum_required(VERSION 3.24)
project(Framework_Markers)

set(CMAKE_CXX_STANDARD 17)

find_package( Boost COMPONENTS program_options REQUIRED )

find_package(OpenCV 4 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

find_package(Eigen3 3.3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

find_package(yaml-cpp REQUIRED)
include_directories(${YAML_CPP_INCLUDE_DIRS})

find_package(MetavisionSDK COMPONENTS core driver REQUIRED)



add_executable(active_markers main.cpp src/utils/options.cpp include/utils/options.hpp src/camera.cpp include/camera.hpp)

target_include_directories(active_markers PRIVATE ${Boost_INCLUDE_DIR})
target_link_libraries( active_markers
                        ${OpenCV_LIBS}
                        yaml-cpp
                        MetavisionSDK::core
                        MetavisionSDK::driver
                        Boost::program_options
                         )


