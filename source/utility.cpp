#include <utility.hpp>

namespace nolang
{
    [[nodiscard]] auto
    IsLetter(char p_byte) noexcept -> bool
    {
        return (p_byte >= 'a' && p_byte <= 'z') ||
               (p_byte >= 'A' && p_byte <= 'Z') ||
               (p_byte == '_');
    }

    [[nodiscard]] auto
    IsDigit(char p_byte) noexcept -> bool
    {
        return (p_byte >= '0' && p_byte <= '9');
    }

    [[nodiscard]] auto
    EnumAsString(TokenType p_token) noexcept -> std::string
    {
        switch(p_token)
        {
            case TokenType::IDENT:
                return "TokenType::IDENT";
            case TokenType::INT:
                return "TokenType::INT";
            case TokenType::ASSIGN:
                return "TokenType::ASSIGN";
            case TokenType::NOT:
                return "TokenType::NOT";
            case TokenType::AND:
                return "TokenType::AND";
            case TokenType::OR:
                return "TokenType::OR";
            case TokenType::PLUS:
                return "TokenType::PLUS";
            case TokenType::MINUS:
                return "TokenType::MINUS";
            case TokenType::ASTERISK:
                return "TokenType::ASTERISK";
            case TokenType::SLASH:
                return "TokenType::SLASH";
            case TokenType::LT:
                return "TokenType::LT";
            case TokenType::GT:
                return "TokenType::GT";
            case TokenType::EQ:
                return "TokenType::EQ";
            case TokenType::NEQ:
                return "TokenType::NEQ";
            case TokenType::GTE:
                return "TokenType::GTE";
            case TokenType::LTE:
                return "TokenType::LTE";
            case TokenType::FUNCTION:
                return "TokenType::FUNCTION";
            case TokenType::LET:
                return "TokenType::LET";
            case TokenType::TRUE:
                return "TokenType::TRUE";
            case TokenType::FALSE:
                return "TokenType::FALSE";
            case TokenType::IF:
                return "TokenType::IF";
            case TokenType::ELSE:
                return "TokenType::ELSE";
            case TokenType::RETURN:
                return "TokenType::RETURN";
            case TokenType::WHILE:
                return "TokenType::WHILE";
            case TokenType::COMMA:
                return "TokenType::COMMA";
            case TokenType::SEMICOLON:
                return "TokenType::SEMICOLON";
            case TokenType::LPAREN:
                return "TokenType::LPAREN";
            case TokenType::RPAREN:
                return "TokenType::RPAREN";
            case TokenType::LBRACE:
                return "TokenType::LBRACE";
            case TokenType::RBRACE:
                return "TokenType::RBRACE";
            case TokenType::ILLEGAL:
                return "TokenType::ILLEGAL";
            case TokenType::EndOfFile:
                return "TokenType::EndOfFile";
        }
    }
}