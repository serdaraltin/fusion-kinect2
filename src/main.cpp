#include "device/device_manager.h"
#include "logger/console_logger.h"
#include <boost/foreach.hpp>
#include <iostream>

using namespace vision;

DeviceManager* device_manager = DeviceManager::getInstance();
ConsoleLogger* console_logger = ConsoleLogger::getInstance();

int main(int argc, char *argv[])
{
    std::string hello("Hello, world!");

    BOOST_FOREACH( char ch, hello){
        std:: cout << ch;
    }

    console_logger->log(Logger::Info, "Vision Finised.");
    return 0;
}

