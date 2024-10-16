/**
 * @file DeviceManager.h
 * @brief The DeviceManager class manages the Freenect2 devices.
 *
 * @details
 * This class interacts with the Freenect2 library to manage devices,
 * allowing for operations such as starting, stopping, and managing device states.
 * It provides functionality to list available devices and select them for use.
 * The class follows the Singleton design pattern.
 *
 * @namespace vision
 */

#ifndef DeviceManager_H
#define DeviceManager_H

#include "libfreenect2/libfreenect2.hpp"
#include "../logger/console_logger.hpp"
#include "../debug/status.hpp"
#include "device.hpp" // Device header
#include <optional>  // C++17 feature for optional return types
#include <gtest/gtest.h>


namespace vision
{

    /**
     * @class DeviceManager
     * @brief Class to manage Freenect2 devices.
     *
     * The DeviceManager class provides an interface for managing Freenect2 devices,
     * allowing interactions such as device enumeration, selection, and streaming control.
     */
    class device_manager {
    private:
        libfreenect2::Freenect2 freenect2; ///< Instance of the Freenect2 library.
        libfreenect2::Freenect2Device *freenect2_device = nullptr; ///< Device manager instance.
        libfreenect2::PacketPipeline *freenect2_pipeline = nullptr; ///< Packet pipeline instance.
        console_logger* console_logger = console_logger::getInstance(); ///< Logger instance.
        std::vector<device> devices; ///< List of devices.
        std::vector<device> selected_devices; ///< List of selected devices.
        static device_manager* instance; ///< Singleton instance.

        // Private constructor and destructor for Singleton pattern
        device_manager(); ///< Private constructor.
        ~device_manager() = default; ///< Default destructor.

        /**
         * @brief Creates a new device instance.
         *
         * @param device_id The ID of the device to create.
         * @return Device* Pointer to the newly created device.
         */
        device* createDevice(int device_id);

        /**
         * @brief Updates the specified device.
         *
         * @param device Pointer to the device to update.
         * @return bool True if the device was updated successfully, false otherwise.
         */
        bool updateDevice(device* device);

        /**
         * @brief Deletes the specified device.
         *
         * @param device Pointer to the device to delete.
         * @return bool True if the device was deleted successfully, false otherwise.
         */
        bool deleteDevice(device* device);

        /**
         * @brief Finds the index of a device in the given device list.
         *
         * @param _devices The list of devices to search.
         * @param device_id The ID of the device to find.
         * @return std::optional<int> The index of the device if found; otherwise, std::nullopt.
         */
        [[nodiscard]] static std::optional<int> findDeviceIndex(
                std::vector<device> _devices, int device_id);

        FRIEND_TEST(device_manager, findDeviceIndex); ///< Test friend declaration.

        /**
         * @brief Checks if a device with the given ID is valid.
         *
         * @param device_id The ID of the device to check.
         * @return bool True if the device is valid, false otherwise.
         */
        bool checkDevice(int device_id);

        FRIEND_TEST(device_manager, checkDevice); ///< Test friend declaration.

        /**
         * @brief Starts the specified device.
         *
         * @param device_id The ID of the device to start.
         * @return bool True if the device was started successfully, false otherwise.
         */
        bool startDevice(int device_id);

        /**
         * @brief Stops the specified device.
         *
         * @param device_id The ID of the device to stop.
         * @return bool True if the device was stopped successfully, false otherwise.
         */
        bool stopDevice(int device_id);

        /**
         * @brief Resets the specified device.
         *
         * @param device_id The ID of the device to reset.
         * @return bool True if the device was reset successfully, false otherwise.
         */
        bool resetDevice(int device_id);

        /**
         * @brief Opens the specified device.
         *
         * @param device_id The ID of the device to open.
         * @return bool True if the device was opened successfully, false otherwise.
         */
        bool openDevice(int device_id);

        /**
         * @brief Enumerates all available devices.
         *
         * @return std::vector<Device> A list of available devices.
         */
        std::vector<device> enumerateDevices();

    public:
        /**
         * @brief Gets the singleton instance of the DeviceManager.
         *
         * @return DeviceManager* Pointer to the singleton instance.
         */
        static device_manager* getInstance();

        device_manager(const device_manager&) = delete; ///< Deleting copy constructor.
        device_manager& operator=(const device_manager&) = delete; ///< Deleting copy assignment operator.

        /**
         * @brief Retrieves a device by its ID.
         *
         * @param device_id The ID of the device to retrieve.
         * @return std::optional<Device> The device if found; otherwise, std::nullopt.
         */
        std::optional<device> getDevice(int device_id);

        /**
         * @brief Gets the count of available devices.
         *
         * @return int The count of available devices.
         */
        [[nodiscard]] int availableDeviceCount();

        /**
         * @brief Gets the list of devices.
         *
         * @return std::vector<Device> A list of devices.
         */
        [[nodiscard]] std::vector<device> getDeviceList();

        /**
         * @brief Gets the list of selected devices.
         *
         * @return std::vector<Device> A list of selected devices.
         */
        [[nodiscard]] std::vector<device> getSelectedDeviceList() const;

        /**
         * @brief Logs the list of devices.
         *
         * @return Result The result of the logging operation.
         */
        [[nodiscard]] Result logDevicesList() const;

        /**
         * @brief Checks if the device list is empty.
         *
         * @return bool True if the device list is empty, false otherwise.
         */
        [[nodiscard]] bool deviceListIsEmpty() const;

        /**
         * @brief Refreshes the device list.
         *
         * @return Result The result of the refresh operation.
         */
        Result refreshDeviceList();

        // Selected list operations

        /**
         * @brief Selects a device by its ID.
         *
         * @param device_id The ID of the device to select.
         * @return bool True if the device was selected successfully, false otherwise.
         */
        bool selectDevice(int device_id);

        /**
         * @brief Deselects a device by its ID.
         *
         * @param device_id The ID of the device to deselect.
         * @return bool True if the device was deselected successfully, false otherwise.
         */
        bool deselectDevice(int device_id);

        /**
         * @brief Clears the selected device list.
         */
        void clearSelectedList();

        /**
         * @brief Checks if the selected device list is empty.
         *
         * @return bool True if the selected list is empty, false otherwise.
         */
        [[nodiscard]] bool selectedListIsEmpty() const;

        // Device-specific streaming and sensor data management

        /**
         * @brief Starts the video stream for a device.
         *
         * @param device_id The ID of the device to start streaming.
         * @return Result The result of the streaming operation.
         */
        Result startVideoStream(int device_id);

        /**
         * @brief Stops the video stream for a device.
         *
         * @param device_id The ID of the device to stop streaming.
         * @return Result The result of the operation.
         */
        Result stopVideoStream(int device_id);

        /**
         * @brief Starts the depth stream for a device.
         *
         * @param device_id The ID of the device to start depth streaming.
         * @return Result The result of the operation.
         */
        Result startDepthStream(int device_id);

        /**
         * @brief Stops the depth stream for a device.
         *
         * @param device_id The ID of the device to stop depth streaming.
         * @return Result The result of the operation.
         */
        Result stopDepthStream(int device_id);

        /**
         * @brief Enables the infrared stream for a device.
         *
         * @param device_id The ID of the device to enable IR streaming.
         * @return Result The result of the operation.
         */
        Result enableIRStream(int device_id);

        /**
         * @brief Disables the infrared stream for a device.
         *
         * @param device_id The ID of the device to disable IR streaming.
         * @return Result The result of the operation.
         */
        Result disableIRStream(int device_id);

        /**
         * @brief Captures a single frame from a device.
         *
         * @param device_id The ID of the device to capture the frame from.
         * @return Result The result of the capture operation.
         */
        Result captureFrame(int device_id);
    };

} // namespace vision

#endif // DeviceManager_H
