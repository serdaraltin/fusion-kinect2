//
// Created by Serdar on 19.09.2024.
//

#include "device/device_manager.h"
#include "debug/status.h"

namespace vision
{
    DeviceManager::DeviceManager()
    {
        const int deviceCount = freenect2.enumerateDevices();
        if (deviceCount == 0)
        {
            consoleLogger->log(Logger::Warning, "Device not found!");
            return;
        }
        for (int i = 0; i < deviceCount; i++)
        {
            deviceList.emplace_back(i,freenect2.getDeviceSerialNumber(i));
        }

    }

    DeviceManager* DeviceManager::getInstance()
    {
        if(instance == nullptr)
            instance = new DeviceManager();
        return instance;
    }

    std::vector<DeviceManager::Device> DeviceManager::getDeviceList()
    {
        return deviceList;
    }

    DeviceManager::Device DeviceManager::getDevice(const int id)
    {
        for(auto device: getDeviceList())
        {
            if(device.id == id)
                return device;
        }
        return {};
    }

    Result DeviceManager::listDevices(const std::vector<Device> &devices) const
    {
        if(devices.empty())
            return {Status::InvalidParam, "List is empty!" };

        consoleLogger->log(Logger::Info, "Listing DeviceManagers:");
        for(auto device : devices)
        {
            consoleLogger->log(Logger::Info,
                std::format("DeviceManager {}: {}", device.id,device.serial));
        }
        return {Status::Success, "Listing is successfull."};
    }

    Result DeviceManager::openDevices(const std::vector<Device> &devices)
    {
        if(devices.empty())
            return {Status::InvalidParam, std::string("List is empty!")};
        //TODO fill this fuction
        return {Status::Success, "DeviceManager(s) opened."};
    }

    Result DeviceManager::selectDevices(const std::vector<int> &ids)
    {
        if (ids.empty())
            return   {Status::NotFound,"List is empty !"};
        else if (ids.size() > deviceList.size())
            return {Status::InvalidParam, "Invalid index size !"};

        for (const int id : ids)
        {
            if (id < 0)
                return {Status::InvalidParam, "Invalid index !"};
            consoleLogger->log(Logger::Info,
                std::format("Selected DeviceManager {}: {}",
                    id ,getDevice(id).serial) );
        }
        return {Status::Success, "DeviceManager selected."};;
    }

}
