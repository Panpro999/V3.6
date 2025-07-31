#pragma once
#include <opencv2/core/cuda.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/cudaarithm.hpp>
#include <vector>

namespace ov_core {
/// \brief Update mask on GPU by drawing rectangles around keypoints.
void updateMaskGPU(cv::cuda::GpuMat &mask, const std::vector<cv::KeyPoint> &kps, int half_size, cv::cuda::Stream &stream);
} // namespace ov_core
