#ifndef DISPLAY_MANAGER_HPP
#define DISPLAY_MANAGER_HPP

#include <opencv2/opencv.hpp>

class DisplayManager {
public:
    static void showFrames(const cv::Mat& rgb, const cv::Mat& depth, const cv::Mat& ir);
};

#endif // DISPLAY_MANAGER_HPP
