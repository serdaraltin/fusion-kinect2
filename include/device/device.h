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
struct Device
{
    int id; ///< Device ID.
    std::string serial; ///< Device serial number.

    /**
     * @brief Default constructor.
     *
     * Sets the ID to -1.
     */
    Device() : id(-1) {}

    /**
     * @brief Parameterized constructor.
     * @param id Device ID.
     * @param serial Device serial number.
     */
    Device(int id, std::string serial) : id(id), serial(std::move(serial)) {}

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

#endif // DEVICE_H
