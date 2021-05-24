#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

#include <utility.hpp>
#include <Token.hpp>

namespace noscript
{
    class Error
    {
    private:
        std::string m_ErrorMessage;
        std::string m_ErrorHeader;
        Token m_TokenFound;
        Token m_TokenExpected;

    public:
        Error() = delete;
        Error(const std::string &) noexcept;
        Error(const std::string &, const std::string &) noexcept;
        Error(const std::string &, const std::string &, const Token &, const Token &) noexcept;
        
        [[nodiscard]] auto ToString() const noexcept -> std::string;
    };
}

#endif