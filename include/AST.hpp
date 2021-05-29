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
        
        In the context of a syntax tree, Program Node is the AST's ROOT node.
        It has many children, each of which is a subtree representing a singular statement.
        example: 
            5;
            10 * 11;
            let x = 13;
        
        This would be represented by the tree:
                                ProgramNode
                              /     |       \
                             5     "*"      "="
                                  /   \    /   \
                                 10   11  x    13
        Starting from this node and evaluating all of its children would essentially mean that we've evaluated
        the entire program.
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
        Similar to RetStatement, the value would be derived by evaluating the tree
        starting at m_Expression.
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
        PrefixExpression Node
        A Prefix Expression is an expression that has a unary operator and one operand to its right.
        Its operand is an expression in of itself, so its operand can also be another PrefixExpression (like "!!true")
        or it could be an InfixExpression (like "!(x == y)")
        Example: !!true;
        Would be represented by the tree
                            "!"
                              \
                              "!"
                                \
                                "true"
        or, with an InfixExpression as its operand,
        example: !(x == y);
                            "!"
                              \
                             "=="
                            /    \
                           x      y
    */
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
        InfixExpression Node
        An Infix Expression is an expression that has a binary operator (the tree's root) and two operands, left and right
        Both operands are expressions in of themselves, so each operand can be another Infix Expression, or a Prefix Expression
        Example: -5 * 6 + 10 / 11;
        Would be represented by the tree
                           "+"
                         /     \
                       "*"     "/"
                       / \     /  \
                     "-"  6   10  11
                     /
                    5
        In the tree above, every subtree that has two leafs (left and right) is an InfixExpression Node.
        i.e. The "*", "/" and "+" trees. For the "*" subtree, it's left operand is a Prefix Expression.
    */
    class InfixExpression : public Expression
    {
    public:
        InfixExpression(Token p_Token, const string &p_Operator, Expression *p_LhsExpression) noexcept : m_Token(p_Token), m_Operator(p_Operator), m_LhsExpression(p_LhsExpression) {}
        auto TokenBody() noexcept -> string;
        auto TokenLiteral() noexcept -> string;
        auto ToString() noexcept -> string;

        Token m_Token;
        string m_Operator;
        Expression *m_LhsExpression;
        Expression *m_RhsExpression;
    };

    /*
        LetStatement Node
        A let statement strictly takes the format of `let <Identifier> = <Expression>`
        or, more formally, 

        <LetStatement> = "let" <Identifier> "=" <Expression> ";"
        <Identifier> = <Letter> { <Letter> | <Digit> | <Underline> }
        <Expression> = ..

        In the context of the syntax tree, the LetStatement Node would conceptually have a left child and a right subtree.
        Left child is explicitly not a subtree, just a singular leaf node, since an identifier is not an expression.
        Right subtree is an expression, so it can be whatever valid expression (Infix or Prefix Expression)
        example: let x = 10 * 11;
        this would be represented by the tree:
                            "="
                           /   \
                          x    "*"
                              /   \
                             10   11
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
        The expression can be an Infix Expression or a Prefix Expression.
        The tree starting at the m_ReturnValue node would be evaluated before executing the 'return'.

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
}

#endif