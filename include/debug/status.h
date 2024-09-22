//
// Created by main on 22.09.2024.
//

#ifndef STATUS_H
#define STATUS_H

#include <any>
#include <optional>
#include <string>
#include <utility>

namespace vision
{
    /**
     * @enum Status
     * @brief Enumeration representing the status of operations.
     *
     * This enum defines various possible statuses that can occur during
     * operations in the application.
     */
    enum class Status
    {
        Success,          ///< Operation was successful.
        Unsuccess,       ///< Operation was unsuccessful.
        Error,           ///< An error occurred during operation.
        EmptyParam,      ///< Provided parameter is empty.
        EmptyData,       ///< Data is empty.
        InvalidParam,    ///< Provided parameter is invalid.
        PermissionDenied, ///< Access was denied due to permissions.
        NotFound,        ///< Requested item was not found.
        Timeout,         ///< Operation timed out.
        Conflict,        ///< A conflict occurred during the operation.
        Pending,         ///< Operation is still pending.
        Cancelled        ///< Operation was cancelled.
    };

    /**
     * @struct Result
     * @brief Struct to encapsulate the result of an operation.
     *
     * Contains the status of the operation, an associated message,
     * and optional data.
     */
    struct Result
    {
        Status status; ///< Status of the operation.
        std::string message; ///< Message providing additional information about the status.
        std::optional<std::any> data; ///< Optional data associated with the result.

        /**
         * @brief Constructor to create a Result with a status.
         * @param stat Status of the operation.
         */
        explicit Result(const Status stat)
            : status(stat), message("Undefined"), data(std::nullopt) {}

        /**
         * @brief Constructor to create a Result with a status and message.
         * @param stat Status of the operation.
         * @param message Message associated with the result.
         */
        Result(const Status stat, std::string message)
            : status(stat), message(std::move(message)), data(std::nullopt) {}

        /**
         * @brief Constructor to create a Result with a status, message, and extra data.
         * @param stat Status of the operation.
         * @param message Message associated with the result.
         * @param extraData Additional data to be stored in the result.
         */
        Result(const Status stat, std::string message, std::any& extraData)
            : status(stat), message(std::move(message)), data(extraData) {}

        /**
         * @brief Equality operator to compare Result objects.
         * @param rhs The Result object to compare against.
         * @return true if the status is Success; false otherwise.
         */
        bool operator==(const Result& rhs) const
        {
            return rhs.status == Status::Success;
        }

        /**
         * @brief Conversion operator to bool.
         * @return true if the status is Success; false otherwise.
         */
        explicit operator bool() const
        {
            return status == Status::Success;
        }
    };
}
#endif //STATUS_H
