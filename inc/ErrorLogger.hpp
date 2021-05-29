#ifndef ERROR_LOGGER_HPP
#define ERROR_LOGGER_HPP

#include <Error.hpp>
#include <Token.hpp>
#include <string>
#include <vector>
#include <ostream>

namespace noscript
{
    class ErrorLogger
    {
    private:
        std::vector<noscript::Error> m_ErrorLog;

    public:
        ErrorLogger() noexcept = default;
        auto errlog(const std::string &) noexcept -> void;
        auto errlog(const std::string &, const std::string &) noexcept -> void;
        auto errlog(const std::string &, const std::string &, const Token &, const Token &) noexcept -> void;
        auto PrintErrLogs(std::ostream &) const noexcept -> void;
        auto GetErrLogs() const noexcept -> std::string;
        auto GetFirstError() const noexcept -> std::string;
        auto GetMostRecentError() const noexcept -> std::string;
    };
}

#endif