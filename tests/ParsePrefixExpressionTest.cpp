#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest/doctest/doctest.h"
#include <Node.hpp>
#include <Token.hpp>
#include <Identifier.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>
#include <AST.hpp>

TEST_CASE("Parse Prefix Expression with correct prefix MINUS operator and correct expression")
{
    std::string input = "-5;";
    std::string expect = "{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_INT, 5}}";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::PrefixExpression *prefix_expr = dynamic_cast<noscript::PrefixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(prefix_expr->TokenBody() == expect);
}

TEST_CASE("Parse Prefix Expression with correct prefix NOT operator and correct expression")
{
    std::string input = "!5;";
    std::string expect = "{TokenType::TOKEN_NOT,\n\t{TokenType::TOKEN_INT, 5}}";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::PrefixExpression *prefix_expr = dynamic_cast<noscript::PrefixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(prefix_expr->TokenBody() == expect);
}

TEST_CASE("Parse Prefix Expression with correct prefix MINUS operator, incorrect expression")
{
    std::string input = "-;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::PrefixExpression *prefix_expr = dynamic_cast<noscript::PrefixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(prefix_expr == nullptr);
}

TEST_CASE("Parse Prefix Expression with correct prefix NOT operator, incorrect expression")
{
    std::string input = "!;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::PrefixExpression *prefix_expr = dynamic_cast<noscript::PrefixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(prefix_expr == nullptr);
}

TEST_CASE("Parse Prefix Expression with correct MINUS operator, keyword as expression")
{
    std::string input = "-let;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::PrefixExpression *prefix_expr = dynamic_cast<noscript::PrefixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(prefix_expr == nullptr);
}

TEST_CASE("Parse Prefix Expression with corect NOT operator, keyword as expression")
{
    std::string input = "!let;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::PrefixExpression *prefix_expr = dynamic_cast<noscript::PrefixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(prefix_expr == nullptr);
}