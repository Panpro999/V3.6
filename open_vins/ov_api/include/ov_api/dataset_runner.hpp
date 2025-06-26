#pragma once

#include <Eigen/Dense>
#include <cv_bridge/cv_bridge.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/Imu.h>
#include <string>

#include "ov_api/openvins_api.hpp"
#include "state/State.h"

namespace openvins_api {

/// \brief \u6570\u636e\u96c6\u5feb\u901f\u8fd0\u884c\u5c01\u88c5
class Runner {
public:
  Runner(const std::string &yaml, const std::string &bag) : cfg_path(yaml), bag_path(bag), vio(yaml) {}

  /// \brief \u987a\u5e8f\u8bfb\u53d6\u5b58\u653e\u5305\u5e76\u4f20\u7ed9 OpenVINS
  void run(const std::string &out_csv = "") {
    rosbag::Bag bag;
    bag.open(bag_path, rosbag::bagmode::Read);
    std::vector<std::string> topics = {"/imu0", "/cam0/image_raw", "/cam1/image_raw"};
    rosbag::View view(bag, rosbag::TopicQuery(topics));

    std::ofstream out;
    if (!out_csv.empty()) {
      out.open(out_csv);
      out << "time,x,y,z\n";
    }

    for (const auto &m : view) {
      if (m.getTopic() == "/imu0") {
        auto imu = m.instantiate<sensor_msgs::Imu>();
        if (!imu)
          continue;
        Eigen::Vector3d wm(imu->angular_velocity.x, imu->angular_velocity.y, imu->angular_velocity.z);
        Eigen::Vector3d am(imu->linear_acceleration.x, imu->linear_acceleration.y, imu->linear_acceleration.z);
        vio.feedImu(imu->header.stamp.toSec(), wm, am);
      } else if (m.getTopic() == "/cam0/image_raw" || m.getTopic() == "/cam1/image_raw") {
        auto img = m.instantiate<sensor_msgs::Image>();
        if (!img)
          continue;
        cv_bridge::CvImageConstPtr cv_ptr;
        try {
          cv_ptr = cv_bridge::toCvShare(img, sensor_msgs::image_encodings::MONO8);
        } catch (cv_bridge::Exception &e) {
          continue;
        }
        int cam_id = (m.getTopic() == "/cam0/image_raw") ? 0 : 1;
        vio.feedCamera(cv_ptr->header.stamp.toSec(), cam_id, cv_ptr->image);
      }

      auto state = vio.getState();
      if (vio.initialized() && !state->_clones_IMU.empty()) {
        const auto &pose = state->_clones_IMU.rbegin()->second;
        Eigen::Vector3d p = pose->pos();
        std::cout << p.transpose() << std::endl;
        if (out.is_open()) {
          out << m.getTime().toSec() << "," << p(0) << "," << p(1) << "," << p(2) << "\n";
        }
      }
    }
    bag.close();
  }

private:
  std::string cfg_path;
  std::string bag_path;
  OpenVINS vio;
};

} // namespace openvins_api
