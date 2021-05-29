#ifndef PARSER_HELPERS_HPP
#define PARSER_HELPERS_HPP

#include <Parser.hpp>
#include <ParserTypes.hpp>
#include <PrefixParseFunctions.hpp>
#include <InfixParseFunctions.hpp>

namespace noscript
{
    Parser::Parser(Lexer *p_Lexer) noexcept
    {
        m_Lexer = p_Lexer;

        this->ConsumeToken();
        this->ConsumeToken();

        this->PutPrefix(TokenType::TOKEN_IDENT, ParseIdentifier);
        this->PutPrefix(TokenType::TOKEN_INT, ParseInteger);
        this->PutPrefix(TokenType::TOKEN_NOT, ParsePrefixExpression);
        this->PutPrefix(TokenType::TOKEN_MINUS, ParsePrefixExpression);

        this->PutInfix(TokenType::TOKEN_PLUS, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_MINUS, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_SLASH, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_ASTERISK, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_EQ, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_NEQ, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_LT, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_LTE, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_GT, parseInfixExpression);
        this->PutInfix(TokenType::TOKEN_GTE, parseInfixExpression);
    }

    auto
    Parser::ConsumeToken() noexcept -> void
    {
        m_ParserCurrToken = m_ParserPeekToken;
        m_ParserPeekToken = m_Lexer->NextToken();
    }

    auto
    Parser::PutPrefix(TokenType p_TokenType, func_PrefixParse p_PrefixParseFunc) -> void
    {
        m_PrefixParseFunctions[p_TokenType] = p_PrefixParseFunc;
    }

    auto
    Parser::PutInfix(TokenType p_TokenType, func_InfixParse p_InfixParseFunc) -> void
    {
        m_InfixParseFunctions[p_TokenType] = p_InfixParseFunc;
    }
}

#endif