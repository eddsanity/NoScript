#ifndef NODE_HPP
#define NODE_HPP

#include <string>

namespace noscript
{
    class Node
    {
    public:
        virtual std::string TokenBody() = 0;
        virtual std::string TokenLiteral() = 0;
        virtual std::string ToString() = 0;
        virtual ~Node() = default;
    };

    class Statement : public Node
    {
    };

    class Expression : public Node
    {
    };
}

#endif