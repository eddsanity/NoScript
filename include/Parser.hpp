#ifndef PARSER_HPP
#define PARSER_HPP

#include <Lexer.hpp>
#include <AST.hpp>
#include <map>
#include <Token.hpp>
#include <ErrorLogger.hpp>
#include <ParserTypes.hpp>

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

    class Parser
    {
    private:
        auto PutPrefix(TokenType, func_PrefixParse) -> void;
        auto PutInfix(TokenType, func_InfixParse) -> void;

        std::map<TokenType, func_PrefixParse> m_PrefixParseFunctions;
        std::map<TokenType, func_InfixParse> m_InfixParseFunctions;

    public:
        Parser() = delete;
        Parser(Parser &) = delete;
        Parser(Parser &&) = delete;
        Parser &operator=(Parser &) = delete;
        Parser &operator=(Parser &&) = delete;

        Parser(Lexer *p_Lexer) noexcept;
        auto ParseStatement() noexcept -> Statement *;
        auto ParseExpression(int) noexcept -> Expression *;
        auto ParseExpressionStatement() noexcept -> ExpressionStatement *;
        auto ParseLetStatement() noexcept -> Statement *;
        auto ParseRetStatement() noexcept -> Statement *;
        auto ParseProgram() noexcept -> Program *;

        auto ConsumeToken() noexcept -> void;

        ErrorLogger m_ErrorLogger;
        Token m_ParserCurrToken;
        Token m_ParserPeekToken;
        Lexer *m_Lexer;
    };
}

#endif