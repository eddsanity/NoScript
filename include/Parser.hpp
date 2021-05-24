#ifndef PARSER_HPP
#define PARSER_HPP

#include <Lexer.hpp>
#include <AST.hpp>
#include <Token.hpp>

namespace noscript
{
    class Parser
    {
    private:
        auto ConsumeToken() noexcept -> void;

    public:
        Parser() = delete;
        Parser(Parser &) = delete;
        Parser(Parser &&) = delete;
        Parser &operator=(Parser &) = delete;
        Parser &operator=(Parser &&) = delete;

        Parser(Lexer *p_Lexer) noexcept;
        auto ParseProgram() noexcept -> Program *;

        Token m_ParserCurrToken;
        Token m_ParserPeekToken;
        unique_ptr<Lexer> m_Lexer;
    };
}

#endif