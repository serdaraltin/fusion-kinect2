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
 * Stores the ID and serial number of each device.
 */
namespace vision
{
    class Device
    {
    private:
        int idx = -1;
        std::string serial;
        std::string nick_name;
        bool open_status = false;
        libfreenect2::Freenect2Device* kinect2 = nullptr;

    public:
        Device();

        //Device(const Device& other);

        ~Device() = default;

        explicit Device(int idx)
            : idx(idx)
        {
        }

        Device(int idx, const std::string& serial)
            : idx(idx),
              serial(serial)
        {
        }

        Device(int idx, const std::string& serial, const std::string& nick_name)
            : idx(idx),
              serial(serial),
              nick_name(nick_name)
        {
        }

        Device(int idx, const std::string& serial, const std::string& nick_name, libfreenect2::Freenect2Device* kinect2)
            : idx(idx),
              serial(serial),
              nick_name(nick_name),
              kinect2(kinect2)
        {
        }

        Device(int idx, const std::string& serial, const std::string& nick_name, bool open_status,
            libfreenect2::Freenect2Device* kinect2)
            : idx(idx),
              serial(serial),
              nick_name(nick_name),
              open_status(open_status),
              kinect2(kinect2)
        {
        }
        Device operator=(const Device& other) {
            if (this == &other){
                return *this;
            }

            this->idx = other.idx;
            this->nick_name = other.nick_name;
            this->open_status = other.open_status;
            this->kinect2 = other.kinect2;
            return *this;
        }
        friend bool operator==(const Device& lhs, const Device& rhs)
        {
            return lhs.idx == rhs.idx
                && lhs.nick_name == rhs.nick_name
                && lhs.open_status == rhs.open_status
                && lhs.kinect2 == rhs.kinect2;
        }

        friend bool operator!=(const Device& lhs, const Device& rhs)
        {
            return !(lhs == rhs);
        }

        explicit operator bool() const
        {
            return kinect2 != nullptr;
        }

        [[nodiscard]] int getIdx() const
        {
            return idx;
        }

        [[nodiscard]] std::string getNickName() const
        {
            return nick_name;
        }

        [[nodiscard]] bool isOpen() const
        {
            return open_status;
        }

        [[nodiscard]] libfreenect2::Freenect2Device* getKinect2() const
        {
            return kinect2;
        }

        [[nodiscard]] std::string getSerial() const
        {
            return serial;
        }

        void setSerial(const std::string& serial)
        {
            this->serial = serial;
        }

        void setIdx(const int idx)
        {
            this->idx = idx;
        }

        void setNickName(const std::string& nick_name)
        {
            this->nick_name = nick_name;
        }

        void setOpen(const bool open_status)
        {
            this->open_status = open_status;
        }

        void setKinect2(libfreenect2::Freenect2Device* kinect2)
        {
            this->kinect2 = kinect2;
        }

    };
}

#endif // DEVICE_H
