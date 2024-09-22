//
// Created by Serdar on 19.09.2024.
//

#include "device/device_manager.h"
#include "debug/status.h"
#include "device/device.h"

namespace vision
{
    DeviceManager* DeviceManager::instance = nullptr;

    DeviceManager::DeviceManager()
    {
        const int deviceCount = freenect2.enumerateDevices();
        if (deviceCount == 0)
        {
            console_logger->log(Logger::Warning, "Device not found!");
            return;
        }
        for (int i = 0; i < deviceCount; i++)
        {
            device_list.emplace_back(i,freenect2.getDeviceSerialNumber(i));
        }

    }

    DeviceManager* DeviceManager::getInstance()
    {
        if(instance == nullptr)
            instance = new DeviceManager();
        return instance;
    }

    std::vector<Device> DeviceManager::getDeviceList()
    {
        return device_list;
    }

    Device DeviceManager::getDevice(const int id)
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

        console_logger->log(Logger::Info, "Listing Devices");
        for(auto device : devices)
        {
            console_logger->log(Logger::Info,
                std::format("Device {}: {}", device.id,device.serial));
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
        else if (ids.size() > device_list.size())
            return {Status::InvalidParam, "Invalid index size !"};

        for (const int id : ids)
        {
            if (id < 0)
                return {Status::InvalidParam, "Invalid index !"};
            console_logger->log(Logger::Info,
                std::format("Selected DeviceManager {}: {}",
                    id ,getDevice(id).serial) );
        }
        return {Status::Success, "DeviceManager selected."};;
    }

}
