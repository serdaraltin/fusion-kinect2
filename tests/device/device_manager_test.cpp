//
// Created by Serdar on 22.09.2024.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "device/device_manager.h"

namespace vision
{
    DeviceManager* manager1 = DeviceManager::getInstance();
    DeviceManager* manager2 = DeviceManager::getInstance();
    ConsoleLogger* console_logger = ConsoleLogger::getInstance();

    TEST_CASE("DeviceManager Singleton Instance", "[DeviceManager]") {

        REQUIRE(manager1 != nullptr);
        REQUIRE(manager2 != nullptr);
        REQUIRE(manager1 == manager2);
    }
}