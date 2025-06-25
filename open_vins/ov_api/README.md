# OpenVINS C++ API

This folder provides a minimal wrapper that exposes the OpenVINS estimator as a
simple C++ class.  The header `openvins_api.hpp` can be included directly in
any project.

## Basic Usage

```cpp
#include <ov_api/openvins_api.hpp>

int main() {
    // Path to the OpenVINS configuration file
    openvins_api::OpenVINS vio("config/kaist/estimator_config.yaml");

    // Feed data
    vio.feedImu(timestamp, gyro, accel);
    vio.feedCamera(timestamp, 0, image);

    if (vio.initialized()) {
        auto state = vio.getState();
        // use state->pos(), state->quat(), ...
    }
}
```

The wrapper internally constructs a `ov_msckf::VioManager` and forwards
measurements to it.  See the configuration files in `open_vins/config/` for
examples.

## Complete Example

The repository contains `example_api.cpp` in the project root which
demonstrates how to create the wrapper and check that the estimator
initializes correctly.  The file is small enough to compile with a
single command:

```bash
# Install dependencies (Ubuntu names shown)
sudo apt-get install libeigen3-dev libopencv-dev libboost-filesystem-dev

# Compile only to verify headers
g++ -std=c++14 \
    -Iopen_vins -Iopen_vins/ov_api/include \
    -Iopen_vins/ov_core/src -Iopen_vins/ov_msckf/src \
    -Iopen_vins/ov_init/src -Iopen_vins/ov_eval/src \
    -I/usr/include/eigen3 -I/usr/include/opencv4 \
    -c example_api.cpp

# Linking against the full OpenVINS libraries is required to run the
# resulting binary.  Building the whole project with CMake will produce
# the necessary libraries for you.
```

Running the above command should create `example_api.o` proving that the
API headers are self contained.  When building OpenVINS with CMake or
Catkin you can link the object against the produced libraries to obtain
a runnable example.

## Dataset Runner

\u672c\u5305\u63d0\u4f9b\u4e86 `openvins_api::Runner` \u7c7b\u53ca\u547d\u4ee4\u884c\u5de5\u5177 `ov_run_dataset`\u3002\u53ea\u9700\u4e00\u884c\u4ee3\u7801\u5c31\u80fd\u8fd0\u884c\u5b58\u50a8\u597d\u7684 rosbag \u6570\u636e\u96c6\uff1a

```cpp
#include <ov_api/dataset_runner.hpp>
int main(int argc, char** argv) {
    return openvins_api::Runner("config.yaml", "data.bag").run(), 0;
}
```

### \u7f16\u8bd1

```bash
mkdir build && cd build
cmake .. -DOPENVINS_ROOT=.. # \u6839\u76ee\u5f55
make
```

### \u542f\u52a8

```bash
./ov_run_dataset --bag data.bag --config config.yaml --out traj.csv
```

\u8fd0\u884c\u65f6\u5c06\u5e38\u91cf\u8f93\u51fa\u6700\u65b0\u7d20\u5bb9\u57fa\u70b9\u4f4d\u7f6e\uff0c\u53ef\u9009\u4ee5 CSV \u5f62\u5f0f\u4fdd\u5b58\u3002
