#include <PrecedenceTable.hpp>

namespace noscript
{
    auto
    LookupPrecedence(TokenType p_TokenType) noexcept -> int
    {
        if (PRECEDENCE_TABLE.find(p_TokenType) == PRECEDENCE_TABLE.end())
            return LOWEST;

        return PRECEDENCE_TABLE.at(p_TokenType);
    }
}