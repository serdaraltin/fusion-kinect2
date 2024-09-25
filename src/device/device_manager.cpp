//
// Created by Serdar on 19.09.2024.
//

#include "device/device_manager.h"

#include <algorithm>
#include <format>
#include <memory>
#include <bits/fs_path.h>

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

        auto _devices = enumerateDevices();
        devices.assign(devices.begin(), devices.end());
    }

    DeviceManager* DeviceManager::getInstance()
    {
        if(instance == nullptr)
            instance = new DeviceManager();
        return instance;
    }

    int DeviceManager::availableDeviceCount()
    {
        return freenect2.enumerateDevices();
    }

    std::vector<Device> DeviceManager::enumerateDevices()
    {
        std::vector<Device> _devices;
        int device_count = availableDeviceCount();
        if (device_count == 0)
            return _devices;
        for (int i = 0; i < device_count; ++i)
        {
            _devices.emplace_back(i,freenect2.getDeviceSerialNumber(i));
        }
        return _devices;
    }

    bool DeviceManager::deviceListIsEmpty() const
    {
        return devices.empty();
    }

    std::vector<Device> DeviceManager::getDeviceList() const
    {
        return devices;
    }

    Result DeviceManager::refreshDeviceList()
    {
        const auto _devices = enumerateDevices();
        if(_devices.empty())
        {
            devices.clear();
            return {Status::EmptyData,"No devices found!"};
        }

        devices.clear();
        devices.assign(_devices.begin(), _devices.end());
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
                std::format("{},{}",device.getIdx(),device.getNickName()));
        }
        return Result(Status::Success);
    }

    std::optional<int> DeviceManager::findDeviceIndex(std::vector<Device> _devices, int device_id)
    {
        const auto it = std::find_if(
            _devices.begin(),
            _devices.end(),
            [device_id] (const Device& device) -> bool{
                return device.getIdx() == device_id;
            });

        if(it != _devices.end())
        {
            return std::distance(_devices.begin(), it);
        }
        return std::nullopt;
    }

    bool DeviceManager::checkDevice(int device_id)
    {
        return !freenect2.getDeviceSerialNumber(device_id).empty();
    }

    std::optional<Device> DeviceManager::getDevice(int device_id)
    {
        if(!availableDeviceCount())
        {
            refreshDeviceList();
            if(!checkDevice(device_id) || deviceListIsEmpty())
                return std::nullopt;
        }

        for(auto& device : devices)
        {
            if(device.getIdx() == device_id)
                return device;
        }
        return std::nullopt;
    }

    bool DeviceManager::selectedListIsEmpty() const
    {
        return selected_devices.empty();
    }

    bool DeviceManager::selectDevice(int device_id)
    {
        const auto _device = getDevice(device_id);
        if(_device == std::nullopt)
            return false;

        selected_devices.emplace_back(
            _device->getIdx(),
            _device->getSerial(),
            _device->getNickName());
        return true;
    }

    bool DeviceManager::deselectDevice(int device_id)
    {
        if(!checkDevice(device_id))
            return false;
        const auto it = std::find_if(
            std::begin(devices),
            std::end(devices),
            selected_devices);

        if(it != std::end(devices))
        {
            devices.erase(it);
            return true;
        }
        return false;
    }

    void DeviceManager::clearSelectedList()
    {
        selected_devices.clear();
    }



}
