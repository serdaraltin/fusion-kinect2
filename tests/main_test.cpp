//
// Created by Serdar on 22.09.2024.
//

#include <gtest/gtest.h>
#include "device/device_manager.h"

namespace vision
{
    TEST(ConsoleLogger, getInstance){
        ConsoleLogger* console_logger1 = ConsoleLogger::getInstance();
        ConsoleLogger* console_logger2= ConsoleLogger::getInstance();
        EXPECT_NE(console_logger1, nullptr);
        EXPECT_NE(console_logger2, nullptr);
        EXPECT_EQ(console_logger1,console_logger2);
    }

    TEST(DeviceManager, getInstance) {
        DeviceManager* device_manager1 = DeviceManager::getInstance();
        DeviceManager* device_manager2 = DeviceManager::getInstance();
        EXPECT_NE(device_manager1, nullptr);
        EXPECT_NE(device_manager2, nullptr);
        EXPECT_EQ(device_manager1, device_manager2);
    }

    TEST(DeviceManager, availableDeviceCount) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        int freenect_enumerate = std::make_unique<libfreenect2::Freenect2>()->enumerateDevices();
        int dm_enumerate = device_manager->availableDeviceCount();
        EXPECT_EQ(dm_enumerate, freenect_enumerate);
    }

    TEST(DeviceManager, getDeviceList) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        int enum_device = device_manager->availableDeviceCount();
        unsigned int device_count = device_manager->getDeviceList().size();
        EXPECT_EQ(enum_device, device_count);
    }

    TEST(DeviceManager, logDeviceList) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        auto result = device_manager->logDevicesList();
        EXPECT_NE(result.status, Status::Error);
    }

    TEST(DeviceManager, deviceListIsEmpty) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        bool freenect_result = std::make_unique<libfreenect2::Freenect2>()->enumerateDevices();
        bool result = !device_manager->deviceListIsEmpty();
        EXPECT_EQ(freenect_result, result);
    }

    TEST(DeviceManager, refreshDeviceList) {
        DeviceManager* device_manager = DeviceManager::getInstance();
        int freenect_enumerate = std::make_unique<libfreenect2::Freenect2>()->enumerateDevices();
        device_manager->refreshDeviceList();
        int dm_enum = device_manager->availableDeviceCount();
        EXPECT_EQ(freenect_enumerate, dm_enum);
    }

    TEST(DeviceManager, getSelectedDeviceList){
        DeviceManager* device_manager = DeviceManager::getInstance();
        device_manager->clearSelectedList();
        EXPECT_TRUE(device_manager->getSelectedDeviceList().empty());

    }

    TEST(DeviceManager, selectDevice){
        DeviceManager* device_manager = DeviceManager::getInstance();
        if(!device_manager->availableDeviceCount()){
            GTEST_LOG_(INFO) << "Device not found !" << std::endl;
            GTEST_SKIP();
        }
        bool result = device_manager->selectDevice(device_manager->getDeviceList()[0].getIdx());
        EXPECT_TRUE(result);
    }

    TEST(DeviceManager, selectListIsEmpty){
        DeviceManager* device_manager = DeviceManager::getInstance();
        device_manager->clearSelectedList();
        EXPECT_TRUE(device_manager->selectedListIsEmpty());
    }

    TEST(DeviceManager, deselectDevice){
        DeviceManager* device_manager = DeviceManager::getInstance();
        if(!device_manager->availableDeviceCount()){
            GTEST_LOG_(INFO) << "Device not found !" << std::endl;
            GTEST_SKIP();
        }

        device_manager->selectDevice(device_manager->getDeviceList()[0].getIdx());
        bool result = device_manager->deselectDevice(0);
        EXPECT_TRUE(result);
    }

    TEST(DeviceManager, findDeviceIndex) {
        DeviceManager *device_manager = DeviceManager::getInstance();
        if(!device_manager->availableDeviceCount()){
            GTEST_LOG_(INFO) << "Device not found !" << std::endl;
            GTEST_SKIP();
        }
        auto device_list = device_manager->getDeviceList();
        std::optional<int> index = vision::DeviceManager::findDeviceIndex(device_list, 0);
        EXPECT_TRUE(index);
    }


    int main(int argc, char **argv){
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

}