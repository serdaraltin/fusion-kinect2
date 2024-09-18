//
// Created by main on 19.09.2024.
//

#include "device/device.h"

Device::Device()
{
    int device_count = Device::freenect2.enumerateDevices();
    if (device_count == 0)
        return;
    for (int i = 0; i < device_count; i++)
        device_list[i] = Device::freenect2.getDeviceSerialNumber(i);
}

Device* Device::getInstance()
{
    if(instance == nullptr)
        instance = new Device();
    return instance;
}

std::array<std::string, sizeof(Device::max_device_num)>  Device::getDeviceList()
{
    return Device::device_list;
}

std::string Device::getDeviceSerial(int index)
{
    return Device::device_list[index];
}
