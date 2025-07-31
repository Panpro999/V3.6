#include "pzj/subpix_gpu.h"
#include <opencv2/cudaoptflow.hpp>

namespace ov_core {

void refineSubpixGPU(const cv::cuda::GpuMat &img, std::vector<cv::Point2f> &pts, const cv::Size &winSize, cv::cuda::Stream &stream) {
  if (pts.empty())
    return;

  cv::Ptr<cv::cuda::SparsePyrLKOpticalFlow> lk = cv::cuda::SparsePyrLKOpticalFlow::create(winSize, 0);

  cv::Mat pts_mat(pts);
  pts_mat = pts_mat.reshape(2, 1);
  cv::cuda::GpuMat d_prev(pts_mat), d_next, d_status, d_err;

  // Run LK with the same image as both prev and next
  lk->calc(img, img, d_prev, d_next, d_status, d_err, stream);

  cv::Mat refined;
  d_next.download(refined, stream);
  stream.waitForCompletion();

  refined = refined.reshape(2, pts.size());
  pts.assign(refined.begin<cv::Point2f>(), refined.end<cv::Point2f>());
}

} // namespace ov_core
