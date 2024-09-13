#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include <../include/libfreenect2/logger.h>
#include <fstream>

class FileLogger : public libfreenect2::Logger {
private:
    std::ofstream logfile_;
public:
    FileLogger(const char *filename);
    bool good() const;
    void log(Level level, const std::string &message) override;
};

#endif // FILE_LOGGER_HPP
