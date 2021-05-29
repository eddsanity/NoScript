#ifndef IDENTIFIER_HPP
#define IDENTIFIER_HPP

#include <Token.hpp>
#include <Node.hpp>
#include <utility.hpp>

namespace noscript
{
    class Identifier : public Expression
    {
    public:
        Identifier() = default;
        Identifier(Token p_Token, const std::string &p_TokenLiteral) noexcept : m_Token{p_Token}, m_Value{p_TokenLiteral} {}
        auto TokenBody() -> std::string { return "{" + noscript::EnumAsString(m_Token.m_TokenType) + ", " + m_Token.m_TokenLiteral + "}"; }
        auto TokenLiteral() -> std::string { return m_Token.m_TokenLiteral; }
        auto ToString() -> std::string { return m_Value; }
        Token m_Token;
        std::string m_Value;
    };
}

#endif