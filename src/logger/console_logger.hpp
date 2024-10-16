//
// Created by Serdar on 19.09.2024.
//

#ifndef CONSOLE_LOGGER_H
#define CONSOLE_LOGGER_H

#include "logger.hpp"

namespace vision
{
    /**
     * @class ConsoleLogger
     * @brief Logger implementation that outputs messages to the console.
     *
     * This class derives from the Logger base class and implements
     * the log function to print messages to the standard output.
     */
    class console_logger : public logger {
    private:
        /**
         * @brief Private constructor for singleton implementation.
         */
        console_logger();

        /**
         * @brief Pointer to the singleton instance.
         */
        static console_logger *instance;

    public:
        /**
         * @brief Get the singleton instance of the ConsoleLogger.
         * @return Pointer to the ConsoleLogger instance.
         */
        static console_logger* getInstance();

        /**
         * @brief Convert a logging level to a string representation.
         * @param level The logging level to convert.
         * @return A string representation of the logging level.
         */
        static std::string getLevelString(Level level);

        /**
         * @brief Log a message with a specific logging level.
         * @param level The logging level of the message.
         * @param message The message to log.
         */
        void log(Level level, const std::string& message) override;

        /**
         * @brief Deleted copy constructor to prevent copying.
         */
        console_logger(const console_logger &) = delete;

        /**
         * @brief Deleted assignment operator to prevent assignment.
         */
        console_logger &operator=(const console_logger &) = delete;

    };
}

#endif //CONSOLE_LOGGER_H
