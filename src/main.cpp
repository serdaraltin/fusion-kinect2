#include "device/device_manager.h"
#include "logger/console_logger.h"

using namespace vision;

device_manager* device_manager = device_manager::getInstance();
console_logger* console_logger = console_logger::getInstance();

int main(int argc, char *argv[])
{
    console_logger->log(logger::Info, "Vision Finised.");
    return 0;
}

