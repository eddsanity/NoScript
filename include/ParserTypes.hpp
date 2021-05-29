#ifndef PARSER_TYPES_HPP
#define PARSER_TYPES_HPP

#include <functional>

#include <Node.hpp>

namespace noscript
{
    class Parser;
    /*
        PrefixParse takes no parameters as there are none to care for.
    */
    using func_PrefixParse = std::function<Expression*(Parser&)>;

    /*
        InfixParse takes an Expression because an infix operator has to care about the
        left-side expression.
    */
    using func_InfixParse = std::function<Expression*(Parser&, Expression*)>;
}

#endif