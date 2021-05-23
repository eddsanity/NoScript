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
        IDENT,
        INT,

        /*
            operators
        */
        ASSIGN,

        /*
            boolean operators
        */
        NOT,
        AND,
        OR,

        /*
            arithmetic operators
        */
        PLUS,
        MINUS,
        ASTERISK,
        SLASH,

        /*
            comparison operators
        */
        LT,
        GT,
        EQ,
        NEQ,
        GTE,
        LTE,

        /*
            keywords
        */
        FUNCTION,
        LET,
        TRUE,
        FALSE,
        IF,
        ELSE,
        RETURN,
        WHILE,

        /*
            Delimiters
        */
        COMMA,
        SEMICOLON,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,

        /*
            Other
        */
        EndOfFile,
        ILLEGAL
    };


    [[nodiscard]] auto
    LookupIdentifier(const std::string& lexeme) -> TokenType;

    const std::map<std::string, TokenType> keywords =
        {
            {"fn", TokenType::FUNCTION},
            {"let", TokenType::LET},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"if", TokenType::IF},
            {"else", TokenType::ELSE},
            {"while", TokenType::WHILE},
            {"return", TokenType::RETURN}};

    /*
        A token consists of a token type (TokenType) and a token literal (std::string) that expresses both the value and the type of the token.
    */
    class Token
    {
    public:
        Token() noexcept = default;
        Token(const TokenType&, const std::string &) noexcept;

        TokenType m_TokenType;
        std::string m_TokenLiteral;
    };
}

#endif