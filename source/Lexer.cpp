#include <Lexer.hpp>

namespace nolang
{
    Lexer::Lexer(const std::string &p_LexerInput) noexcept
    {
        this->m_LexerInput = p_LexerInput;
        m_LexerPeekPos = 0;
        m_LexerCurrPos = 0;
        this->ConsumeChar();
    }

    auto
    Lexer::ConsumeChar() noexcept -> void
    {
        /*
            if EOF, current character is nothing
            else, current character is wherever the peek pointer is pointing to,
            i.e. character m_LexerInput[m_LexerPeekPos] is consumed.
        */
        if (m_LexerPeekPos >= m_LexerInput.length())
            m_LexerChar = 0;
        else
            m_LexerChar = m_LexerInput[m_LexerPeekPos];

        // update "file pointers"
        m_LexerCurrPos = m_LexerPeekPos;
        m_LexerPeekPos++;
    }

    auto
    Lexer::ConsumeSpace() noexcept -> void
    {
        while (m_LexerChar == ' ' ||
               m_LexerChar == '\t' ||
               m_LexerChar == '\n' ||
               m_LexerChar == '\r')
            this->ConsumeChar();
    }

    [[nodiscard]] auto
    Lexer::NextToken() noexcept -> nolang::Token
    {
        nolang::Token result_token;

        this->ConsumeSpace();

        char lex_char = m_LexerChar;

        switch (lex_char)
        {
        case '+':
            result_token = Token(TokenType::PLUS, "+");
            break;
        case '-':
            result_token = Token(TokenType::MINUS, "-");
            break;
        case '*':
            result_token = Token(TokenType::ASTERISK, "*");
            break;
        case '/':
            result_token = Token(TokenType::SLASH, "/");
            break;
        case ',':
            result_token = Token(TokenType::COMMA, ",");
            break;
        case ';':
            result_token = Token(TokenType::SEMICOLON, ";");
            break;
        case '(':
            result_token = Token(TokenType::LPAREN, "(");
            break;
        case ')':
            result_token = Token(TokenType::RPAREN, ")");
            break;
        case '{':
            result_token = Token(TokenType::LBRACE, "{");
            break;
        case '}':
            result_token = Token(TokenType::RBRACE, "}");
            break;
        case 0:
            result_token = Token(TokenType::EndOfFile, "");
            break;
        }

        this->ConsumeChar();
        return result_token;
    }

}