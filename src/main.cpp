#include "device/device.h"
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

     consoleLogger->log(Logger::Info, "Vision Finised.");
     return 0;
}