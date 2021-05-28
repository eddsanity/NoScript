#ifndef LEXER_HPP
#define LEXER_HPP

#include <cstdint>
#include <string>

#include <Token.hpp>
#include <utility.hpp>

namespace noscript
{

    /*
        Lexer currently has 4 member variables, 
            m_LexerInput is the line of code or the body of code the lexer is currently processing. 
                Plan to turn this into an std::istream in the future.
            m_LexerCurrPos is the current "file pointer" position before the look-ahead.
                basically the position of m_LexerChar.
            m_LexerPeekPos is the look-ahead "file pointer" position.
                Used to look ahead from the current character to determine what looks ahead, in multiple-character wide tokens
                (operators '==' '!=' etc, identifiers)
            m_LexerChar is the current character being processed.
    */
    class Lexer
    {
    private:
        // advance the "file pointers" by consuming characters
        auto ConsumeChar() noexcept -> void;
        // skip over space or space-like characters since they carry no significance in noscript
        auto ConsumeSpace() noexcept -> void;
        auto ReadWord() noexcept -> std::string;
        auto ReadInteger() noexcept -> std::string;
        auto Lookahead() const noexcept -> char;

    public:
        Lexer() = delete;
        Lexer(Lexer &&) = delete;
        Lexer &operator=(Lexer &&) = delete;

        Lexer(const std::string &) noexcept;

        auto NextToken() noexcept -> noscript::Token;

        std::string m_LexerInput;
        uint32_t m_LexerCurrPos;
        uint32_t m_LexerPeekPos;
        char m_LexerChar;
    };
}

#endif