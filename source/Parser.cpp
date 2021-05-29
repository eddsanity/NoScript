#include <Parser.hpp>

namespace noscript
{
    auto
    Parser::ParseProgram() noexcept -> Program *
    {
        Program *program_node = new Program();

        while (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_EOF)
        {
            Statement *stmt = this->ParseStatement();

            if (stmt != nullptr)
                program_node->m_Statements.push_back(stmt);

            this->ConsumeToken();
        }

        return program_node;
    }

    auto
    Parser::ParseStatement() noexcept -> Statement *
    {
        switch (m_ParserCurrToken.m_TokenType)
        {
        case TokenType::TOKEN_LET:
            return this->ParseLetStatement();
        case TokenType::TOKEN_RETURN:
            return this->ParseRetStatement();
        default:
            return this->ParseExpressionStatement();
        }
    }

    auto
    Parser::ParseLetStatement() noexcept -> Statement *
    {
        LetStatement *let_stmt = new LetStatement();
        let_stmt->m_Token = m_ParserCurrToken;
        Identifier *stmt_identifier = new Identifier();
        Expression *stmt_value = nullptr;

        // Move past the TOKEN_LET token
        this->ConsumeToken();

        // If the token immediately after the TOKEN_LET isn't an identifier, catch the error.
        if (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_IDENT)
        {
            m_ErrorLogger.errlog("Syntax Error", "Expected an identifier in TOKEN_LET statement");
            return nullptr;
        }

        stmt_identifier->m_Token = m_ParserCurrToken;
        stmt_identifier->m_Value = m_ParserCurrToken.m_TokenLiteral;

        // Move past the TOKEN_IDENT token
        this->ConsumeToken();

        // If the token immediately after the identifier isn't an assignment operator, catch the error.
        if (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_ASSIGN)
        {
            m_ErrorLogger.errlog("Syntax Error", "Expected an assignment operator in TOKEN_LET statement");
            return nullptr;
        }

        // Move past the TOKEN_ASSIGN token
        this->ConsumeToken();

        stmt_value = this->ParseExpression(LOWEST);

        // Move past the rhs-expression token
        // this->ConsumeToken();
        while (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_SEMICOLON)
            this->ConsumeToken();

        let_stmt->m_IdentifierName = stmt_identifier;
        let_stmt->m_IdentifierValue = stmt_value;
        return let_stmt;
    }

    auto
    Parser::ParseRetStatement() noexcept -> Statement *
    {
        RetStatement *ret_stmt = new RetStatement();
        ret_stmt->m_Token = m_ParserCurrToken;
        Expression *stmt_value = nullptr;

        // Move past the TOKEN_RETURN token
        this->ConsumeToken();

        stmt_value = nullptr;

        // Move past the return expression token
        // this->ConsumeToken();
        while (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_SEMICOLON)
            this->ConsumeToken();

        if (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_SEMICOLON)
        {
            m_ErrorLogger.errlog("Missing semicolon", "Expecting a semicolo");
            return nullptr;
        }

        ret_stmt->m_ReturnValue = stmt_value;
        return ret_stmt;
    }

    auto
    Parser::ParseExpressionStatement() noexcept -> ExpressionStatement *
    {
        ExpressionStatement *expr_stmt = new ExpressionStatement();
        expr_stmt->m_Token = m_ParserCurrToken;

        expr_stmt->m_Expression = this->ParseExpression(LOWEST);

        if (m_ParserPeekToken.m_TokenType == TokenType::TOKEN_SEMICOLON)
            this->ConsumeToken();

        return expr_stmt;
    }

    auto
    Parser::ParseExpression(int p_precedence) noexcept -> Expression *
    {
        /* 
            If there are no parse functions associated with the token type, return null
        */
        if (m_PrefixParseFunctions.find(m_ParserCurrToken.m_TokenType) == m_PrefixParseFunctions.end())
            return nullptr;

        /*
            If there is a parse function associated with the token type, get that function and execute it
            and return whatever it returns
        */
        auto left_expression = m_PrefixParseFunctions.at(m_ParserCurrToken.m_TokenType)(*this);
        return left_expression;
    }
}