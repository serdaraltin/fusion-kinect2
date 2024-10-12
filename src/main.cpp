#include "device/device_manager.h"
#include "logger/console_logger.h"

using namespace vision;

DeviceManager* device_manager = DeviceManager::getInstance();
ConsoleLogger* console_logger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{

    console_logger->log(Logger::Info, "Vision Finised.");
    return 0;
}

