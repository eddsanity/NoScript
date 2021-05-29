#include <PrefixParseFunctions.hpp>

namespace noscript
{
    auto
    ParseIdentifier(Parser &p_parser) noexcept -> Expression *
    {
        return new Identifier(p_parser.m_ParserCurrToken, p_parser.m_ParserCurrToken.m_TokenLiteral);
    }

    auto
    ParseInteger(Parser &p_parser) noexcept -> Expression *
    {
        IntegerLiteral *int64_literal = new IntegerLiteral(p_parser.m_ParserCurrToken);

        int64_t int64_value = 0;

        try
        {
            int64_value = std::stoi(int64_literal->TokenLiteral());
        }
        catch (std::invalid_argument)
        {
            p_parser.m_ErrorLogger.errlog("Couldn't parse integer");
            return nullptr;
        }

        int64_literal->m_Int64Value = int64_value;
        return int64_literal;
    }
}