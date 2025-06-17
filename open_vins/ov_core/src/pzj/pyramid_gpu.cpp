#include "pzj/pyramid_gpu.h"
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/imgproc.hpp>

namespace ov_core {

/* ---- CUDA 版 buildPyramidGPU ---- */
void buildPyramidGPU(const cv::cuda::GpuMat& img0,
                     std::vector<cv::cuda::GpuMat>& pyr,
                     int levels,
                     const cv::Size& winSize,
                     cv::cuda::Stream& stream)
{
    CV_Assert(levels >= 1);
    pyr.resize(levels);

    const int pad_x = winSize.width;   // 与 CPU 版一致
    const int pad_y = winSize.height;

    /* ---------- level‑0 ---------- */
    // 同步版调用，使用默认 Stream::Null()
    cv::cuda::copyMakeBorder(img0, pyr[0],
                             pad_y, pad_y, pad_x, pad_x,
                             cv::BORDER_REFLECT101);

    /* ---------- 后续层 ---------- */
    cv::Size roi_sz(img0.cols, img0.rows);

    for (int l = 1; l < levels; ++l)
    {
        // ① 取上一层中心 ROI（去掉 padding）
        cv::Rect prev_roi_rect(pad_x, pad_y, roi_sz.width, roi_sz.height);
        cv::cuda::GpuMat prev_roi(pyr[l - 1], prev_roi_rect);

        // ② pyrDown
        cv::Size half((roi_sz.width + 1) >> 1, (roi_sz.height + 1) >> 1);
        cv::cuda::GpuMat half_roi;
        cv::cuda::pyrDown(prev_roi, half_roi, stream);

        // ③ 再补边（仍同步调用）
        cv::cuda::copyMakeBorder(half_roi, pyr[l],
                                 pad_y, pad_y, pad_x, pad_x,
                                 cv::BORDER_REFLECT101);

        roi_sz = half;
    }
}

} // namespace ov_core
