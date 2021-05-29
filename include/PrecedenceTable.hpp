#ifndef PRECEDENCE_TABLE_HPP
#define PRECEDENCE_TABLE_HPP

#include <Token.hpp>
#include <map>

namespace noscript
{
    enum ExpressionPrecedence
    {
        LOWEST = 0,
        EQUALS = 1,
        LESSGREATER = 2,
        ADD = 3,
        MUL = 4,
        PREFIX = 5,
        CALL = 6
    };

    const std::map<TokenType, int> PRECEDENCE_TABLE =
        {
            {TokenType::TOKEN_EQ, EQUALS},
            {TokenType::TOKEN_NEQ, EQUALS},
            {TokenType::TOKEN_LT, LESSGREATER},
            {TokenType::TOKEN_LTE, LESSGREATER},
            {TokenType::TOKEN_GT, LESSGREATER},
            {TokenType::TOKEN_GTE, LESSGREATER},
            {TokenType::TOKEN_PLUS, ADD},
            {TokenType::TOKEN_MINUS, ADD},
            {TokenType::TOKEN_SLASH, MUL},
            {TokenType::TOKEN_ASTERISK, MUL}};

    auto
    LookupPrecedence(TokenType p_TokenType) noexcept -> int;
}

#endif