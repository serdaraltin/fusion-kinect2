#ifndef KINECT_DEVICE_HPP
#define KINECT_DEVICE_HPP

#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>

class KinectDevice {
private:
    libfreenect2::Freenect2 freenect2_;
    libfreenect2::Freenect2Device *device_;
    libfreenect2::PacketPipeline *pipeline_;
    libfreenect2::SyncMultiFrameListener listener_;
    std::string serial_;

public:
    KinectDevice();
    bool initialize();
    void shutdown();
    libfreenect2::SyncMultiFrameListener& getListener();
    libfreenect2::Freenect2Device* getDevice();
};

#endif // KINECT_DEVICE_HPP
