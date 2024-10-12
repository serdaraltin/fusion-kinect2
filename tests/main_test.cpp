//
// Created by Serdar on 22.09.2024.
//

#include <gtest/gtest.h>
#include "device/device_manager.h"

namespace vision
{
    /**
     * @brief Tests the singleton instance of ConsoleLogger.
     *
     * This test verifies that multiple calls to getInstance return the same instance
     * and that it is not null.
     */
    TEST(ConsoleLogger, getInstance) {
        ConsoleLogger* console_logger1 = ConsoleLogger::getInstance();
        ConsoleLogger* console_logger2 = ConsoleLogger::getInstance();
        EXPECT_NE(console_logger1, nullptr);
        EXPECT_NE(console_logger2, nullptr);
        EXPECT_EQ(console_logger1, console_logger2);
    }

    /**
     * @brief Tests the singleton instance of DeviceManager.
     *
     * This test checks that multiple calls to getInstance return the same instance
     * and that it is not null.
     */
    TEST(DeviceManager, getInstance) {
        DeviceManager* device_manager1 = DeviceManager::getInstance();
        DeviceManager* device_manager2 = DeviceManager::getInstance();
        EXPECT_NE(device_manager1, nullptr);
        EXPECT_NE(device_manager2, nullptr);
        EXPECT_EQ(device_manager1, device_manager2);
    }

    /**
     * @brief Tests the available device count against the Freenect device count.
     *
     * This test compares the number of devices reported by the DeviceManager
     * with the number reported by the libfreenect2 library.
     */
    TEST(DeviceManager, availableDeviceCount) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        int freenect_enumerate = std::make_unique<libfreenect2::Freenect2>()->enumerateDevices();
        int dm_enumerate = device_manager->availableDeviceCount();
        EXPECT_EQ(dm_enumerate, freenect_enumerate);
    }

    /**
     * @brief Tests the retrieval of the device list.
     *
     * This test verifies that the device count from the DeviceManager matches
     * the size of the retrieved device list.
     */
    TEST(DeviceManager, getDeviceList) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        int enum_device = device_manager->availableDeviceCount();
        unsigned int device_count = device_manager->getDeviceList().size();
        EXPECT_EQ(enum_device, device_count);
    }

    /**
     * @brief Tests logging the device list.
     *
     * This test checks that logging the devices does not result in an error status.
     */
    TEST(DeviceManager, logDeviceList) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        auto result = device_manager->logDevicesList();
        EXPECT_NE(result.status, Status::Error);
    }

    /**
     * @brief Tests whether the device list is empty.
     *
     * This test verifies that the device list's emptiness matches the
     * enumeration result from the Freenect library.
     */
    TEST(DeviceManager, deviceListIsEmpty) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        bool freenect_result = std::make_unique<libfreenect2::Freenect2>()->enumerateDevices();
        bool result = !device_manager->deviceListIsEmpty();
        EXPECT_EQ(freenect_result, result);
    }

    /**
     * @brief Tests refreshing the device list.
     *
     * This test checks that the device count in DeviceManager is updated
     * after calling refreshDeviceList.
     */
    TEST(DeviceManager, refreshDeviceList) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        int freenect_enumerate = std::make_unique<libfreenect2::Freenect2>()->enumerateDevices();
        device_manager->refreshDeviceList();
        int dm_enum = device_manager->availableDeviceCount();
        EXPECT_EQ(freenect_enumerate, dm_enum);
    }

    /**
     * @brief Tests retrieving the selected device list.
     *
     * This test verifies that the selected device list is empty after clearing it.
     */
    TEST(DeviceManager, getSelectedDeviceList) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        device_manager->clearSelectedList();
        EXPECT_TRUE(device_manager->getSelectedDeviceList().empty());
    }

    /**
     * @brief Tests selecting a device.
     *
     * This test verifies that a device can be selected if devices are available.
     */
    TEST(DeviceManager, selectDevice) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        if (!device_manager->availableDeviceCount()) {
            GTEST_LOG_(INFO) << "Device not found!" << std::endl;
            GTEST_SKIP();
        }
        bool result = device_manager->selectDevice(device_manager->getDeviceList()[0].getIdx());
        EXPECT_TRUE(result);
    }

    /**
     * @brief Tests if the selected list is empty.
     *
     * This test checks that the selected list is indeed empty after clearing it.
     */
    TEST(DeviceManager, selectListIsEmpty) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        device_manager->clearSelectedList();
        EXPECT_TRUE(device_manager->selectedListIsEmpty());
    }

    /**
     * @brief Tests deselecting a device.
     *
     * This test verifies that a device can be deselected correctly
     * after it has been selected.
     */
    TEST(DeviceManager, deselectDevice) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        if (!device_manager->availableDeviceCount()) {
            GTEST_LOG_(INFO) << "Device not found!" << std::endl;
            GTEST_SKIP();
        }

        device_manager->selectDevice(device_manager->getDeviceList()[0].getIdx());
        bool result = device_manager->deselectDevice(0);
        EXPECT_TRUE(result);
    }

    /**
     * @brief Tests finding a device index.
     *
     * This test checks that the index of an existing device can be found in the device list.
     */
    TEST(DeviceManager, findDeviceIndex) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        if (!device_manager->availableDeviceCount()) {
            GTEST_LOG_(INFO) << "Device not found!" << std::endl;
            GTEST_SKIP();
        }
        auto device_list = device_manager->getDeviceList();

        std::optional<int> index = vision::DeviceManager::findDeviceIndex(device_list, device_list.front().getIdx());
        EXPECT_TRUE(index.has_value());
    }

    /**
     * @brief Tests checking the status of a device.
     *
     * This test verifies that a device's status can be checked successfully
     * if it exists in the device list.
     */
    TEST(DeviceManager, checkDevice) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        device_manager->enumerateDevices();
        if (!device_manager->availableDeviceCount()) {
            GTEST_LOG_(INFO) << "Device not found!" << std::endl;
            GTEST_SKIP();
        }
        auto device_list = device_manager->getDeviceList();
        bool result = device_manager->checkDevice(device_list.front().getIdx());
        EXPECT_TRUE(result);
    }

    /**
     * @brief The main function for running all tests.
     *
     * This function initializes Google Test and runs all test cases.
     *
     * @param argc Command line argument count.
     * @param argv Command line arguments.
     * @return int Result of the test execution.
     */
    int main(int argc, char **argv) {
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

}
