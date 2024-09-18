#include <format>
#include <iostream>
#include <memory>
#include "device/device.h"

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

int main(int argc, char *argv[])
{
     Device* deviceInstance = Device::getInstance();
     logPrint(deviceInstance->getDeviceList()[0], LogType::Info);

     libfreenect2::Freenect2Device *device;
     libfreenect2::PacketPipeline *pipeline;

     logPrint("Finished", LogType::Info);
     return 0;
}