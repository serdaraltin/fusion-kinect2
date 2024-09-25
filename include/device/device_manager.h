#ifndef DeviceManager_H
#define DeviceManager_H

#include "libfreenect2/libfreenect2.hpp"
#include "logger/console_logger.h"
#include "debug/status.h"
#include "device.h" // Device header
#include <optional>  // C++17 feature for optional return types

namespace vision
{

    class DeviceManager {
    private:
        libfreenect2::Freenect2 freenect2; ///< Freenect2 library instance.
        libfreenect2::Freenect2Device *freenect2_device = nullptr; ///< Freenect2 library device manager instance.
        libfreenect2::PacketPipeline *freenect2_pipeline = nullptr; ///< Freenect2 library packet pipeline instance.
        ConsoleLogger* console_logger = ConsoleLogger::getInstance(); ///< Console logger instance.
        std::vector<Device> devices; ///< List of devices.
        std::vector<Device> selected_devices;
        static DeviceManager* instance; ///< Singleton instance.

        // Private constructor and destructor for Singleton pattern
        DeviceManager();
        ~DeviceManager() = default;


        /*Device* createDevice(int device_id);
        bool updateDevice(Device* device);
        bool deleteDevice(Device* device);*/

        [[nodiscard]] static std::optional<int> findDeviceIndex(
            std::vector<Device> _devices, int device_id);


        bool checkDevice(int device_id);
        /*
        bool startDevice(int device_id);
        bool stopDevice(int device_id);
        bool resetDevice(int device_id);
        bool openDevice(int device_id);*/

        std::vector<Device> enumerateDevices();


    public:

        static DeviceManager* getInstance();

        DeviceManager(const DeviceManager&) = delete;
        DeviceManager& operator=(const DeviceManager&) = delete;

        std::optional<Device> getDevice(int device_id);
        //std::optional<Device> getDevice(std::string device_serial);
        [[nodiscard]] int availableDeviceCount();
        [[nodiscard]] std::vector<Device> getDeviceList() const;
        [[nodiscard]] Result logDevicesList() const;
        [[nodiscard]] bool deviceListIsEmpty() const;
        Result refreshDeviceList();

        // Selected List operations
        bool selectDevice(int device_id);
        //bool selectDevice(std::string device_serial);
        bool deselectDevice(int device_id);
        void clearSelectedList();
        [[nodiscard]] bool selectedListIsEmpty() const;


        // Device-specific streaming and sensor data management
        Result startVideoStream(int device_id);   // Start video stream
        Result stopVideoStream(int device_id);    // Stop video stream
        Result startDepthStream(int device_id);   // Start depth stream
        Result stopDepthStream(int device_id);    // Stop depth stream
        Result enableIRStream(int device_id);     // Enable IR stream
        Result disableIRStream(int device_id);    // Disable IR stream
        Result captureFrame(int device_id);       // Capture a single frame from device

    };


}

#endif // DeviceManager_H
