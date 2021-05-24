#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <Token.hpp>
#include <Node.hpp>

namespace noscript
{
    class Identifier : public Expression
    {
    public:
        [[nodiscard]] auto TokenLiteral() -> std::string { return m_Token.m_TokenLiteral; }

        Token m_Token;
        std::string m_Value;
    };
}

#endif