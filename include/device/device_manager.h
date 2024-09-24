#ifndef DeviceManager_H
#define DeviceManager_H

#include "libfreenect2/libfreenect2.hpp"
#include "logger/console_logger.h"
#include <format>
#include <utility>
#include "debug/status.h"
#include "device.h" // Include the new device header

namespace vision
{

    class DeviceManager {
    private:
        libfreenect2::Freenect2 freenect2; ///< Freenect2 library instance.
        libfreenect2::Freenect2Device *freenect2_device = nullptr; ///< Freenect2 library device manager instance.
        libfreenect2::PacketPipeline *freenect2_pipeline = nullptr; ///< Freenect2 library packet pipeline instance.
        ConsoleLogger* console_logger = ConsoleLogger::getInstance(); ///< Console logger instance.
        int max_DeviceManager_num = 2; ///< Maximum number of Device Managers.
        std::vector<Device> device_list; ///< List of devices.
        static DeviceManager* instance; ///< Singleton instance.
        DeviceManager(); ///< Private constructor.
        ~DeviceManager() = default; ///< Private default destructor.
    public:
        bool listIsEmpty() const;
        bool isDevice(int id) const;
        Result newDevice(int id);
        //Device getDevice(int id);
        Result updateDevice(Device* device);
        Result deleteDevice(Device* device);
        Result checkDevice(Device* device);
        Result startDevice(Device* device);
        Result stopDevice(Device* device);
        Result resetDevice(Device* device);
        static Device* castToDevice(const std::any& data);
        Result listDevices(const std::vector<Device>& devices) const;
        Result openDevices(const std::vector<Device>& devices);
        Result selectDevices(const std::vector<int>& id) const;
        static DeviceManager* getInstance();
        std::vector<Device> getDeviceList() const;
        DeviceManager(const DeviceManager&) = delete;
        DeviceManager& operator=(const DeviceManager&) = delete;
    };
}

#endif // DeviceManager_H
