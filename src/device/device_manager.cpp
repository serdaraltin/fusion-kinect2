//
// Created by Serdar on 19.09.2024.
//

#include "device/device_manager.h"

#include <algorithm>
#include <format>
#include "debug/status.h"
#include "device/device.h"

namespace vision
{
    // Definition of the Singleton instance
    device_manager* device_manager::instance = nullptr;

    device_manager::device_manager()
    {
        freenect2_device = nullptr;
        freenect2_pipeline = new libfreenect2::CpuPacketPipeline();

        auto _devices = enumerateDevices();
        devices.assign(_devices.begin(), _devices.end());
    }

    device_manager* device_manager::getInstance()
    {
        if(instance == nullptr)
            instance = new device_manager();
        return instance;
    }

    int device_manager::availableDeviceCount()
    {
        return freenect2.enumerateDevices();
    }

    std::vector<device> device_manager::enumerateDevices()
    {
        std::vector<device> _devices;
        int device_count = availableDeviceCount();
        if (device_count == 0)
            return _devices;
        for (int i = 0; i < device_count; ++i)
        {
            _devices.emplace_back(i,freenect2.getDeviceSerialNumber(i));
        }
        return _devices;
    }

    bool device_manager::deviceListIsEmpty() const
    {
        return devices.empty();
    }

    std::vector<device> device_manager::getDeviceList()
    {
        auto _devices = enumerateDevices();
        devices.assign(_devices.begin(), _devices.end());
        return devices;
    }

    Result device_manager::refreshDeviceList()
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

    Result device_manager::logDevicesList() const
    {
        if(deviceListIsEmpty())
            return {Status::Cancelled,"List is empty!"};

        console_logger->log(logger::Info, "Listing devices...");
        for(const auto& device : devices)
        {
            console_logger->log(
                    logger::Info,
                    std::format("{},{}",device.getIdx(),device.getNickName()));
        }
        return Result(Status::Success);
    }

    std::optional<int> device_manager::findDeviceIndex(std::vector<device> _devices, int device_id)
    {
        const auto it = std::ranges::find_if(_devices,
        [device_id] (const device& device) -> bool{
            return device.getIdx() == device_id;
        });

        if(it != _devices.end())
        {
            return std::distance(_devices.begin(), it);
        }
        return std::nullopt;
    }



    std::optional<device> device_manager::getDevice(const int device_id)
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

    bool device_manager::selectedListIsEmpty() const
    {
        return selected_devices.empty();
    }

    bool device_manager::selectDevice(const int device_id)
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

    bool device_manager::deselectDevice(int device_id)
    {
        if(!checkDevice(device_id))
            return false;
        const auto it = std::ranges::find_if(selected_devices,
        [device_id] (const device& device) -> bool
        {
            return device.getIdx() == device_id;
        });

        if(it != std::end(devices))
        {
            devices.erase(it);
            return true;
        }
        return false;
    }

    void device_manager::clearSelectedList()
    {
        selected_devices.clear();
    }

    std::vector<device> device_manager::getSelectedDeviceList() const{
        return selected_devices;
    }


    bool device_manager::updateDevice(device* device){
        std::optional<int> index = findDeviceIndex(devices, device->getIdx());
        if(!index)
            return false;

        //TODO this area will be filled 
        return false;
    }

    bool device_manager::checkDevice(const int device_id)
    {
        return !freenect2.getDeviceSerialNumber(device_id).empty();
    }

    bool device_manager::startDevice(const int device_id) {
        if(!checkDevice(device_id))
            return false;

         auto device = freenect2.openDevice(device_id);
         if(device == nullptr){
            return false;
         }

        return true;

    }




}
