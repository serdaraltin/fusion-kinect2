#include "log/FileLogger.hpp"

FileLogger::FileLogger(const char *filename) {
    if (filename) logfile_.open(filename);
    level_ = Debug;
}

bool FileLogger::good() const {
    return logfile_.is_open() && logfile_.good();
}

void FileLogger::log(Level level, const std::string &message) {
    logfile_ << "[" << level2str(level) << "] " << message << std::endl;
}
