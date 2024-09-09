#include "image-process/FrameProcessor.hpp"

FrameProcessor::FrameProcessor(const libfreenect2::Freenect2Device::IrCameraParams& ir_params, const libfreenect2::Freenect2Device::ColorCameraParams& color_params)
    : registration_(ir_params, color_params) {}

cv::Mat FrameProcessor::processDepthFrame(const libfreenect2::Frame* frame) {
    cv::Mat depth(frame->height, frame->width, CV_16UC1, frame->data);
    cv::Mat normalized;
    depth.convertTo(normalized, CV_8UC1, 255.0 / 4500.0);
    return normalized;
}

cv::Mat FrameProcessor::processIrFrame(const libfreenect2::Frame* frame) {
    cv::Mat ir(frame->height, frame->width, CV_16UC1, frame->data);
    cv::Mat normalized;
    double max_val;
    cv::minMaxLoc(ir, nullptr, &max_val);
    ir.convertTo(normalized, CV_8UC1, 255.0 / max_val);
    return normalized;
}

void FrameProcessor::applyRegistration(const libfreenect2::Frame* rgb, const libfreenect2::Frame* depth, libfreenect2::Frame* undistorted, libfreenect2::Frame* registered) {
    registration_.apply(rgb, depth, undistorted, registered);
}
