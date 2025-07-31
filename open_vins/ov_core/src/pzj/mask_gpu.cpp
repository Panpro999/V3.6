#include "pzj/mask_gpu.h"

namespace ov_core {

void updateMaskGPU(cv::cuda::GpuMat &mask, const std::vector<cv::KeyPoint> &kps, int half_size, cv::cuda::Stream &stream) {
  if (mask.empty() || kps.empty())
    return;
  for (const auto &kp : kps) {
    int x = static_cast<int>(kp.pt.x);
    int y = static_cast<int>(kp.pt.y);
    int x1 = std::max(0, x - half_size);
    int y1 = std::max(0, y - half_size);
    int x2 = std::min(mask.cols, x + half_size);
    int y2 = std::min(mask.rows, y + half_size);
    if (x1 >= x2 || y1 >= y2)
      continue;
    cv::Rect roi(x1, y1, x2 - x1, y2 - y1);
    cv::cuda::GpuMat sub(mask, roi);
    sub.setTo(cv::Scalar(255), stream);
  }
}

} // namespace ov_core
