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
    };

    class Statement : public Node
    {
    };

    class Expression : public Node
    {
    };
}

#endif