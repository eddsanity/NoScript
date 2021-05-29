#include <InfixParseFunctions.hpp>

namespace noscript
{
    auto
    parseInfixExpression(Parser &p_parser, Expression *p_LhsExpression) -> Expression *
    {
        InfixExpression *infix_expr = new InfixExpression(p_parser.m_ParserCurrToken, p_parser.m_ParserCurrToken.m_TokenLiteral, p_LhsExpression);

        auto precedence = LookupPrecedence(p_parser.m_ParserCurrToken.m_TokenType);

        p_parser.ConsumeToken();

        infix_expr->m_RhsExpression = p_parser.ParseExpression(precedence);

        if (infix_expr->m_RhsExpression == nullptr)
        {
            p_parser.m_ErrorLogger.errlog("Invalid r-operand: " + p_parser.m_ParserCurrToken.m_TokenLiteral);
            return nullptr;
        }

        return infix_expr;
    }
}