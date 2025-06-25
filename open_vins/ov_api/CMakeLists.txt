cmake_minimum_required(VERSION 3.10)
project(ov_api)

# \u5982\u679c\u6ca1\u6709\u4f20\u5165 OPENVINS_ROOT\uff0c\u5219\u9ed8\u8ba4\u4e3a\u9879\u76ee\u6839\u76ee\u5f55
if(NOT OPENVINS_ROOT)
    set(OPENVINS_ROOT ${CMAKE_SOURCE_DIR})
endif()

find_package(catkin REQUIRED COMPONENTS roscpp rosbag cv_bridge ov_core ov_msckf ov_init)
find_package(Eigen3 REQUIRED)

include_directories(
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
    ${OPENVINS_ROOT}
    ${OPENVINS_ROOT}/ov_api/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
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
