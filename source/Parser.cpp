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
        case TokenType::RETURN:
            return this->ParseRetStatement();
        default:
            return nullptr;
        }
    }

    [[nodiscard]] auto
    Parser::ParseLetStatement() noexcept -> Statement *
    {
        LetStatement *let_stmt = new LetStatement();
        let_stmt->m_Token = m_ParserCurrToken;
        Identifier *stmt_identifier = new Identifier();
        Expression *stmt_value = nullptr;

        // Move past the LET token
        this->ConsumeToken();

        // If the token immediately after the LET isn't an identifier, catch the error.
        if (m_ParserCurrToken.m_TokenType != TokenType::IDENT)
        {
            m_ErrorLogger.errlog("Syntax Error", "Expected an identifier in LET statement");
            return nullptr;
        }

        stmt_identifier->m_Token = m_ParserCurrToken;
        stmt_identifier->m_Value = m_ParserCurrToken.m_TokenLiteral;

        // Move past the IDENT token
        this->ConsumeToken();

        // If the token immediately after the identifier isn't an assignment operator, catch the error.
        if (m_ParserCurrToken.m_TokenType != TokenType::ASSIGN)
        {
            m_ErrorLogger.errlog("Syntax Error", "Expected an assignment operator in LET statement");
            return nullptr;
        }

        // Move past the ASSIGN token
        this->ConsumeToken();

        stmt_value = nullptr;

        // Move past the rhs-expression token
        // this->ConsumeToken();
        while(m_ParserCurrToken.m_TokenType != TokenType::SEMICOLON)
            this->ConsumeToken();

        let_stmt->m_IdentifierName = stmt_identifier;
        let_stmt->m_IdentifierValue = stmt_value;
        return let_stmt;
    }

    [[nodiscard]] auto
    Parser::ParseRetStatement() noexcept -> Statement *
    {
        RetStatement *ret_stmt = new RetStatement();
        ret_stmt->m_Token = m_ParserCurrToken;
        Expression *stmt_value = nullptr;

        // Move past the RETURN token
        this->ConsumeToken();

        stmt_value = nullptr;

        // Move past the return expression token
        // this->ConsumeToken();
        while(m_ParserCurrToken.m_TokenType != TokenType::SEMICOLON)
            this->ConsumeToken();

        if(m_ParserCurrToken.m_TokenType != TokenType::SEMICOLON)
        {
            m_ErrorLogger.errlog("Missing semicolon", "Expecting a semicolo");
            return nullptr;
        }

        ret_stmt->m_ReturnValue = stmt_value;
        return ret_stmt;
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