#include "device/device_manager.h"
#include "logger/console_logger.h"

using namespace vision;

device_manager* device_manager = device_manager::getInstance();
ConsoleLogger* console_logger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{
    console_logger->log(logger::Info, "Vision Finised.");
    return 0;
}

