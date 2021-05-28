#include <PrefixParseFunctions.hpp>

namespace noscript
{
    auto
    ParseIdentifier(Parser &p_parser) noexcept -> Expression *
    {
        return new Identifier(p_parser.m_ParserCurrToken, p_parser.m_ParserCurrToken.m_TokenLiteral);
    }
}