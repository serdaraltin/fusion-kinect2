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
        int id = -1;
        std::string nick_name;
        bool open_status = false;
        libfreenect2::Freenect2Device* kinect2 = nullptr;

    public:
        Device();

        //Device(const Device& other);

        ~Device() = default;

        Device(const int id, std::string  nick_name)
            : id(id), nick_name(std::move(nick_name)){}

        Device(const int id, std::string  nick_name, const bool open_status, libfreenect2::Freenect2Device* kinect2)
            : id(id),nick_name(std::move(nick_name)),open_status(open_status),kinect2(kinect2){}

        Device(const int id, std::string  nick_name, libfreenect2::Freenect2Device* kinect2)
            : id(id),
              nick_name(std::move(nick_name)),
              kinect2(kinect2)
        {
        }

        friend bool operator==(const Device& lhs, const Device& rhs)
        {
            return lhs.id == rhs.id
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

        [[nodiscard]] int getId() const
        {
            return id;
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

        void setId(const int id)
        {
            this->id = id;
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
