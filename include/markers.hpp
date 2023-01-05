//
// Created by aloch on 03.01.23.
//

#ifndef FRAMEWORK_MARKERS_MARKERS_HPP
#define FRAMEWORK_MARKERS_MARKERS_HPP

#include <Eigen/Core>
#include <Eigen/Geometry>

#include <metavision/sdk/base/events/event_cd.h>

#include "utils/options.hpp"

class Model3D {
public:
    Model3D();

    void setPose(const Eigen::Vector3f &trans, const Eigen::Quaternionf &rot);

    // Getters
    Eigen::Ref<Eigen::Vector3f> getVertexWorldCs(unsigned int ivert) { return vert_world_cs_[ivert]; }

    Eigen::Vector3f getVertexObjectCs(unsigned int ivert) { return vert_object_cs_[ivert]; }

    Eigen::Ref<Eigen::Vector2f> getVertexFrameCs(unsigned int ivert) { return vert_frame_cs_[ivert]; }

    //Utils
    float calculateDistanceFromCenter(const Metavision::Event2d *ev) const { return (Eigen::Vector2f(ev->x, ev->y) - projected_center_).norm(); }

    bool checkIfWithinRange(const Metavision::Event2d *ev) const { return calculateDistanceFromCenter(ev) < max_projected_distance_; }

private:
    void clearModel();
    void transform();
    Eigen::Vector2f project(const Eigen::Vector3f &point);
    Eigen::Vector2f project(unsigned int ivert);

    Eigen::Vector2f projected_center_;

    std::vector<Eigen::Vector3f> vert_object_cs_; // Coordinates of the vertices on the Object Coordinate System
    std::vector<Eigen::Vector3f> vert_world_cs_;  // Coordinates of the vertices on the World Coordinate System
    std::vector<Eigen::Vector2f> vert_frame_cs_;  // Projection of the vertices

    Eigen::Vector3f translation_;
    Eigen::Quaternionf rot_quaternion_;
    Eigen::Matrix3f camera_matrix_eigen_;

    float max_projected_distance_;

};

class Marker{
public:
    Marker();
private:
};

class MarkersManager{
public:
    MarkersManager(Utils::Options::MarkersSetup setup);
private:
    Utils::Options::MarkersSetup config;


};


#endif //FRAMEWORK_MARKERS_MARKERS_HPP
