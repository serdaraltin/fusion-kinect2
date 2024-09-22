#include "device/device_manager.h"
#include "libfreenect2/logger.h"
#include "logger/console_logger.h"
#include "debug/status.h"

using namespace vision;

DeviceManager* DeviceManager::instance;
ConsoleLogger* ConsoleLogger::instance;

DeviceManager* DeviceManagerManager = DeviceManager::getInstance();
ConsoleLogger* consoleLogger = ConsoleLogger::getInstance();


int main(int argc, char *argv[])
{
    /* libfreenect2::Freenect2DeviceManager *DeviceManager;
     libfreenect2::PacketPipeline *pipeline;*/



    auto DeviceManagers = DeviceManagerManager->getDeviceList();

    /*std::vector<int> indexs = {0};
    auto selectDeviceManager = DeviceManagerManager->selectDeviceManagers(indexs);
    if(!selectDeviceManager.first)
    {
        consoleLogger->log(Logger::Error, selectDeviceManager.second);
    }*/

    consoleLogger->log(Logger::Info, "Vision Finised.");
    return 0;
}