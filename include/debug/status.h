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
    enum class Status
    {
        Success,
        Error,
        Unsuccess,
        InvalidParam,
        PermissionDenied,
        NotFound,
        Timeout,
        Conflict,
        Pendind,
        Cancelled
    };

    struct Result
    {
        Status status;
        std::string message;
        std::optional<std::any> data;

        explicit Result(const Status stat)
            : status(stat), message("Undefined"), data(std::nullopt) {}
        Result(const Status stat, std::string  message)
            : status(stat), message(std::move(message)), data(std::nullopt) {}

        Result(const Status stat, std::string  message, std::any& extraData)
            : status(stat), message(std::move(message)), data(extraData) {}

        bool operator==(const Result& rhs) const
        {
            return  rhs.status == Status::Success;
        }

        explicit operator bool() const
        {
            return status == Status::Success;
        }
    };
}
#endif //STATUS_H
