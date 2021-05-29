#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <map>
#include <string>

namespace noscript
{
    enum class TokenType
    {
        /*
            identifiers and literals
            only supported literal is of type int currently
        */
        TOKEN_IDENT,
        TOKEN_INT,

        /*
            operators
        */
        TOKEN_ASSIGN,

        /*
            boolean operators
        */
        TOKEN_NOT,
        TOKEN_AND,
        TOKEN_OR,

        /*
            arithmetic operators
        */
        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_ASTERISK,
        TOKEN_SLASH,

        /*
            comparison operators
        */
        TOKEN_LT,
        TOKEN_GT,
        TOKEN_EQ,
        TOKEN_NEQ,
        TOKEN_GTE,
        TOKEN_LTE,

        /*
            keywords
        */
        TOKEN_FUNCTION,
        TOKEN_LET,
        TOKEN_TRUE,
        TOKEN_FALSE,
        TOKEN_IF,
        TOKEN_ELSE,
        TOKEN_RETURN,
        TOKEN_WHILE,

        /*
            Delimiters
        */
        TOKEN_COMMA,
        TOKEN_SEMICOLON,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,

        /*
            Other
        */
        TOKEN_EOF,
        TOKEN_NOTSET,
        TOKEN_ILLEGAL
    };

    auto
    LookupIdentifier(const std::string &lexeme) -> TokenType;

    const std::map<std::string, TokenType> keywords =
        {
            {"fn", TokenType::TOKEN_FUNCTION},
            {"let", TokenType::TOKEN_LET},
            {"true", TokenType::TOKEN_TRUE},
            {"false", TokenType::TOKEN_FALSE},
            {"if", TokenType::TOKEN_IF},
            {"else", TokenType::TOKEN_ELSE},
            {"while", TokenType::TOKEN_WHILE},
            {"return", TokenType::TOKEN_RETURN}};

    /*
        A token consists of a token type (TokenType) and a token literal (std::string) that expresses both the value and the type of the token.
    */
    class Token
    {
    public:
        Token() noexcept = default;
        Token(const TokenType &, const std::string &) noexcept;

        TokenType m_TokenType;
        std::string m_TokenLiteral;
    };
}

#endif