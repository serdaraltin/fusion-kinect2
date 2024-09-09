#include "FileLogger.hpp"
#include "KinectDevice.hpp"
#include "FrameProcessor.hpp"
#include "DisplayManager.hpp"

void processFrames(FrameProcessor& frame_processor, KinectDevice& kinect) {
    libfreenect2::FrameMap frames;
    if (!kinect.getListener().waitForNewFrame(frames, 10 * 1000)) {
        std::cout << "Timeout!" << std::endl;
        return;
    }

    libfreenect2::Frame* rgb = frames[libfreenect2::Frame::Color];
    libfreenect2::Frame* depth = frames[libfreenect2::Frame::Depth];

    libfreenect2::Frame undistorted(512, 424, 4), registered(512, 424, 4);
    frame_processor.applyRegistration(rgb, depth, &undistorted, &registered);

    cv::Mat rgb_frame = cv::Mat(rgb->height, rgb->width, CV_8UC4, rgb->data);
    cv::Mat depth_frame = frame_processor.processDepthFrame(depth);
    cv::Mat ir_frame = frame_processor.processIrFrame(&registered);

    DisplayManager::showFrames(rgb_frame, depth_frame, ir_frame);

    kinect.getListener().release(frames);
}

int main() {
    FileLogger file_logger("LOGFILE");
    if (!file_logger.good()) {
        std::cerr << "Failed to open log file." << std::endl;
        return -1;
    }
    setGlobalLogger(&file_logger);
    std::cout << "Log file created." << std::endl;

    KinectDevice kinect;
    if (!kinect.initialize()) return -1;

    FrameProcessor frame_processor(kinect.getDevice()->getIrCameraParams(), kinect.getDevice()->getColorCameraParams());

    while (true) {
        processFrames(frame_processor, kinect);

        int key = cv::waitKey(1);
        if (key == 'q') break;
    }

    kinect.shutdown();
    return 0;
}
