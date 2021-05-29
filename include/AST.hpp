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
        auto TokenBody() noexcept -> string;
        auto TokenLiteral() noexcept -> string;
        auto ToString() noexcept -> string;

        vector<Statement *> m_Statements;

        ~Program() noexcept;
    };

    /*
        ExpressionStatement Node
        An Expression Statement is an expression, used as a program statement.
        example: "5 + 5;". This, in the REPL, would output 10.
    */
    class ExpressionStatement : public Statement
    {
    public:
        auto TokenBody() noexcept -> string;
        auto TokenLiteral() noexcept -> string;
        auto ToString() noexcept -> string;

        Token m_Token;
        Expression *m_Expression;
    };

    /*
        IntegerLiteral Node
        An Integer Literal is an expression, containing a 64-bit integer value
    */
    class IntegerLiteral : public Expression
    {
    public:
        IntegerLiteral(Token p_Token) noexcept : m_Token(p_Token) {}
        auto TokenBody() noexcept -> string;
        auto TokenLiteral() noexcept -> string;
        auto ToString() noexcept -> string;

        Token m_Token;
        int64_t m_Int64Value;
    };

    class PrefixExpression : public Expression
    {
    public:
        PrefixExpression(Token p_Token, const string &p_Operator) noexcept : m_Token(p_Token), m_Operator(p_Operator) {}
        auto TokenBody() noexcept -> string;
        auto TokenLiteral() noexcept -> string;
        auto ToString() noexcept -> string;

        Token m_Token; /* Prefix Operator Token */
        string m_Operator;
        Expression *m_RhsExpression;
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
        auto TokenBody() noexcept -> string;
        auto TokenLiteral() noexcept -> string;
        auto ToString() noexcept -> string;

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
        auto TokenBody() noexcept -> string;
        auto TokenLiteral() noexcept -> string;
        auto ToString() noexcept -> string;

        Token m_Token;
        Expression *m_ReturnValue;
    };
}

#endif