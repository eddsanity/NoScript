#ifndef INFIX_PARSE_FUNCTIONS_HPP
#define INFIX_PARSE_FUNCTIONS_HPP

#include <Node.hpp>
#include <Parser.hpp>

namespace noscript
{
    auto
    parseInfixExpression(Parser &p_parser, Expression *p_LhsExpression) -> Expression *;
}

#endif