#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest/doctest/doctest.h"
#include <Node.hpp>
#include <Token.hpp>
#include <Identifier.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>
#include <AST.hpp>

TEST_CASE("ParseLetStatement method with valid input")
{
    std::string input = "let x = 5;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::LetStatement *let_stmt = dynamic_cast<noscript::LetStatement *>(parser.ParseLetStatement());
    CHECK(let_stmt->TokenBody() == "{TokenType::TOKEN_LET, let}");
    CHECK(let_stmt->m_IdentifierName->TokenBody() == "{TokenType::TOKEN_IDENT, x}");
    CHECK(let_stmt->m_IdentifierValue->TokenBody() == "{TokenType::TOKEN_INT, 5}");
}

TEST_CASE("ParseLetStatement method with a missing identifier")
{
    std::string input = "let = 5;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::LetStatement *let_stmt = dynamic_cast<noscript::LetStatement *>(parser.ParseLetStatement());
    CHECK(let_stmt == nullptr);
}

TEST_CASE("ParseLetStatement method without an assignment operator")
{
    std::string input = "let x  5;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::LetStatement *let_stmt = dynamic_cast<noscript::LetStatement *>(parser.ParseLetStatement());
    CHECK(let_stmt == nullptr);
}

TEST_CASE("ParseLetStatement method with an invalid integer value on the right hand side")
{
    std::string input = "let x = 5;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    parser.m_ParserPeekToken = noscript::Token(noscript::TokenType::TOKEN_INT, "non-integer-input");
    
    noscript::LetStatement *let_stmt = dynamic_cast<noscript::LetStatement *>(parser.ParseLetStatement());
    CHECK(let_stmt == nullptr);
}