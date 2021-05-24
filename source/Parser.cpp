#include <Parser.hpp>

namespace noscript
{
    Parser::Parser(Lexer *p_Lexer) noexcept
    {
        m_Lexer = p_Lexer;

        this->ConsumeToken();
        this->ConsumeToken();
    }

    auto
    Parser::ConsumeToken() noexcept -> void
    {
        m_ParserCurrToken = m_ParserPeekToken;
        m_ParserPeekToken = m_Lexer->NextToken();
    }

    [[nodiscard]] auto
    Parser::ParseProgram() noexcept -> Program *
    {
        Program *program_node = new Program();

        while (m_ParserCurrToken.m_TokenType != TokenType::EndOfFile)
        {
            Statement *stmt = this->ParseStatement();

            if (stmt != nullptr)
                program_node->m_Statements.push_back(stmt);

            // TODO: Add error logging if statement is nullptr

            this->ConsumeToken();
        }

        return program_node;
    }

    [[nodiscard]] auto
    Parser::ParseStatement() noexcept -> Statement *
    {
        switch (m_ParserCurrToken.m_TokenType)
        {
        case TokenType::LET:
            return this->ParseLetStatement();
        default:
            return nullptr;
        }
    }

    [[nodiscard]] auto
    Parser::ParseLetStatement() noexcept -> Statement *
    {
        LetStatement *let_stmt = new LetStatement();
        Identifier *stmt_identifier = new Identifier();
        Expression *stmt_value = nullptr;

        // Move past the LET token
        this->ConsumeToken();
        
        // If the token immediately after the LET isn't an identifier, catch the error.
        if(m_ParserCurrToken.m_TokenType != TokenType::IDENT)
        {
            // TODO: Error logger raises error
            return nullptr;
        }

        stmt_identifier->m_Token = m_ParserCurrToken;
        stmt_identifier->m_Value = m_ParserCurrToken.m_TokenLiteral;

        // Move past the IDENT token
        this->ConsumeToken();

        // If the token immediately after the identifier isn't an assignment operator, catch the error.
        if (m_ParserCurrToken.m_TokenType != TokenType::ASSIGN)
        {
            // TODO: Error logger raises error
            return nullptr;
        }

        // Move past the ASSIGN token
        this->ConsumeToken();

        stmt_value = nullptr;

        let_stmt->m_IdentifierName = stmt_identifier;
        let_stmt->m_IdentifierValue = stmt_value;
        let_stmt->m_Token = m_ParserCurrToken;
        return let_stmt;
    }

    // [[nodiscard]] auto
    // Parser::ParseExpression() noexcept -> Expression *
    // {
    //     switch (m_ParserCurrToken.m_TokenType)
    //     {
    //     case TokenType::INT:
    //         if (m_ParserPeekToken.m_TokenType ==)
    //     }
    // }
}