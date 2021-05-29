#include <iostream>
#include <vector>
#include <utility.hpp>
#include <Token.hpp>
#include <Lexer.hpp>
#include <AST.hpp>
#include <Parser.hpp>

auto main() -> int
{
    // std::string lexer_input = "let num1 = 5;" \
    //                           "let num2 = 10;" \
    //                           "let add = fn(x, y) {" \
    //                           "    return x + y;" \
    //                           "};" \
    //                           " " \
    //                           "let result = add(num1, num2);" \
    //                           "if(result != num1 && num1 <= num2 || result >= num2) {" \
    //                           "    while(result != num1) {" \
    //                           "        num1 = num1 + 1;" \
    //                           "    }" \
    //                           "    return true;" \
    //                           "} else {" \
    //                           "    return false;" \
    //                           "}" \
    //                           " " \
    //                           "num1 = &num2;" \
    //                           "num2 = |num2;";

    // std::string lexer_input = "let x = 5;" \
    //                           "let y = 10;" \
    //                           "let foobar = 838383;" \
    //                           "return my_var;" \
    //                           "return 5050;" \
    //                           "return (e^x);";
    // std::string lexer_input = "foobar;" \
    //                           "x;" \
    //                           "5 + 6;";
    // noscript::Lexer lexer{lexer_input};
    // noscript::Parser parser(&lexer);

    // std::string input = "let x = 5;";
    // noscript::Lexer lexer(input);
    // noscript::Parser parser(&lexer);

    // noscript::LetStatement* stmt = dynamic_cast<noscript::LetStatement*>(parser.ParseLetStatement());
    // // auto let_stmt = dynamic_cast<noscript::LetStatement*>(parser.ParseLetStatement());
    // std::cout << stmt->TokenBody() << "\n";
    // std::cout << stmt->m_IdentifierName->TokenBody() << "\n";
    // std::cout << stmt->m_IdentifierValue->TokenBody() << "\n";

        std::string input = "return 5;";
    noscript::Lexer lexer(input);
    noscript::Parser parser(&lexer);

    noscript::RetStatement* ret_stmt = dynamic_cast<noscript::RetStatement*>(parser.ParseRetStatement());
    std::cout << ret_stmt->TokenBody();

    // auto program = parser.ParseProgram();

    // std::cout << "Aloooooooooo00oooooo\n";
    // for(auto& stmt : program->m_Statements)
    //     std::cout << stmt->TokenBody() << "\n";
    // std::cout << "IDENTIFIERS: \n";
    // for(auto& stmt : program->m_Statements)
    //     std::cout << stmt->TokenLiteral() << std::endl;

    // std::vector<noscript::Token> tokens;

    // for (auto curr_token = lexer.NextToken(); curr_token.m_TokenType != noscript::TokenType::EndOfFile; curr_token = lexer.NextToken())
    // {
    //     // std::cout << "{" << noscript::EnumAsString(curr_token.m_TokenType) << ", \"" << curr_token.m_TokenLiteral << "\"}\n";
    //     tokens.push_back(curr_token);
    // }

    // for(auto itr = tokens.cbegin(); itr != tokens.cend(); itr++)
    //     std::cout << "{" << noscript::EnumAsString((*itr).m_TokenType) << ", \"" << (*itr).m_TokenLiteral << "\"}\n";

    return 0;
}