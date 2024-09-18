//
// Created by main on 19.09.2024.
//

#include <format>
#include <iostream>
#include <ostream>

#include "logger/console_logger.h"

ConsoleLogger::ConsoleLogger()
{
    level_ = Info;
}

ConsoleLogger* ConsoleLogger::getInstance()
{
    if (instance == nullptr)
        instance = new ConsoleLogger();
    return instance;
}
std::string ConsoleLogger::getLevelString(Level level)
{
    switch (level)
    {
    case None: return "None";
    case Error: return "Error";
    case Warning: return "Warning";
    case Info: return "Info";
    case Debug: return "Debug";
    default: return "Unknown";
    }
}

void ConsoleLogger::log(Level level, const std::string& message)
{

    if(level <= level_)
    {
        std::cout << std::format("[{}] {}",getLevelString(level), message ) << std::endl;
    }
}
