#ifndef PREFIX_PARSE_FUNCTIONS_HPP
#define PREFIX_PARSE_FUNCTIONS_HPP

#include <Node.hpp>
#include <Parser.hpp>

namespace noscript
{
    auto
    ParseIdentifier(Parser &p_parser) noexcept -> Expression *;

    auto
    ParseInteger(Parser &p_parser) noexcept -> Expression *;

    auto
    ParsePrefixExpression(Parser &p_parser) noexcept -> Expression *;
}

#endif