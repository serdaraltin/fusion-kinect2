//
// Created by Serdar on 19.09.2024.
//

#ifndef DEVICE_H
#define DEVICE_H

#include "libfreenect2/libfreenect2.hpp"
#include "logger/console_logger.h"
#include <iostream>

#include <map>
#include <format>


namespace vision
{
    class Device {
    private:
        ConsoleLogger* consoleLogger = ConsoleLogger::getInstance();
        libfreenect2::Freenect2 freenect2;
        int max_device_num = 2;
        std::map<int, std::string> deviceList;
        static Device* instance;
        Device();
    public:
        std::pair<bool, std::string> listDevices();
        std::pair<bool, std::string> openDevices(const std::vector<std::string> &devices);
        std::pair<bool, std::string> selectDevices(const std::vector<int> &indexs);
        static Device* getInstance();
        std::map<int, std::string> getDeviceList();
        std::string getDeviceSerial(int index);
        Device(const Device&) = delete;
        Device& operator=(const Device&) = delete;
    };
}

#endif //DEVICE_H
