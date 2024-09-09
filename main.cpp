#include <libfreenect2/libfreenect2.hpp>
#include <libfreenect2/frame_listener_impl.h>
#include <libfreenect2/registration.h>
#include <libfreenect2/packet_pipeline.h>
#include <libfreenect2/logger.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace libfreenect2;
using namespace std;
using namespace cv;

// Logger class for file logging
class FileLogger : public Logger {
private:
    std::ofstream logfile_;
public:
    FileLogger(const char *filename) {
        if (filename) logfile_.open(filename);
        level_ = Debug;
    }
    bool good() const {
        return logfile_.is_open() && logfile_.good();
    }
    void log(Level level, const std::string &message) override {
        logfile_ << "[" << level2str(level) << "] " << message << std::endl;
    }
};

// Class to handle Kinect device initialization and shutdown
class KinectDevice {
private:
    Freenect2 freenect2_;
    Freenect2Device *device_;
    PacketPipeline *pipeline_;
    SyncMultiFrameListener listener_;
    std::string serial_;

public:
    KinectDevice() : device_(nullptr), pipeline_(new CpuPacketPipeline()), listener_(Frame::Color | Frame::Ir | Frame::Depth) {}

    bool initialize() {
        if (freenect2_.enumerateDevices() == 0) {
            cout << "No device connected!" << endl;
            return false;
        }
        serial_ = freenect2_.getDefaultDeviceSerialNumber();
        device_ = freenect2_.openDevice(serial_, pipeline_);
        if (!device_) {
            cout << "Failed to open device!" << endl;
            return false;
        }
        device_->setColorFrameListener(&listener_);
        device_->setIrAndDepthFrameListener(&listener_);
        return device_->start();
    }

    void shutdown() {
        if (device_) {
            device_->stop();
            device_->close();
        }
    }

    SyncMultiFrameListener& getListener() { return listener_; }
    Freenect2Device* getDevice() { return device_; }
};

// Class to process and normalize frames
class FrameProcessor {
private:
    Registration registration_;

public:
    FrameProcessor(const Freenect2Device::IrCameraParams& ir_params, const Freenect2Device::ColorCameraParams& color_params)
        : registration_(ir_params, color_params) {}

    Mat processDepthFrame(const Frame* frame) {
        Mat depth(frame->height, frame->width, CV_16UC1, frame->data);
        Mat normalized;
        depth.convertTo(normalized, CV_8UC1, 255.0 / 4500.0);
        return normalized;
    }

    Mat processIrFrame(const Frame* frame) {
        Mat ir(frame->height, frame->width, CV_16UC1, frame->data);
        Mat normalized;
        double max_val;
        minMaxLoc(ir, nullptr, &max_val);
        ir.convertTo(normalized, CV_8UC1, 255.0 / max_val);
        return normalized;
    }

    void applyRegistration(const Frame* rgb, const Frame* depth, Frame* undistorted, Frame* registered) {
        registration_.apply(rgb, depth, undistorted, registered);
    }
};

// Class to manage and display frames
class DisplayManager {
public:
    static void showFrames(const Mat& rgb, const Mat& depth, const Mat& ir) {
        if (rgb.empty() || depth.empty() || ir.empty()) {
            cerr << "One or more frames are empty. Skipping display." << endl;
            return;
        }

        Size frame_size(640, 480);
        Mat rgb_resized, depth_resized, ir_resized;
        resize(rgb, rgb_resized, frame_size);
        resize(depth, depth_resized, frame_size);
        resize(ir, ir_resized, frame_size);

        Mat rgb_3ch, depth_3ch, ir_3ch;
        cvtColor(rgb_resized, rgb_3ch, COLOR_RGBA2BGR);
        cvtColor(depth_resized, depth_3ch, COLOR_GRAY2BGR);
        cvtColor(ir_resized, ir_3ch, COLOR_GRAY2BGR);

        Mat top_row, bottom_row, final_display;
        hconcat(rgb_3ch, depth_3ch, top_row);
        hconcat(ir_3ch, Mat::zeros(ir_resized.size(), CV_8UC3), bottom_row);
        vconcat(top_row, bottom_row, final_display);

        namedWindow("Combined View", WINDOW_NORMAL);
        resizeWindow("Combined View", frame_size.width * 2, frame_size.height * 2);

        imshow("Combined View", final_display);
    }
};

void processFrames(FrameProcessor& frame_processor, KinectDevice& kinect) {
    FrameMap frames;
    if (!kinect.getListener().waitForNewFrame(frames, 10 * 1000)) {
        cout << "Timeout!" << endl;
        return;
    }

    Frame* rgb = frames[Frame::Color];
    Frame* depth = frames[Frame::Depth];

    Frame undistorted(512, 424, 4), registered(512, 424, 4);
    frame_processor.applyRegistration(rgb, depth, &undistorted, &registered);

    Mat rgb_frame = Mat(rgb->height, rgb->width, CV_8UC4, rgb->data);
    Mat depth_frame = frame_processor.processDepthFrame(depth);
    Mat ir_frame = frame_processor.processIrFrame(&registered);

    DisplayManager::showFrames(rgb_frame, depth_frame, ir_frame);

    kinect.getListener().release(frames);
}

int main() {
    FileLogger file_logger("LOGFILE");
    if (!file_logger.good()) {
        cerr << "Failed to open log file." << endl;
        return -1;
    }
    setGlobalLogger(&file_logger);
    cout << "Log file created." << endl;

    KinectDevice kinect;
    if (!kinect.initialize()) return -1;

    FrameProcessor frame_processor(kinect.getDevice()->getIrCameraParams(), kinect.getDevice()->getColorCameraParams());

    while (true) {
        processFrames(frame_processor, kinect);

        int key = waitKey(1);
        if (key == 'q') break;
    }

    kinect.shutdown();
    return 0;
}
