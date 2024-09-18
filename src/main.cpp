#include <format>
#include <iostream>
#include <memory>

#include "libfreenect2/libfreenect2.hpp"



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
     }

     std::cout << std::format("[{}] [Vision] {}", stype, message) << std::endl;
}

class Device
{

private:
     libfreenect2::Freenect2 freenect2;
     int max_device_count = 2;
     std::array<std::string, sizeof(max_device_count)> device_list;

     static Device* instance;

     Device()
     {
          int deviceCount = freenect2.enumerateDevices() ;
          if(deviceCount == 0)
          {
               logPrint("No device found!", LogType::Warning);
          }

          for (int i = 0; i < deviceCount; i++)
               device_list[i] = freenect2.getDeviceSerialNumber(i);
     }
public:
     Device(const Device&) = delete;
     Device& operator=(const Device&) = delete;

     static Device* getInstance()
     {
          if(instance == nullptr)
          {
               instance = new Device();
          }
          return instance;
     }

     std::string getDeviceSerial(const int index)
     {
          return device_list[index];
     }

     std::array<std::string, sizeof(max_device_count)> getDeviceList()
     {
          return device_list;
     }

};

Device* Device::instance = nullptr;

int main(int argc, char *argv[])
{

     Device* deviceInstance = Device::getInstance();

     logPrint(Device::getInstance()->getDeviceList()[0], LogType::Info);

     libfreenect2::Freenect2Device *device;
     libfreenect2::PacketPipeline *pipeline;

     logPrint("Finished", LogType::Info);
     return 0;
}