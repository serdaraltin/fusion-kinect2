//
// Created by Serdar on 22.09.2024.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "device/device_manager.h"
#include "device/device.h"
#include "debug/status.h"


namespace vision
{
    TEST_CASE("DeviceManager Singleton Instance", "[DeviceManager]") {

        DeviceManager* manager1 = DeviceManager::getInstance();
        DeviceManager* manager2 = DeviceManager::getInstance();

        REQUIRE(manager1 != nullptr);
        REQUIRE(manager2 != nullptr);
        REQUIRE(manager1 == manager2);
    }
}