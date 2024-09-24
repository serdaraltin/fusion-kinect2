//
// Created by Serdar on 19.09.2024.
//

#include "device/device_manager.h"

#include <algorithm>
#include <memory>

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

        if (const int device_count = freenect2.enumerateDevices(); device_count == 0)
        {
            console_logger->log(Logger::Warning, "Device not found!");
            return;
        }
    }



    bool DeviceManager::listIsEmpty() const
    {
        return device_list.empty();
    }

    bool DeviceManager::isDevice(const int id) const
    {
        for(auto& device : device_list)
        {
            if(device.getId() == id)
                return true;
        }
        return false;
    }

    DeviceManager* DeviceManager::getInstance()
    {
        if(instance == nullptr)
            instance = new DeviceManager();
        return instance;
    }
    Device* DeviceManager::castToDevice(const std::any& data)
    {
        try
        {
            return  std::any_cast<Device*>(data);
        }catch (const std::bad_any_cast&)
        {
            return nullptr;
        }
    }

    Result DeviceManager::newDevice(const int id)
    {
        if(freenect2.getDeviceSerialNumber(id).empty())
            return {Status::InvalidParam, "Device not found!"};
        if(isDevice(id))
            return {Status::Cancelled, "Device already exists."};
        device_list.emplace_back(
            id,
            freenect2.getDeviceSerialNumber(id),
            nullptr);

        return {Status::Success, "New device added."};
    }

   /* Device DeviceManager::getDevice(const int id)
    {
        if(listIsEmpty())
            return {};

        for(const auto& device : device_list)
        {
            if(device.getId() == id)
            {
                return device;
            }
        }

        return {};
    }*/

    Result DeviceManager::updateDevice(Device* device)
    {
        if(listIsEmpty())
            return {Status::Unsuccess, "Device list empty!"};

        return {Status::Success, "Operation is successfull."};
    }

    Result DeviceManager::deleteDevice(Device* device)
    {
        return {Status::Success, "Operation is successfull."};
    }

    Result DeviceManager::checkDevice(Device* device)
    {
        return {Status::Success, "Operation is successfull."};
    }

    Result DeviceManager::startDevice(Device* device)
    {
        return {Status::Success, "Operation is successfull."};
    }

    Result DeviceManager::stopDevice(Device* device)
    {
        return {Status::Success, "Operation is successfull."};
    }

    Result DeviceManager::resetDevice(Device* device)
    {
        return {Status::Success, "Operation is successfull."};
    }



    std::vector<Device> DeviceManager::getDeviceList() const
    {
        console_logger->log(Logger::Info, "Device manager started!");

        return device_list;
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
        /*for(auto device : devices)
        {
            std::unique_ptr<libfreenect2::Freenect2Device> new_device(
                freenect2.openDevice(device.getKinect2()->getSerialNumber(), freenect2_pipeline));


            getDeviceList().emplace_back(
                0,
                std::format("{}-{}",DEFAULT_DEVICE_NAME,getDeviceList().size()),
                std::move(new_device).get());

            device.setOpen(freenect2_device);
            console_logger->log(Logger::Info,
                std::format("Device {}: {} is opened.",device.getId(),device.getKinect2()->getSerialNumber()));
        }*/

        return {Status::Success, "Device(s) opened."};
    }

    Result DeviceManager::selectDevices(const std::vector<int> &ids) const
    {
        if (ids.empty())
            return   {Status::NotFound,"List is empty !"};
        else if (ids.size() > getDeviceList().size())
            return {Status::InvalidParam, "Invalid index size !"};

        for (const int id : ids)
        {
            if (id < 0)
                return {Status::InvalidParam, "Invalid index !"};
        }
        return {Status::Success, "DeviceManager selected."};;
    }

}
