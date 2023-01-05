//
// Created by aloch on 03.01.23.
//

#include "../include/markers.hpp"

Model3D::Model3D() {
    clearModel();
}

void Model3D::clearModel() {
        vert_object_cs_.clear();
        vert_world_cs_.clear();
        vert_frame_cs_.clear();
}

void Model3D::setPose(const Eigen::Vector3f &trans, const Eigen::Quaternionf &rot) {
    translation_ = trans;
    rot_quaternion_ = rot;
    transform();
}

Eigen::Vector2f Model3D::project(const Eigen::Vector3f &point)
{
    Eigen::Vector3f tmp = camera_matrix_eigen_ * point;
    if (abs(tmp[2]) > 0)
    {
        tmp /= tmp[2];
    }
    return Eigen::Vector2f{tmp[0], tmp[1]};
}

Eigen::Vector2f Model3D::project(unsigned int ivert)
{
    Eigen::Vector3f tmp = camera_matrix_eigen_ * vert_world_cs_[ivert];
    if (abs(tmp[2]) > 0)
    {
        tmp /= tmp[2];
    }
    return Eigen::Vector2f{tmp[0], tmp[1]};
}

void Model3D::transform()
{
    projected_center_ = project(translation_);

    max_projected_distance_ = 0;
    for (unsigned int ii = 0; ii < vert_object_cs_.size(); ii++)
    {
        vert_world_cs_[ii] = rot_quaternion_ * vert_object_cs_[ii] + translation_;
        vert_frame_cs_[ii] = project(ii);
        if (ii < 4)
        {
            if ((vert_frame_cs_[ii] - projected_center_).norm() > max_projected_distance_)
                max_projected_distance_ = (vert_frame_cs_[ii] - projected_center_).norm();
        }
    }
    max_projected_distance_ *= 1.2;
}

MarkersManager::MarkersManager(Utils::Options::MarkersSetup setup) {
    config = setup;
};