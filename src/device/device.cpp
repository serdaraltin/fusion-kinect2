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
            deviceList[i] = Device::freenect2.getDeviceSerialNumber(i);
        }

    }

    std::pair<bool, std::string> Device::listDevices()
    {
        if(deviceList.empty())
            return std::make_pair(false, std::string("No devices!"));

        consoleLogger->log(Logger::Info, "Listing devices:");
        for(auto device : deviceList)
        {
            consoleLogger->log(Logger::Info, std::format("Device {}: {}", device.first,device.second));
        }
        return std::make_pair(true, std::string("Listing is successfull."));
    }

    std::pair<bool, std::string> Device::openDevices(const std::vector<std::string>& devices)
    {
        if(deviceList.empty())
            return std::make_pair(false, std::string("No devices!"));
        return std::make_pair(true, std::string("Device(s) opened."));
    }

    std::pair<bool, std::string> Device::selectDevices(const std::vector<int> &indexs)
    {
        if (indexs.empty())
            return {false, "List is empty !"};
        else if (indexs.size() > deviceList.size())
            return {false, "Invalid index size !"};

        for (const int index : indexs)
        {
            if (index < 0)
                return {false, "Invalid index !"};
            consoleLogger->log(Logger::Info,
                std::format("Selected Device {}: {}",
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
        return Device::deviceList;
    }

    std::string Device::getDeviceSerial(int index)
    {
        return Device::deviceList[index];
    }
}
