//
// Created by Serdar on 19.09.2024.
//

#ifndef DeviceManager_H
#define DeviceManager_H

#include "libfreenect2/libfreenect2.hpp"
#include "logger/console_logger.h"
#include <format>
#include <utility>
#include "debug/status.h"

namespace vision
{
    class DeviceManager {
    private:
        struct Device
        {
            int id;
            std::string serial;
            Device()
                :id(-1){}
            Device(const int id, std::string  serial)
                : id(id), serial(std::move(serial)) {}

            bool operator==(const Device& other) const
            {
                if(!other.serial.empty())
                    return true;
                return false;
            }
            explicit operator bool() const
            {
                return !serial.empty();
            }
        };
        ConsoleLogger* consoleLogger = ConsoleLogger::getInstance();
        libfreenect2::Freenect2 freenect2;
        int max_DeviceManager_num = 2;
        std::vector<Device> deviceList;
        static DeviceManager* instance;
        DeviceManager();
    public:
        [[nodiscard]] Result listDevices(const std::vector<Device> &devices) const;
        static Result openDevices(const std::vector<Device> &devices) ;
        Result selectDevices(const std::vector<int> &id);
        static DeviceManager* getInstance();
        std::vector<Device> getDeviceList();
        Device getDevice(int id);
        DeviceManager(const DeviceManager&) = delete;
        DeviceManager& operator=(const DeviceManager&) = delete;
    };
}

#endif //DeviceManager_H
