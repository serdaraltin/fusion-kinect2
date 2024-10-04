//
// Created by Serdar on 22.09.2024.
//

#include <gtest/gtest.h>
#include "device/device_manager.h"

namespace vision
{



    TEST(DeviceManager, SingletonInstance) {
        DeviceManager* manager1 = DeviceManager::getInstance();
        DeviceManager* manager2 = DeviceManager::getInstance();
        EXPECT_NE(manager1, nullptr);
        EXPECT_NE(manager2, nullptr);
        EXPECT_EQ(manager1, manager2);
    }

    TEST(ConsoleLogger, SingletonInstance){
        ConsoleLogger* console_logger1 = ConsoleLogger::getInstance();
        ConsoleLogger* console_logger2= ConsoleLogger::getInstance();
        EXPECT_NE(console_logger1, nullptr);
        EXPECT_NE(console_logger2, nullptr);
        EXPECT_EQ(console_logger1,console_logger2);
    }

    int main(int argc, char **argv){
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }

}