#include <utility.hpp>

namespace noscript
{
    auto
    IsLetter(char p_byte) noexcept -> bool
    {
        return (p_byte >= 'a' && p_byte <= 'z') ||
               (p_byte >= 'A' && p_byte <= 'Z') ||
               (p_byte == '_');
    }

    auto
    IsDigit(char p_byte) noexcept -> bool
    {
        return (p_byte >= '0' && p_byte <= '9');
    }

    auto
    EnumAsString(noscript::TokenType p_token) noexcept -> std::string
    {
        switch (p_token)
        {
        case TokenType::TOKEN_IDENT:
            return "TokenType::TOKEN_IDENT";
        case TokenType::TOKEN_INT:
            return "TokenType::TOKEN_INT";
        case TokenType::TOKEN_ASSIGN:
            return "TokenType::TOKEN_ASSIGN";
        case TokenType::TOKEN_NOT:
            return "TokenType::TOKEN_NOT";
        case TokenType::TOKEN_AND:
            return "TokenType::TOKEN_AND";
        case TokenType::TOKEN_OR:
            return "TokenType::TOKEN_OR";
        case TokenType::TOKEN_PLUS:
            return "TokenType::TOKEN_PLUS";
        case TokenType::TOKEN_MINUS:
            return "TokenType::TOKEN_MINUS";
        case TokenType::TOKEN_ASTERISK:
            return "TokenType::TOKEN_ASTERISK";
        case TokenType::TOKEN_SLASH:
            return "TokenType::TOKEN_SLASH";
        case TokenType::TOKEN_LT:
            return "TokenType::TOKEN_LT";
        case TokenType::TOKEN_GT:
            return "TokenType::TOKEN_GT";
        case TokenType::TOKEN_EQ:
            return "TokenType::TOKEN_EQ";
        case TokenType::TOKEN_NEQ:
            return "TokenType::TOKEN_NEQ";
        case TokenType::TOKEN_GTE:
            return "TokenType::TOKEN_GTE";
        case TokenType::TOKEN_LTE:
            return "TokenType::TOKEN_LTE";
        case TokenType::TOKEN_FUNCTION:
            return "TokenType::TOKEN_FUNCTION";
        case TokenType::TOKEN_LET:
            return "TokenType::TOKEN_LET";
        case TokenType::TOKEN_TRUE:
            return "TokenType::TOKEN_TRUE";
        case TokenType::TOKEN_FALSE:
            return "TokenType::TOKEN_FALSE";
        case TokenType::TOKEN_IF:
            return "TokenType::TOKEN_IF";
        case TokenType::TOKEN_ELSE:
            return "TokenType::TOKEN_ELSE";
        case TokenType::TOKEN_RETURN:
            return "TokenType::TOKEN_RETURN";
        case TokenType::TOKEN_WHILE:
            return "TokenType::TOKEN_WHILE";
        case TokenType::TOKEN_COMMA:
            return "TokenType::TOKEN_COMMA";
        case TokenType::TOKEN_SEMICOLON:
            return "TokenType::TOKEN_SEMICOLON";
        case TokenType::TOKEN_LPAREN:
            return "TokenType::TOKEN_LPAREN";
        case TokenType::TOKEN_RPAREN:
            return "TokenType::TOKEN_RPAREN";
        case TokenType::TOKEN_LBRACE:
            return "TokenType::TOKEN_LBRACE";
        case TokenType::TOKEN_RBRACE:
            return "TokenType::TOKEN_RBRACE";
        case TokenType::TOKEN_ILLEGAL:
            return "TokenType::TOKEN_ILLEGAL";
        case TokenType::TOKEN_EOF:
            return "TokenType::TOKEN_EndOfFile";
        default:
            return "Unknown Token Type";
        }
    }
}