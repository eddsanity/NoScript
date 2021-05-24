#ifndef PARSER_HPP
#define PARSER_HPP

#include <Lexer.hpp>
#include <AST.hpp>
#include <Token.hpp>
#include <ErrorLogger.hpp>

namespace noscript
{
    class Parser
    {
    private:
        auto ConsumeToken() noexcept -> void;
        [[nodiscard]] auto ParseStatement() noexcept -> Statement *;
        [[nodiscard]] auto ParseLetStatement() noexcept -> Statement *;
        [[nodiscard]] auto ParseRetStatement() noexcept -> Statement *;
        [[nodiscard]] auto ParseIdentifier() noexcept -> Identifier *;
        [[nodiscard]] auto ParseExpression() noexcept -> Expression *;

    public:
        Parser() = delete;
        Parser(Parser &) = delete;
        Parser(Parser &&) = delete;
        Parser &operator=(Parser &) = delete;
        Parser &operator=(Parser &&) = delete;

        Parser(Lexer *p_Lexer) noexcept;
        [[nodiscard]] auto ParseProgram() noexcept -> Program *;

        Token m_ParserCurrToken;
        Token m_ParserPeekToken;
        Lexer *m_Lexer;
        ErrorLogger m_ErrorLogger;
    };
}

#endif