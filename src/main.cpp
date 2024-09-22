#include "device/device.h"
#include "libfreenect2/logger.h"
#include "logger/console_logger.h"

using namespace vision;

Device* Device::instance;
ConsoleLogger* ConsoleLogger::instance;

Device* deviceManager = Device::getInstance();
ConsoleLogger* consoleLogger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{
    /* libfreenect2::Freenect2Device *device;
     libfreenect2::PacketPipeline *pipeline;*/
    auto devices = deviceManager->getDeviceList();
    deviceManager->listDevices();
    std::vector<int> indexs = {0};
    auto selectDevice = deviceManager->selectDevices(indexs);
    if(!selectDevice.first)
    {
        consoleLogger->log(Logger::Error, selectDevice.second);
    }
    consoleLogger->log(Logger::Info, "Vision Finised.");
    return 0;
}