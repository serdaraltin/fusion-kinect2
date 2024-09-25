//
// Created by Serdar on 19.09.2024.
//

#include "device/device_manager.h"

#include <algorithm>
#include <format>
#include <memory>

#include "debug/status.h"
#include "device/device.h"
#include "config/config.h"

namespace vision
{
    // Definition of the Singleton instance
    DeviceManager* DeviceManager::instance = nullptr;

    DeviceManager::DeviceManager()
    {
        freenect2_device = nullptr;
        freenect2_pipeline = new libfreenect2::CpuPacketPipeline();

        devices = enumerateDevices();
    }

    DeviceManager* DeviceManager::getInstance()
    {
        if(instance == nullptr)
            instance = new DeviceManager();
        return instance;
    }

    std::vector<Device> DeviceManager::getDeviceList() const
    {
        return devices;
    }

    bool DeviceManager::deviceListIsEmpty() const
    {
        return getDeviceList().empty();
    }

    std::vector<Device> DeviceManager::enumerateDevices()
    {
        std::vector<Device> _devices;
        int device_count = freenect2.enumerateDevices();
        if (device_count == 0)
            return _devices;
        for (const int idx : device_count)
        {
            _devices.emplace_back(idx,freenect2.getDeviceSerialNumber(idx));
        }
        return _devices;
    }

    Result DeviceManager::refreshDeviceList()
    {
        const auto _devices = enumerateDevices();
        if(_devices.empty())
            return {Status::EmptyData, "No devices found!"};

        getDeviceList() = _devices;
        return {Status::Success,"List refreshed."};
    }

    Result DeviceManager::logDevicesList() const
    {
        if(deviceListIsEmpty())
            return {Status::Cancelled,"List is empty!"};

        console_logger->log(Logger::Info,"Listing devices...");
        for(const auto& device : devices)
        {
            console_logger->log(
                Logger::Info,
                std::format("{},{}",device.getId(),device.getNickName()));
        }
        return Result(Status::Success);
    }




}
