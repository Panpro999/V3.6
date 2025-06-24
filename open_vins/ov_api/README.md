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
