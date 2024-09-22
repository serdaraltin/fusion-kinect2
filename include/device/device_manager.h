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
    /**
     * @class DeviceManager
     * @brief Class that manages devices.
     *
     * This class contains functions to list, open, and select devices.
     * It is designed using the Singleton design pattern.
     */
    class DeviceManager {
    private:
        /**
         * @struct Device
         * @brief Holds device information.
         *
         * Stores the ID and serial number of each device.
         */
        struct Device
        {
            int id; ///< Device ID.
            std::string serial; ///< Device serial number.

            /**
             * @brief Default constructor.
             *
             * Sets the ID to -1.
             */
            Device()
                : id(-1) {}

            /**
             * @brief Parameterized constructor.
             * @param id Device ID.
             * @param serial Device serial number.
             */
            Device(const int id, std::string serial)
                : id(id), serial(std::move(serial)) {}

            /**
             * @brief Equality operator.
             * @param other Other Device object.
             * @return true If the serial number is not empty.
             * @return false Otherwise.
             */
            bool operator==(const Device& other) const
            {
                return !other.serial.empty();
            }

            /**
             * @brief Boolean conversion operator.
             * @return true If the serial number is not empty, false otherwise.
             */
            explicit operator bool() const
            {
                return !serial.empty();
            }
        };

        ConsoleLogger* consoleLogger = ConsoleLogger::getInstance(); ///< Console logger instance.
        libfreenect2::Freenect2 freenect2; ///< Freenect2 library instance.
        int max_DeviceManager_num = 2; ///< Maximum number of Device Managers.
        std::vector<Device> deviceList; ///< List of devices.
        static DeviceManager* instance; ///< Singleton instance.
        DeviceManager(); ///< Private constructor.

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
        static Result openDevices(const std::vector<Device>& devices);

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

#endif //DeviceManager_H
