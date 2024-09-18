//
// Created by Serdar on 19.09.2024.
//

#ifndef DEVICE_H
#define DEVICE_H

#include "libfreenect2/libfreenect2.hpp"
#include <iostream>
#include <array>

class Device {
private:
    libfreenect2::Freenect2 freenect2;
    int max_device_num = 2;
    std::array<std::string, sizeof(max_device_num)> device_list;
    static Device* instance;
    Device();

public:
    static Device* getInstance();
    std::array<std::string, sizeof(max_device_num)> getDeviceList();
    std::string getDeviceSerial(int index);
    Device(const Device&) = delete;
    Device& operator=(const Device&) = delete;
};


#endif //DEVICE_H
