//
// Created by Serdar on 22.09.2024.
//

#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <utility>

/**
 * @struct Device
 * @brief Holds device information.
 *
 * Stores the ID, serial number, nickname, open status, and device pointer of each device.
 */
namespace vision
{
    /**
     * @class Device
     * @brief Class representing a device.
     *
     * This class encapsulates the properties and functionalities related to a device,
     * including its identification, status, and associated resources.
     */
    class device
    {
    private:
        int idx = -1; ///< Device index.
        std::string serial; ///< Device serial number.
        std::string nick_name; ///< Device nickname.
        bool open_status = false; ///< Device open status.
        libfreenect2::Freenect2Device* kinect2 = nullptr; ///< Pointer to the Kinect2 device.

    public:
        /// Default constructor.
        device();

        /// Default destructor.
        ~device() = default;

        /**
         * @brief Constructs a Device with an index.
         *
         * @param idx The index of the device.
         */
        explicit device(int idx)
                : idx(idx)
        {
        }

        /**
         * @brief Constructs a Device with an index and serial number.
         *
         * @param idx The index of the device.
         * @param serial The serial number of the device.
         */
        device(int idx, std::string  serial)
                : idx(idx),
                  serial(std::move(serial))
        {
        }

        /**
         * @brief Constructs a Device with an index, serial number, and nickname.
         *
         * @param idx The index of the device.
         * @param serial The serial number of the device.
         * @param nick_name The nickname of the device.
         */
        device(int idx, std::string  serial, std::string  nick_name)
                : idx(idx),
                  serial(std::move(serial)),
                  nick_name(std::move(nick_name))
        {
        }

        /**
         * @brief Constructs a Device with an index, serial number, nickname, and Kinect2 pointer.
         *
         * @param idx The index of the device.
         * @param serial The serial number of the device.
         * @param nick_name The nickname of the device.
         * @param kinect2 Pointer to the Kinect2 device.
         */
        device(int idx, std::string  serial, std::string  nick_name, libfreenect2::Freenect2Device* kinect2)
                : idx(idx),
                  serial(std::move(serial)),
                  nick_name(std::move(nick_name)),
                  kinect2(kinect2)
        {
        }

        /**
         * @brief Constructs a Device with all attributes.
         *
         * @param idx The index of the device.
         * @param serial The serial number of the device.
         * @param nick_name The nickname of the device.
         * @param open_status The open status of the device.
         * @param kinect2 Pointer to the Kinect2 device.
         */
        device(int idx, std::string  serial, std::string  nick_name, bool open_status,
               libfreenect2::Freenect2Device* kinect2)
                : idx(idx),
                  serial(std::move(serial)),
                  nick_name(std::move(nick_name)),
                  open_status(open_status),
                  kinect2(kinect2)
        {
        }

        /**
         * @brief Assignment operator for Device.
         *
         * @param other The Device to copy.
         * @return Device& Reference to this device after assignment.
         */
        device operator=(const device& other) {
            if (this == &other){
                return *this;
            }

            this->idx = other.idx;
            this->nick_name = other.nick_name;
            this->open_status = other.open_status;
            this->kinect2 = other.kinect2;
            return *this;
        }

        /**
         * @brief Equality operator for comparing two devices.
         *
         * @param lhs The left-hand side device.
         * @param rhs The right-hand side device.
         * @return bool True if the devices are equal; false otherwise.
         */
        friend bool operator==(const device& lhs, const device& rhs)
        {
            return lhs.idx == rhs.idx
                   && lhs.nick_name == rhs.nick_name
                   && lhs.open_status == rhs.open_status
                   && lhs.kinect2 == rhs.kinect2;
        }

        /**
         * @brief Inequality operator for comparing two devices.
         *
         * @param lhs The left-hand side device.
         * @param rhs The right-hand side device.
         * @return bool True if the devices are not equal; false otherwise.
         */
        friend bool operator!=(const device& lhs, const device& rhs)
        {
            return !(lhs == rhs);
        }

        /**
         * @brief Converts the device to a boolean value.
         *
         * @return bool True if the Kinect2 pointer is not null; false otherwise.
         */
        explicit operator bool() const
        {
            return kinect2 != nullptr;
        }

        /**
         * @brief Gets the index of the device.
         *
         * @return int The index of the device.
         */
        [[nodiscard]] int getIdx() const
        {
            return idx;
        }

        /**
         * @brief Gets the nickname of the device.
         *
         * @return std::string The nickname of the device.
         */
        [[nodiscard]] std::string getNickName() const
        {
            return nick_name;
        }

        /**
         * @brief Checks if the device is open.
         *
         * @return bool True if the device is open; false otherwise.
         */
        [[nodiscard]] bool isOpen() const
        {
            return open_status;
        }

        /**
         * @brief Gets the Kinect2 device pointer.
         *
         * @return libfreenect2::Freenect2Device* Pointer to the Kinect2 device.
         */
        [[nodiscard]] libfreenect2::Freenect2Device* getKinect2() const
        {
            return kinect2;
        }

        /**
         * @brief Gets the serial number of the device.
         *
         * @return std::string The serial number of the device.
         */
        [[nodiscard]] std::string getSerial() const
        {
            return serial;
        }

        /**
         * @brief Sets the serial number of the device.
         *
         * @param serial The serial number to set.
         */
        void setSerial(const std::string& serial)
        {
            this->serial = serial;
        }

        /**
         * @brief Sets the index of the device.
         *
         * @param idx The index to set.
         */
        void setIdx(const int idx)
        {
            this->idx = idx;
        }

        /**
         * @brief Sets the nickname of the device.
         *
         * @param nick_name The nickname to set.
         */
        void setNickName(const std::string& nick_name)
        {
            this->nick_name = nick_name;
        }

        /**
         * @brief Sets the open status of the device.
         *
         * @param open_status The open status to set.
         */
        void setOpen(const bool open_status)
        {
            this->open_status = open_status;
        }

        /**
         * @brief Sets the Kinect2 device pointer.
         *
         * @param kinect2 Pointer to the Kinect2 device to set.
         */
        void setKinect2(libfreenect2::Freenect2Device* kinect2)
        {
            this->kinect2 = kinect2;
        }
    };
}

#endif // DEVICE_H
