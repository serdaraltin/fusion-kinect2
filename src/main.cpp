#include "device/device_manager.h"
#include "libfreenect2/logger.h"
#include "logger/console_logger.h"
#include "debug/status.h"
#include "device/device.h"

using namespace vision;

DeviceManager* device_manager = DeviceManager::getInstance();
ConsoleLogger* console_logger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{
    /* libfreenect2::Freenect2DeviceManager *DeviceManager;
     libfreenect2::PacketPipeline *pipeline;*/

    auto list_result = device_manager->listDevices(device_manager->getDeviceList());



    console_logger->log(Logger::Info, "Vision Finised.");
    return 0;
}