cmake_minimum_required(VERSION 3.10)
project(ov_api)

set(OPENVINS_ROOT ${OPENVINS_ROOT})

find_package(catkin REQUIRED COMPONENTS roscpp rosbag cv_bridge ov_core ov_msckf ov_init)
find_package(Eigen3 REQUIRED)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${OPENVINS_ROOT}
    ${OPENVINS_ROOT}/ov_api/include
)

add_executable(ov_run_dataset src/ov_run_dataset.cpp)
add_executable(example_main src/example_main.cpp)

target_link_libraries(ov_run_dataset ${catkin_LIBRARIES})
target_link_libraries(example_main ${catkin_LIBRARIES})

install(DIRECTORY include/
        DESTINATION include/ov_api
        FILES_MATCHING PATTERN "*.hpp")

install(TARGETS ov_run_dataset example_main
        RUNTIME DESTINATION bin)
