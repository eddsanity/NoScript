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
        Returns the keyword if it's a keyword, returns TokenType::TOKEN_IDENT if it isn't.
        Returning TokenType::TOKEN_IDENT signifies that the lexeme can be used as an identifier (variable name)
    */
    auto
    LookupIdentifier(const std::string &lexeme) -> TokenType
    {
        if (noscript::keywords.find(lexeme) == noscript::keywords.end())
            return TokenType::TOKEN_IDENT;
        return noscript::keywords.at(lexeme);
    }
}