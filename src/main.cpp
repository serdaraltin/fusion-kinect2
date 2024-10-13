#include "device/device_manager.hpp"
#include "logger/console_logger.hpp"


using namespace vision;

DeviceManager* device_manager = DeviceManager::getInstance();
ConsoleLogger* console_logger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{
    console_logger->log(Logger::Info, "Vision Finised.");
    return 0;
}

