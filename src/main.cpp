#include "logging/FileLogger.hpp"
#include "device/KinectDevice.hpp"
#include "image-processing/FrameProcessor.hpp"
#include "gui/DisplayManager.hpp"

using namespace cv;
using namespace std;
using namespace libfreenect2;

KinectDevice kinect;


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

int initializeLog()
{
    FileLogger file_logger("LOGFILE");
    if (!file_logger.good()) {
        cerr << "Failed to open log file." << endl;
        return -1;
    }
    setGlobalLogger(&file_logger);
    cout << "Log file created." << endl;
    return 0;
}

int main() {
    if (!kinect.initialize())
        return -1;

    FrameProcessor frame_processor(kinect.getDevice()->getIrCameraParams(), kinect.getDevice()->getColorCameraParams());

    while (true) {
        processFrames(frame_processor, kinect);

        int key = waitKey(1);
        if (key == 'q') break;
    }

    kinect.shutdown();
    return 0;
}
