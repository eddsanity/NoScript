#include <AST.hpp>

namespace noscript
{
    [[nodiscard]] auto
    Program::TokenLiteral() -> string
    {
        if (m_Statements.size() > 0)
            return m_Statements[0]->TokenLiteral();
        else
            return "";
    }

    Program::~Program() noexcept
    {
        for (auto stmt_ptr : m_Statements)
            delete stmt_ptr;
    }

    [[nodiscard]] auto
    LetStatement::TokenLiteral() -> string
    {
        return m_Token.m_TokenLiteral;
    }

    [[nodiscard]] auto
    RetStatement::TokenLiteral() -> string
    {
        return m_Token.m_TokenLiteral;
    }

}