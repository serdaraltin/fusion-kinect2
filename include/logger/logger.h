//
// Created by main on 19.09.2024.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace vision
{
    /**
     * @class Logger
     * @brief Abstract base class for logging utilities.
     *
     * This class provides an interface for logging messages at various
     * levels of severity. Derived classes should implement the log
     * method to handle logging functionality.
     */
    class logger {
    private:
    public:
        /**
         * @enum Level
         * @brief Enumeration representing logging levels.
         *
         * This enum defines different levels of logging, where higher
         * values correspond to more verbose output.
         */
        enum Level
        {
            None = 0,     ///< No logging.
            Error = 1,    ///< Error messages.
            Warning = 2,  ///< Warning messages.
            Info = 3,     ///< Informational messages.
            Debug = 4,    ///< Debug messages.
        };

        /**
         * @brief Default destructor.
         */
        virtual ~logger() = default;

        /**
         * @brief Log a message with a specific logging level.
         * @param level The logging level of the message.
         * @param message The message to log.
         */
        virtual void log(Level level, const std::string &message) = 0;

        /**
         * @brief Set the logging level.
         * @param level The logging level to set.
         */
        void setLevel(Level level);

        /**
         * @brief Get the default logging level.
         * @return The default logging level.
         */
        static Level getDefaultLevel();

        /**
         * @brief Convert a logging level to a string representation.
         * @param level The logging level to convert.
         * @return A string representation of the logging level.
         */
        static std::string getLevelString(Level level);

        /**
         * @brief Get the current logging level.
         * @return The current logging level.
         */
        Level getLevel() const;

    protected:
        Level level_; ///< Current logging level.
    };
}

#endif //LOGGER_H
