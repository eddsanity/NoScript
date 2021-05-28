#include <ErrorLogger.hpp>

namespace noscript
{
    auto
    ErrorLogger::errlog(const std::string &p_ErrorMessage) noexcept -> void
    {
        m_ErrorLog.push_back(Error(p_ErrorMessage));
    }

    auto
    ErrorLogger::errlog(const std::string &p_ErrorHeader, const std::string &p_ErrorMessage) noexcept -> void
    {
        m_ErrorLog.push_back(Error(p_ErrorHeader, p_ErrorMessage));
    }

    auto
    ErrorLogger::errlog(const std::string &p_ErrorHeader, const std::string &p_ErrorMessage, const Token &p_ExpectedToken, const Token &p_ActualToken) noexcept -> void
    {
        m_ErrorLog.push_back(Error(p_ErrorHeader, p_ErrorMessage, p_ExpectedToken, p_ActualToken));
    }

    auto
    ErrorLogger::PrintErrLogs(std::ostream &p_outstream) const noexcept -> void
    {
        for (auto &err : m_ErrorLog)
            p_outstream << err.ToString();
    }

    auto
    ErrorLogger::GetErrLogs() const noexcept -> std::string
    {
        std::string output = "";
        for (auto &err : m_ErrorLog)
            output += err.ToString();
        return output;
    }

    auto
    ErrorLogger::GetFirstError() const noexcept -> std::string
    {
        if (m_ErrorLog.size() >= 1)
            return m_ErrorLog[0].ToString();
        return "";
    }

    auto
    ErrorLogger::GetMostRecentError() const noexcept -> std::string
    {
        if (m_ErrorLog.size() >= 1)
            return m_ErrorLog[m_ErrorLog.size() - 1].ToString();
        return "";
    }
}