#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest/doctest/doctest.h"
#include <Node.hpp>
#include <Token.hpp>
#include <Identifier.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>
#include <AST.hpp>


TEST_CASE("ParseRetStatement method with a constant integer value") {
    std::string input = "return 5;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::RetStatement* ret_stmt = dynamic_cast<noscript::RetStatement*>(parser.ParseRetStatement());
    CHECK(ret_stmt->TokenBody() == "{TokenType::TOKEN_RETURN, return}");
    CHECK(ret_stmt->m_ReturnValue->TokenBody() == "{TokenType::TOKEN_INT, 5}");
}

TEST_CASE("ParseRetStatement method with an identifier") {
    std::string input = "return x;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::RetStatement* ret_stmt = dynamic_cast<noscript::RetStatement*>(parser.ParseRetStatement());
    CHECK(ret_stmt->TokenBody() == "{TokenType::TOKEN_RETURN, return}");
    CHECK(ret_stmt->m_ReturnValue->TokenBody() == "{TokenType::TOKEN_IDENT, x}");
}

TEST_CASE("ParseRetStatement method with an invalid integer") {
    std::string input = "return x;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    parser.m_ParserPeekToken = noscript::Token(noscript::TokenType::TOKEN_INT, "non-integer-input");

    noscript::RetStatement* ret_stmt = dynamic_cast<noscript::RetStatement*>(parser.ParseRetStatement());
    CHECK(ret_stmt == nullptr);
}