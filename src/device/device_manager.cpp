//
// Created by Serdar on 19.09.2024.
//

#include "device/device_manager.h"
#include "debug/status.h"
#include "device/device.h"
#include "config/config.h"

namespace vision
{
    DeviceManager* DeviceManager::instance = nullptr;


    DeviceManager::DeviceManager()
    {
        freenect2_device = nullptr;
        freenect2_pipeline = new libfreenect2::CpuPacketPipeline();

        const int deviceCount = freenect2.enumerateDevices();
        if (deviceCount == 0)
        {
            console_logger->log(Logger::Warning, "Device not found!");
            return;
        }
        for (int i = 0; i < deviceCount; i++)
        {
            device_list.emplace_back(i, std::format("{}-{}",DEFAULT_DEVICE_NAME,i));
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
        console_logger->log(Logger::Info, "Device manager started!");
        return device_list;
    }

    Device DeviceManager::getDevice(const int id)
    {
        for(const auto& device: getDeviceList())
        {
            if(device.getId() == id)
                return device;
        }
        return device_list.front();
    }

    Result DeviceManager::listDevices(const std::vector<Device> &devices) const
    {
        if(devices.empty())
            return {Status::InvalidParam, "List is empty!" };

        console_logger->log(Logger::Info, "Listing Devices");
        for(const auto& device : devices)
        {
            console_logger->log(Logger::Info,
                std::format("{}: {}", device.getNickName(), device.getId()));
        }
        return {Status::Success, "Listing is successfull."};
    }

    Result DeviceManager::openDevices(const std::vector<Device> &devices)
    {
        if(devices.empty())
            return {Status::InvalidParam, std::string("List is empty!")};

        console_logger->log(Logger::Info, "Opening Devices");
        for(auto device : devices)
        {
            freenect2_device = freenect2.openDevice(device.getKinect2()->getSerialNumber(), freenect2_pipeline);
            device.setOpen(freenect2_device);
            console_logger->log(Logger::Info,
                std::format("Device {}: {} is opened.",device.getId(),device.getKinect2()->getSerialNumber()));
        }

        return {Status::Success, "Device(s) opened."};
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
                    id ,getDevice(id).getKinect2()->getSerialNumber()) );
        }
        return {Status::Success, "DeviceManager selected."};;
    }

}
