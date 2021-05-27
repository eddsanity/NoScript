#include <AST.hpp>

namespace noscript
{
    Program::~Program() noexcept
    {
        for (auto stmt_ptr : m_Statements)
            delete stmt_ptr;
    }

    [[nodiscard]] auto
    Program::TokenLiteral() -> string
    {
        if (m_Statements.size() > 0)
            return m_Statements[0]->TokenLiteral();
        else
            return "";
    }

    [[nodiscard]] auto
    Program::ToString() -> string
    {
        string output_string = "";
        for(auto& stmt : m_Statements)
            output_string += stmt->ToString();
        return output_string;
    }

    [[nodiscard]] auto
    ExpressionStatement::TokenLiteral() -> string
    {
        return m_Token.m_TokenLiteral;
    }

    [[nodiscard]] auto
    ExpressionStatement::ToString() -> string
    {
        if(m_Expression != nullptr)
            return m_Expression->ToString();
        return "";
    }

    [[nodiscard]] auto
    LetStatement::TokenLiteral() -> string
    {
        return m_Token.m_TokenLiteral;
    }

    [[nodiscard]] auto
    LetStatement::ToString() -> string
    {
        string output_string("");
        output_string += this->TokenLiteral() + " ";
        output_string += m_IdentifierName->ToString();
        output_string += " = ";

        if(m_IdentifierValue != nullptr)
            output_string += m_IdentifierValue->ToString();
        
        output_string += ";";
        return output_string;
    }

    [[nodiscard]] auto
    RetStatement::TokenLiteral() -> string
    {
        return m_Token.m_TokenLiteral;
    }

    [[nodiscard]] auto
    RetStatement::ToString() -> string
    {
        string output_string("");
        output_string += this->TokenLiteral() + " ";

        if(m_ReturnValue != nullptr)
            output_string += m_ReturnValue->ToString();

        output_string += ";";
        return output_string;
    }

}