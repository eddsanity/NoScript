#ifndef TOKEN_HPP
#define TOKEN_HPP

namespace nolang
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
        EOF,
        ILLEGAL
    };
}

#endif