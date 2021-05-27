#ifndef PREFIX_PARSE_FUNCTIONS_HPP
#define PREFIX_PARSE_FUNCTIONS_HPP

#include <Node.hpp>
#include <ParserTypes.hpp>
#include <Parser.hpp>

namespace noscript
{
    [[nodiscard]] auto
    ParseIdentifier(Parser& p_parser) noexcept -> Expression *;
}

#endif