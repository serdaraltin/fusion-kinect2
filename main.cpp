
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
    cv::Mat f = cv::Mat(frame->height, frame->width, CV_16UC1, frame->data);
    cv::Mat depth_frame_normalized;
    f.convertTo(depth_frame_normalized, CV_8UC1, 255.0 / 4500.0); // Normalize et
    return depth_frame_normalized;
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
    if (enable_depth)
        types |= libfreenect2::Frame::Ir | libfreenect2::Frame::Depth;

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

        cv::Mat rgb_frame = convertFrameToMat(rgb);
        cv::Mat depth_frame = convertFrameToMatDepth(depth);
        cv::Mat ir_frame = convertFrameToMatDepth(ir);


        // IR verisini normalize et
        cv::Mat ir_frame_normalized;
        double max_val;
        cv::minMaxLoc(ir_frame, nullptr, &max_val);
        ir_frame.convertTo(ir_frame_normalized, CV_8UC1, 255.0 / max_val); // Normalize et

        // IR görüntüsünü göster
        cv::imshow("IR Frame", ir_frame_normalized);

        // Görüntüleri Tek Ekranda Göster
        if (!rgb_frame.empty() && !depth_frame.empty() && !ir_frame.empty()) {
            // RGB ve diğer görüntülerin boyutlarını kontrol edin ve uyumlu hale getirin
            cv::Size new_size(640, 480);
            cv::resize(rgb_frame, rgb_frame, new_size);
            cv::resize(depth_frame, depth_frame, new_size);
            cv::resize(ir_frame, ir_frame, new_size);

            // Görüntüleri uygun türdeki `cv::Mat`'lere dönüştürün
            cv::Mat rgb_frame_3ch, depth_frame_3ch, ir_frame_3ch;
            cv::cvtColor(rgb_frame, rgb_frame_3ch, cv::COLOR_RGBA2BGR); // RGB'yi 3 kanal haline getirin
            cv::cvtColor(depth_frame, depth_frame_3ch, cv::COLOR_GRAY2BGR); // Depth'yi 3 kanal haline getirin
            cv::cvtColor(ir_frame, ir_frame_3ch, cv::COLOR_GRAY2BGR); // IR'yi 3 kanal haline getirin

            // Görüntüleri birleştir
            cv::Mat top_row, bottom_row, final_display;
            cv::hconcat(rgb_frame_3ch, depth_frame_3ch, top_row);
            cv::hconcat(ir_frame_3ch, cv::Mat::zeros(ir_frame.size(), CV_8UC3), bottom_row); // Eksik 4. alanı siyah olarak doldurun
            cv::vconcat(top_row, bottom_row, final_display);

            // Görüntüyü Göster
            cv::imshow("Combined View", final_display);
        }
        int key = cv::waitKey(1);

        if (key == 'q')
            break;

        listener.release(frames);
    }
    dev->stop();
    dev->close();
    return 0;
}
