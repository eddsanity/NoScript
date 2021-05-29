#include <AST.hpp>
#include <utility.hpp>

namespace noscript
{
    Program::~Program() noexcept
    {
        for (auto stmt_ptr : m_Statements)
            delete stmt_ptr;
    }

    auto
    Program::TokenBody() noexcept -> string
    {
        if (m_Statements.size() > 0)
            return m_Statements[0]->TokenBody();
        else
            return "";
    }

    auto
    Program::TokenLiteral() noexcept -> string
    {
        if (m_Statements.size() > 0)
            return m_Statements[0]->TokenLiteral();
        else
            return "";
    }

    auto
    Program::ToString() noexcept -> string
    {
        string output_string = "";
        for (auto &stmt : m_Statements)
            output_string += stmt->ToString();
        return output_string;
    }

    auto
    ExpressionStatement::TokenBody() noexcept -> string
    {
        return "{" + noscript::EnumAsString(m_Token.m_TokenType) + ", " + m_Token.m_TokenLiteral + "}";
    }

    auto
    ExpressionStatement::TokenLiteral() noexcept -> string
    {
        return m_Token.m_TokenLiteral;
    }

    auto
    ExpressionStatement::ToString() noexcept -> string
    {
        if (m_Expression != nullptr)
            return m_Expression->ToString();
        return "";
    }

    auto
    IntegerLiteral::TokenBody() noexcept -> string
    {
        return "{" + noscript::EnumAsString(m_Token.m_TokenType) + ", " + std::to_string(m_Int64Value) + "}";
    }

    auto
    IntegerLiteral::TokenLiteral() noexcept -> string
    {
        return m_Token.m_TokenLiteral;
    }

    auto
    IntegerLiteral::ToString() noexcept -> string
    {
        return m_Token.m_TokenLiteral;
    }

    auto
    PrefixExpression::TokenBody() noexcept -> string
    {
        return "{" + noscript::EnumAsString(m_Token.m_TokenType) + ", " + m_RhsExpression->TokenBody() + "}";
    }

    auto
    PrefixExpression::TokenLiteral() noexcept -> string
    {
        return m_Token.m_TokenLiteral;
    }

    auto
    PrefixExpression::ToString() noexcept -> string
    {
        string output{""};

        output += "(";
        output += m_Operator;
        output += m_RhsExpression->ToString();
        output += ")";
        return output;
    }

    auto
    LetStatement::TokenBody() noexcept -> string
    {
        return "{" + noscript::EnumAsString(m_Token.m_TokenType) + ", " + m_Token.m_TokenLiteral + "}";
    }

    auto
    LetStatement::TokenLiteral() noexcept -> string
    {
        return m_Token.m_TokenLiteral;
    }

    auto
    LetStatement::ToString() noexcept -> string
    {
        string output_string("");
        output_string += this->TokenBody() + " ";
        output_string += m_IdentifierName->ToString();
        output_string += " = ";

        if (m_IdentifierValue != nullptr)
            output_string += m_IdentifierValue->ToString();

        output_string += ";";
        return output_string;
    }

    auto
    RetStatement::TokenBody() noexcept -> string
    {
        return "{" + noscript::EnumAsString(m_Token.m_TokenType) + ", " + m_Token.m_TokenLiteral + "}";
    }

    auto
    RetStatement::TokenLiteral() noexcept -> string
    {
        return m_Token.m_TokenLiteral;
    }

    auto
    RetStatement::ToString() noexcept -> string
    {
        string output_string("");
        output_string += this->TokenBody() + " ";

        if (m_ReturnValue != nullptr)
            output_string += m_ReturnValue->ToString();

        output_string += ";";
        return output_string;
    }

}