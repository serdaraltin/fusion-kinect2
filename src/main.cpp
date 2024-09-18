#include <format>
#include <iostream>
#include "device/device.h"
#include "logger/console_logger.h"

enum LogType
{
     Info,
     Warning,
     Error
};

void logPrint(std::string message, LogType type)
{
     std::string stype = "Info";
     switch(type)
     {
          case Warning:
               stype = "Warning";
          case Error:
               stype = "Error";
          default:
               stype = "Undefined";
     }

     std::cout << std::format("[{}] [Vision] {}", stype, message) << std::endl;
}

Device* Device::instance;
ConsoleLogger* ConsoleLogger::instance;
Device* deviceInstance = Device::getInstance();
ConsoleLogger* consoleLogger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{

    /* libfreenect2::Freenect2Device *device;
     libfreenect2::PacketPipeline *pipeline;*/

     consoleLogger->log(Logger::Info, "Vision Finised.");
     return 0;
}