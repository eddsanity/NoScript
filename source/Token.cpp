#include <Token.hpp>

namespace noscript
{
    noscript::Token::Token(const TokenType &p_TokenType, const std::string &p_TokenLiteral) noexcept
    {
        this->m_TokenType = p_TokenType;
        this->m_TokenLiteral = p_TokenLiteral;
    }

    /*
        Determines whether a given lexeme is a keyword or not.
        Returns the keyword if it's a keyword, returns TokenType::IDENT if it isn't.
        Returning TokenType::IDENT signifies that the lexeme can be used as an identifier (variable name)
    */
    auto
    LookupIdentifier(const std::string &lexeme) -> TokenType
    {
        if (noscript::keywords.find(lexeme) == noscript::keywords.end())
            return TokenType::IDENT;
        return noscript::keywords.at(lexeme);
    }
}