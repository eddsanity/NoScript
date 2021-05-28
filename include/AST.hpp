#ifndef AST_HPP
#define AST_HPP

#include <vector>
#include <ostream>

#include <Token.hpp>
#include <Node.hpp>
#include <Identifier.hpp>

namespace noscript
{
    using std::string;
    using std::vector;
    /*
        AST Root.
        NoScript, as a language, is a sequence of statements. Naturally, the "Program" is
        also primarily just a sequence (array) of statements. 
        Each statement _could_ have expressions in it, but an expression cannot have a statement in it.

        basically, 
        <Program> = <Statements>
        <Statements> = <Statement> ";" { <Statements> }
        <Statement>  = <LetStatement> |
                       <RetStatement> |
                       ..
    */
    class Program : public Node
    {
    public:
        auto TokenLiteral() -> string;
        auto ToString() -> string;

        vector<Statement *> m_Statements;

        ~Program() noexcept;
    };

    class ExpressionStatement : public Statement
    {
    public:
        auto TokenLiteral() -> string;
        auto ToString() -> string;

        Token m_Token;
        Expression *m_Expression;
    };

    class IntegerLiteral : public Expression
    {
    public:
        auto TokenLiteral() -> string;
        auto ToString() -> string;

        Token m_Token;
        int64_t m_Int64Value;
    };

    /*
        LetStatement Node
        A let statement strictly takes the format of `let <Identifier> = <Expression>`
        or, more formally, 

        <LetStatement> = "let" <Identifier> "=" <Expression>
        <Identifier> = <Letter> { <Letter> | <Digit> | <Underline> }
        <Expression> = ..
    */
    class LetStatement : public Statement
    {
    public:
        auto TokenLiteral() -> string;
        auto ToString() -> string;

        Token m_Token;
        Identifier *m_IdentifierName;
        Expression *m_IdentifierValue;
    };

    /*
        ReturnStatement Node
        A return statement is strictly the keyword 'return' and an expression that's evaluated and then the resulting literal
        value is returned.

        <RetStatement> = "return" <Expression>
    */
    class RetStatement : public Statement
    {
    public:
        auto TokenLiteral() -> string;
        auto ToString() -> string;

        Token m_Token;
        Expression *m_ReturnValue;
    };
}

#endif