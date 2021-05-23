#include <iostream>
#include <vector>
#include <utility.hpp>
#include <Token.hpp>
#include <Lexer.hpp>

auto main() -> int
{
    std::string lexer_input = "let num1 = 5;" \
                              "let num2 = 10;" \
                              "let add = fn(x, y) {" \
                              "    return x + y;" \
                              "};" \
                              " " \
                              "let result = add(num1, num2);" \
                              "if(result != num1 && num1 <= num2 || result >= num2) {" \
                              "    while(result != num1) {" \
                              "        num1 = num1 + 1;" \
                              "    }" \
                              "    return true;" \
                              "} else {" \
                              "    return false;" \
                              "}" \
                              " " \
                              "num1 = &num2;" \
                              "num2 = |num2;";
    noscript::Lexer lexer{lexer_input};
    std::vector<noscript::Token> tokens;
    
    for (auto curr_token = lexer.NextToken(); curr_token.m_TokenType != noscript::TokenType::EndOfFile; curr_token = lexer.NextToken())
    {
        // std::cout << "{" << noscript::EnumAsString(curr_token.m_TokenType) << ", \"" << curr_token.m_TokenLiteral << "\"}\n";
        tokens.push_back(curr_token);
    }
    return 0;
}