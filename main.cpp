
#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>
#include <iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
//#include <OpenNI.h>

std::string serial;
libfreenect2::Freenect2 freenect2;
libfreenect2::Freenect2Device *dev = 0;
libfreenect2::PacketPipeline *pipeline = 0;

class MyFileLogger: public libfreenect2::Logger
{
private:
    std::ofstream logfile_;
public:
    MyFileLogger(const char *filename)
    {
        if (filename)
            logfile_.open(filename);
        level_ = Debug;
    }
    bool good()
    {
        return logfile_.is_open() && logfile_.good();
    }
    virtual void log(Level level, const std::string &message)
    {
        logfile_ << "[" << libfreenect2::Logger::level2str(level) << "] " << message << std::endl;
    }
};

int create_logger()
{
    MyFileLogger *file_logger = new MyFileLogger("LOGFILE");
    if(file_logger->good())
    {
        libfreenect2::setGlobalLogger(file_logger);
        std::cout << "Log file created." << std::endl;
        return 0;
    }else
    {
        std::cerr << "Failed to open log file." << std::endl;
        delete file_logger;
        return -1;
    }
}

bool find_device()
{
    if(freenect2.enumerateDevices() == 0)
    {
        std::cout << "no device connected!" << std::endl;
        return false;
    }
    if (serial == "")
        serial = freenect2.getDefaultDeviceSerialNumber();
    return true;
}

cv::Mat convertFrameToMat(libfreenect2::Frame *frame) {
    return cv::Mat(frame->height, frame->width, CV_8UC4, frame->data);
}
cv::Mat convertFrameToMatDepth(const libfreenect2::Frame *frame) {
    return cv::Mat(frame->height, frame->width, CV_16UC1, frame->data);
}
int main()
{
    if (!find_device())
        exit(0);
    pipeline = new libfreenect2::CpuPacketPipeline();
    dev = freenect2.openDevice(serial, pipeline);

    int types = 0;
    bool enable_rgb = true;
    bool enable_depth = true;

    if (enable_rgb)
        types |= libfreenect2::Frame::Color;
    /*if (enable_depth)
        types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;*/

    libfreenect2::SyncMultiFrameListener listener(types);
    libfreenect2::FrameMap frames;
    dev->setColorFrameListener(&listener);
    dev->setIrAndDepthFrameListener(&listener);

    if (enable_rgb && enable_depth)
    {
        if (!dev->start())
            return -1;
    }
    else
    {
        if (!dev->startStreams(enable_rgb, enable_depth))
            return -1;
    }
    std::cout << "device serial: " << dev->getSerialNumber() << std::endl;
    std::cout << "device firmware: " << dev->getFirmwareVersion() << std::endl;

    libfreenect2::Registration* registration = new libfreenect2::Registration(dev->getIrCameraParams(), dev->getColorCameraParams());
    libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4);


    while(true)
    {
        if (!listener.waitForNewFrame(frames, 10*1000)) // 10 sconds
        {
            std::cout << "timeout!" << std::endl;
            return -1;
        }
        libfreenect2::Frame *rgb = frames[libfreenect2::Frame::Color];
        libfreenect2::Frame *ir = frames[libfreenect2::Frame::Ir];
        libfreenect2::Frame *depth = frames[libfreenect2::Frame::Depth];
        registration->apply(rgb, depth, &undistorted, &registered);

        cv::Mat frame = convertFrameToMat(rgb);
        cv::imshow("fusion-body", frame);

        int key = cv::waitKey(1);

        if (key == 'q')
            break;


        listener.release(frames);
    }


}
