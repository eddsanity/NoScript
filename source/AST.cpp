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

    [[nodiscard]] auto
    LetStatement::TokenLiteral() -> string
    {
        return m_Token.m_TokenLiteral;
    }
}