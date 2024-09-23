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
    /**
     * @class DeviceManager
     * @brief Class that manages devices.
     *
     * This class contains functions to list, open, and select devices.
     * It is designed using the Singleton design pattern.
     */
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
        ~DeviceManager()= default; ///< Private default destructor.
    public:
        /**
         * @brief Function to list devices.
         * @param devices Vector of device information.
         * @return Result Status of the devices.
         */
        [[nodiscard]] Result listDevices(const std::vector<Device>& devices) const;

        /**
         * @brief Function to open devices.
         * @param devices List of devices to open.
         * @return Result Status of the operation.
         */
        Result openDevices(const std::vector<Device>& devices);

        /**
         * @brief Function to select specific devices.
         * @param id IDs of devices to be selected.
         * @return Result Status of the selection.
         */
        Result selectDevices(const std::vector<int>& id);

        /**
         * @brief Function to get the singleton instance.
         * @return DeviceManager* Pointer to the device manager instance.
         */
        static DeviceManager* getInstance();

        /**
         * @brief Function to get the list of devices.
         * @return std::vector<Device> List of devices.
         */
        std::vector<Device> getDeviceList();

        /**
         * @brief Function to get a specific device.
         * @param id Device ID.
         * @return Device Information of the relevant device.
         */
        Device getDevice(int id);

        /**
         * @brief Disables the copy constructor.
         */
        DeviceManager(const DeviceManager&) = delete;

        /**
         * @brief Disables the assignment operator.
         */
        DeviceManager& operator=(const DeviceManager&) = delete;
    };
}

#endif // DeviceManager_H
