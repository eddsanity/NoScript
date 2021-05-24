#ifndef AST_HPP
#define AST_HPP

#include <vector>

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
        <Statements> = <statement> { <Statements> }
        <Statement>  = <LetStatement> |
                       <RetStatement> |
                       ..
    */
    class Program : public Node
    {
    public:
        [[nodiscard]] auto TokenLiteral() -> string;

        vector<Statement*> m_Statements;

        ~Program() noexcept;
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
        [[nodiscard]] auto TokenLiteral() -> string;

        Token m_Token;
        Identifier* m_IdentifierName;
        Expression* m_IdentifierValue;
    };
}

#endif