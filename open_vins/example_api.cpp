#include <ov_api/openvins_api.hpp>
#include <Eigen/Dense>
#include <opencv2/opencv.hpp>

int main() {
    // Instantiate the wrapper using one of the provided configurations
    openvins_api::OpenVINS vio("open_vins/config/kaist/estimator_config.yaml");

    // The example just constructs the estimator. In a real application you
    // would feed IMU and camera data.
    return vio.initialized() ? 0 : 1;
}
