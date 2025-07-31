#pragma once
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/types.hpp>
#include <vector>

namespace ov_core {
/// \brief Refine keypoints to subpixel accuracy on the GPU using LK iterations.
void refineSubpixGPU(const cv::cuda::GpuMat &img, std::vector<cv::Point2f> &pts, const cv::Size &winSize, cv::cuda::Stream &stream);
} // namespace ov_core
