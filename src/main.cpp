#include "../cmake-build-debug/_deps/catch2-src/single_include/catch2/catch.hpp"
#include "device/device_manager.h"
#include "logger/console_logger.h"

using namespace vision;

DeviceManager* device_manager = DeviceManager::getInstance();
ConsoleLogger* console_logger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{


    //device_manager->openDevices(device_manager->getDeviceList());

    console_logger->log(Logger::Info, "Vision Finised.");
    return 0;
}