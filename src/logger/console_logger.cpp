//
// Created by main on 19.09.2024.
//

#include <format>
#include <iostream>
#include <ostream>
#include "logger/console_logger.h"
#include "config/config.h"
#include "cxxabi.h"
#include "execinfo.h"
#include <dlfcn.h>
#include <cstring>

namespace vision
{

    console_logger* console_logger::instance;
    console_logger::console_logger()
    {
        level_ = Info;
        this->log(Info,"Console Logger initialized.");
    }

    console_logger* console_logger::getInstance()
    {
        if (instance == nullptr)
            instance = new console_logger();
        return instance;
    }
    std::string console_logger::getLevelString(Level level)
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

    void console_logger::log(Level level, const std::string& message)
    {
        if(level <= level_)
        {
            std::cout << std::format("[{}] [{}] {}",getLevelString(level), APP_NAME, message ) << std::endl;
        }

    }
}