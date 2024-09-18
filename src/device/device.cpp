//
// Created by Serdar on 19.09.2024.
//

#include "device/device.h"
#include "logger/console_logger.h"

Device::Device()
{
    int deviceCount = Device::freenect2.enumerateDevices();
    if (deviceCount == 0)
    {
        ConsoleLogger::getInstance()->log(Logger::Warning, "Device not found!");
        return;
    }
    for (int i = 0; i < deviceCount; i++)
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
