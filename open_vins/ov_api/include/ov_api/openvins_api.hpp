#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ov_core/src/utils/sensor_data.h"
#include "ov_core/src/utils/opencv_yaml_parse.h"
#include "ov_msckf/src/core/VioManager.h"
#include "ov_msckf/src/core/VioManagerOptions.h"

namespace openvins_api {

class OpenVINS {
public:
    explicit OpenVINS(const std::string &config_path) {
        parser = std::make_shared<ov_core::YamlParser>(config_path);
        params.print_and_load(parser);
        vio = std::make_shared<ov_msckf::VioManager>(params);
    }

    bool initialized() const { return vio->initialized(); }

    void feedImu(double timestamp, const Eigen::Vector3d &wm, const Eigen::Vector3d &am) {
        ov_core::ImuData data;
        data.timestamp = timestamp;
        data.wm = wm;
        data.am = am;
        vio->feed_measurement_imu(data);
    }

    void feedCamera(double timestamp, int cam_id, const cv::Mat &image) {
        ov_core::CameraData msg;
        msg.timestamp = timestamp;
        msg.sensor_ids.push_back(cam_id);
        msg.images.push_back(image);
        msg.masks.emplace_back();
        vio->feed_measurement_camera(msg);
    }

    std::shared_ptr<ov_msckf::State> getState() { return vio->get_state(); }

private:
    std::shared_ptr<ov_core::YamlParser> parser;
    ov_msckf::VioManagerOptions params;
    std::shared_ptr<ov_msckf::VioManager> vio;
};

} // namespace openvins_api

