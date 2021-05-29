#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest/doctest/doctest.h"
#include <Node.hpp>
#include <Token.hpp>
#include <Identifier.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>
#include <AST.hpp>


TEST_CASE("Testing the ParseLetStatement method") {
    std::string input = "let x = 5;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::LetStatement* let_stmt = dynamic_cast<noscript::LetStatement*>(parser.ParseLetStatement());
    CHECK(let_stmt->TokenBody() == "{TokenType::TOKEN_LET, let}");
    CHECK(let_stmt->m_IdentifierName->TokenBody() == "{TokenType::TOKEN_IDENT, x}");
    CHECK(let_stmt->m_IdentifierValue->TokenBody() == "{TokenType::TOKEN_INT, 5}");
}