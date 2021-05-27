#ifndef PARSER_HELPERS_HPP
#define PARSER_HELPERS_HPP

#include <Parser.hpp>
#include <ParserTypes.hpp>
#include <PrefixParseFunctions.hpp>

namespace noscript
{
    Parser::Parser(Lexer *p_Lexer) noexcept
    {
        m_Lexer = p_Lexer;

        this->ConsumeToken();
        this->ConsumeToken();

        this->PutPrefix(TokenType::IDENT, ParseIdentifier);
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