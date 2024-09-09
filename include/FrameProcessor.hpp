#ifndef FRAME_PROCESSOR_HPP
#define FRAME_PROCESSOR_HPP

#include <libfreenect2/registration.h>
#include <opencv2/opencv.hpp>

class FrameProcessor {
private:
    libfreenect2::Registration registration_;

public:
    FrameProcessor(const libfreenect2::Freenect2Device::IrCameraParams& ir_params, const libfreenect2::Freenect2Device::ColorCameraParams& color_params);
    cv::Mat processDepthFrame(const libfreenect2::Frame* frame);
    cv::Mat processIrFrame(const libfreenect2::Frame* frame);
    void applyRegistration(const libfreenect2::Frame* rgb, const libfreenect2::Frame* depth, libfreenect2::Frame* undistorted, libfreenect2::Frame* registered);
};

#endif // FRAME_PROCESSOR_HPP
