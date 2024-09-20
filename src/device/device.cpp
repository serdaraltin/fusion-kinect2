//
// Created by Serdar on 19.09.2024.
//

#include "device/device.h"


#include <iterator>
namespace vision
{
    Device::Device()
    {
        int deviceCount = Device::freenect2.enumerateDevices();
        if (deviceCount == 0)
        {
            consoleLogger->log(Logger::Warning, "Device not found!");
            return;
        }
        for (int i = 0; i < deviceCount; i++)
        {
            device_list[i] = Device::freenect2.getDeviceSerialNumber(i);
        }

    }

    std::pair<bool, std::string> Device::selectDevices(const std::vector<int> &indexs)
    {
        if (indexs.empty())
            return {false, "List is empty !"};
        else if (indexs.size() > device_list.size())
            return {false, "Invalid index size !"};

        for (const int index : indexs)
        {
            if (index < 0)
                return {false, "Invalid index !"};
            consoleLogger->log(Logger::Info,
                std::format("Selecting device -> Index: {} | Serial: {}",
                    index ,getDeviceSerial(index)) );
        }
        return {true, "Device selected."};;
    }


    Device* Device::getInstance()
    {
        if(instance == nullptr)
            instance = new Device();
        return instance;
    }

    std::map<int, std::string> Device::getDeviceList()
    {
        return Device::device_list;
    }

    std::string Device::getDeviceSerial(int index)
    {
        return Device::device_list[index];
    }
}
