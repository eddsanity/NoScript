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
            int64_value = std::stoi(int64_literal->TokenLiteral(), 0, 10);
        }
        catch (std::invalid_argument)
        {
            p_parser.m_ErrorLogger.errlog("Couldn't parse integer");
            return nullptr;
        }

        int64_literal->m_Int64Value = int64_value;
        return int64_literal;
    }

    auto
    ParsePrefixExpression(Parser &p_parser) noexcept -> Expression *
    {
        PrefixExpression *prefix_expr = new PrefixExpression(p_parser.m_ParserCurrToken, p_parser.m_ParserCurrToken.m_TokenLiteral);

        p_parser.ConsumeToken();

        prefix_expr->m_RhsExpression = p_parser.ParseExpression(PREFIX);

        return prefix_expr;
    }
}