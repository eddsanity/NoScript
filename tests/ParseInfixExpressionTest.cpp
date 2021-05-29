#define DOCTEST_CONFIG_USE_STD_HEADERS

#include "doctest/doctest/doctest.h"
#include <Node.hpp>
#include <Token.hpp>
#include <Identifier.hpp>
#include <Lexer.hpp>
#include <Parser.hpp>
#include <AST.hpp>

TEST_CASE("Parse Infix Expression with correct MULTIPLY operator and operands")
{
    std::string input = "-11 * 12;";
    std::string expect = "{TokenType::TOKEN_ASTERISK,\n\t{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_INT, 11}}\n*\n\t{TokenType::TOKEN_INT, 12}}";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr->TokenBody() == expect);
}

TEST_CASE("Parse Infix Expression with correct DIVIDE operator and operands")
{
    std::string input = "-11 / 12;";
    std::string expect = "{TokenType::TOKEN_SLASH,\n\t{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_INT, 11}}\n/\n\t{TokenType::TOKEN_INT, 12}}";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr->TokenBody() == expect);
}

TEST_CASE("Parse Infix Expression with correct PLUS operator and operands")
{
    std::string input = "-11 + 12;";
    std::string expect = "{TokenType::TOKEN_PLUS,\n\t{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_INT, 11}}\n+\n\t{TokenType::TOKEN_INT, 12}}";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr->TokenBody() == expect);
}

TEST_CASE("Parse Infix Expression with correct MINUS operator and operands")
{
    std::string input = "-11 - 12;";
    std::string expect = "{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_INT, 11}}\n-\n\t{TokenType::TOKEN_INT, 12}}";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr->TokenBody() == expect);
}

TEST_CASE("Parse Infix Expression with correct PLUS operator and operands both with prefix operators")
{
    std::string input = "-11 + -12;";
    std::string expect = "{TokenType::TOKEN_PLUS,\n\t{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_INT, 11}}\n+\n\t{TokenType::TOKEN_MINUS,\n\t{TokenType::TOKEN_INT, 12}}}";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr->TokenBody() == expect);
}

TEST_CASE("Parse Infix Expression with correct PLUS operator and incorrect lhs operand")
{
    std::string input = "-let + 12;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr == nullptr);
}

TEST_CASE("Parse Infix Expression with correct PLUS operator and incorrect rhs operand")
{
    std::string input = "-11 + let;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr == nullptr);
}

TEST_CASE("Parse Infix Expression with correct PLUS operator and incorrect rhs operand")
{
    std::string input = "-11 + ;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr == nullptr);
}

TEST_CASE("Parse Infix Expression, messy input")
{
    std::string input = "- + ;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::InfixExpression *infix_expr = dynamic_cast<noscript::InfixExpression *>(parser.ParseExpression(noscript::LOWEST));
    CHECK(infix_expr == nullptr);
}