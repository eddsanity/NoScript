#include <Error.hpp>

namespace noscript
{
    Error::Error(const std::string & p_ErrorMessage) noexcept
    {
        m_ErrorMessage = p_ErrorMessage;
    }

    Error::Error(const std::string & p_ErrorHeader, const std::string & p_ErrorMessage) noexcept
    {
        m_ErrorHeader = p_ErrorHeader;
        m_ErrorMessage = p_ErrorMessage;
    }

    Error::Error(const std::string & p_ErrorHeader, const std::string & p_ErrorMessage, const Token & p_ExpectedToken, const Token & p_ActualToken) noexcept
    {
        m_ErrorHeader = p_ErrorHeader;
        m_ErrorMessage = p_ErrorMessage;
        m_TokenExpected = p_ExpectedToken;
        m_TokenFound = p_ActualToken;
    }

    [[nodiscard]] auto
    Error::ToString() const noexcept -> std::string
    {
        return "-" + m_ErrorHeader + ": " 
                   + m_ErrorMessage
                   + ".\n\tExpected: " + EnumAsString(m_TokenExpected.m_TokenType)
                   + ", \tFound: " + EnumAsString(m_TokenFound.m_TokenType) + ".\n";
    }
}