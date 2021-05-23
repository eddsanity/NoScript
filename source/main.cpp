#include <iostream>
#include <Token.hpp>
#include <Lexer.hpp>


auto main() -> int
{
    std::string lexer_input = "{ } ( ) + - / * , ;";
    nolang::Lexer lexer{lexer_input};
    
    for(auto curr_token = lexer.NextToken(); curr_token.m_TokenType != nolang::TokenType::EndOfFile; curr_token = lexer.NextToken())
    {
        std::cout << "current token is : " << curr_token.m_TokenLiteral << "\n";
    }
    return 0;
}