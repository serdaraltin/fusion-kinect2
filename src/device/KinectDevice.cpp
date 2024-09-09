#include "KinectDevice.hpp"
#include <iostream>

KinectDevice::KinectDevice()
    : device_(nullptr), pipeline_(new libfreenect2::CpuPacketPipeline()), listener_(libfreenect2::Frame::Color | libfreenect2::Frame::Ir | libfreenect2::Frame::Depth) {}

bool KinectDevice::initialize() {
    if (freenect2_.enumerateDevices() == 0) {
        std::cout << "No device connected!" << std::endl;
        return false;
    }
    serial_ = freenect2_.getDefaultDeviceSerialNumber();
    device_ = freenect2_.openDevice(serial_, pipeline_);
    if (!device_) {
        std::cout << "Failed to open device!" << std::endl;
        return false;
    }
    device_->setColorFrameListener(&listener_);
    device_->setIrAndDepthFrameListener(&listener_);
    return device_->start();
}

void KinectDevice::shutdown() {
    if (device_) {
        device_->stop();
        device_->close();
    }
}

libfreenect2::SyncMultiFrameListener& KinectDevice::getListener() {
    return listener_;
}

libfreenect2::Freenect2Device* KinectDevice::getDevice() {
    return device_;
}
