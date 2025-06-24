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
