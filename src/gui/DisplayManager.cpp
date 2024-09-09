#include "gui/DisplayManager.hpp"

void DisplayManager::showFrames(const cv::Mat& rgb, const cv::Mat& depth, const cv::Mat& ir) {
    if (rgb.empty() || depth.empty() || ir.empty()) {
        std::cerr << "One or more frames are empty. Skipping display." << std::endl;
        return;
    }

    cv::Size frame_size(640, 480);
    cv::Mat rgb_resized, depth_resized, ir_resized;
    cv::resize(rgb, rgb_resized, frame_size);
    cv::resize(depth, depth_resized, frame_size);
    cv::resize(ir, ir_resized, frame_size);

    cv::Mat rgb_3ch, depth_3ch, ir_3ch;
    cv::cvtColor(rgb_resized, rgb_3ch, cv::COLOR_RGBA2BGR);
    cv::cvtColor(depth_resized, depth_3ch, cv::COLOR_GRAY2BGR);
    cv::cvtColor(ir_resized, ir_3ch, cv::COLOR_GRAY2BGR);

    cv::Mat top_row, bottom_row, final_display;
    cv::hconcat(rgb_3ch, depth_3ch, top_row);
    cv::hconcat(ir_3ch, cv::Mat::zeros(ir_resized.size(), CV_8UC3), bottom_row);
    cv::vconcat(top_row, bottom_row, final_display);

    cv::namedWindow("Combined View", cv::WINDOW_NORMAL);
    cv::resizeWindow("Combined View", frame_size.width * 2, frame_size.height * 2);

    cv::imshow("Combined View", final_display);
}
