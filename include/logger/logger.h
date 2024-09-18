//
// Created by main on 19.09.2024.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class Logger {
private:
public:
    enum Level
    {
        None = 0,
        Error = 1,
        Warning = 2,
        Info = 3,
        Debug = 4,
    };
    virtual ~Logger() = default;
    virtual void log(Level level, const std::string &message) = 0;
    void setLevel(Level level);
    static Level getDefaultLevel();
    static std::string getLevelString(Level level);
    Level getLevel() const;
protected:
    Level level_;

};



#endif //LOGGER_H
