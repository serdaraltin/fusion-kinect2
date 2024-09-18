//
// Created by main on 19.09.2024.
//

#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "logger.h"

class ConsoleLogger : public Logger {
private:
    ConsoleLogger();
    static ConsoleLogger *instance;
public:
    static ConsoleLogger* getInstance();
    static std::string getLevelString(Level level);
    void log(Level level, const std::string& message) override;

    ConsoleLogger(const ConsoleLogger &) = delete;
    ConsoleLogger &operator=(const ConsoleLogger &) = delete;

};


#endif //CONSOLE_LOGGER_H
