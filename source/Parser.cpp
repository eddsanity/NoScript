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
            m_ErrorLogger.errlog("Expecting an IDENTIFIER, found: " + m_ParserCurrToken.m_TokenLiteral);
            return nullptr;
        }

        stmt_identifier->m_Token = m_ParserCurrToken;
        stmt_identifier->m_Value = m_ParserCurrToken.m_TokenLiteral;

        // Move past the TOKEN_IDENT token
        this->ConsumeToken();

        // If the token immediately after the identifier isn't an assignment operator, catch the error.
        if (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_ASSIGN)
        {
            m_ErrorLogger.errlog("Expecting an ASSIGNMENT (=) operator, found: " + m_ParserCurrToken.m_TokenLiteral);
            return nullptr;
        }

        // Move past the TOKEN_ASSIGN token
        this->ConsumeToken();

        stmt_value = this->ParseExpression(LOWEST);
        if (stmt_value == nullptr)
            return nullptr;

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

        stmt_value = this->ParseExpression(LOWEST);
        if (stmt_value == nullptr)
            return nullptr;

        // Move past the return expression token
        // this->ConsumeToken();
        while (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_SEMICOLON)
            this->ConsumeToken();

        if (m_ParserCurrToken.m_TokenType != TokenType::TOKEN_SEMICOLON)
        {
            m_ErrorLogger.errlog("Missing semicolon");
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
        {
            m_ErrorLogger.errlog("Invalid operator: " + m_ParserCurrToken.m_TokenLiteral);
            return nullptr;
        }

        /*
            If there is a parse function associated with the token type, get that function and execute it
            and return whatever it returns
        */
        auto prefix_fn_ptr = m_PrefixParseFunctions.at(m_ParserCurrToken.m_TokenType);
        auto left_expression = prefix_fn_ptr(*this);

        /*
            If the left expression is null, then the prefix_fn_ptr failed
            log the error and return null
        */
        if (left_expression == nullptr)
            return nullptr;

        while (m_ParserPeekToken.m_TokenType != TokenType::TOKEN_SEMICOLON &&
               p_precedence < LookupPrecedence(m_ParserPeekToken.m_TokenType))
        {
            auto infix_fn_ptr = m_InfixParseFunctions.at(m_ParserPeekToken.m_TokenType);

            /* If no infix function exists for the parsed token, return whatever's LHS is */
            if (infix_fn_ptr == nullptr)
                return left_expression;

            this->ConsumeToken();

            left_expression = infix_fn_ptr(*this, left_expression);

            /*
                Similar to left_expression in the prefix situation, if left_expression is null
                then infix_fn_ptr has failed, log the error and return null
            */
            if (left_expression == nullptr)
                return nullptr;
        }

        return left_expression;
    }
}