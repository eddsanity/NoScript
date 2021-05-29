#include <Lexer.hpp>

namespace noscript
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

    auto
    Lexer::ReadWord() noexcept -> std::string
    {
        uint32_t start_pos = m_LexerCurrPos;
        while (IsLetter(m_LexerChar) || IsDigit(m_LexerChar))
            this->ConsumeChar();

        return m_LexerInput.substr(start_pos, m_LexerCurrPos - start_pos);
    }

    auto
    Lexer::ReadInteger() noexcept -> std::string
    {
        uint32_t start_pos = m_LexerCurrPos;
        while (IsDigit(m_LexerChar))
            this->ConsumeChar();

        return m_LexerInput.substr(start_pos, m_LexerCurrPos - start_pos);
    }

    auto
    Lexer::Lookahead() const noexcept -> char
    {
        if (m_LexerPeekPos >= m_LexerInput.length())
            return 0;
        return m_LexerInput[m_LexerPeekPos];
    }

    auto
    Lexer::NextToken() noexcept -> noscript::Token
    {
        noscript::Token result_token;

        this->ConsumeSpace();

        char lex_char = m_LexerChar;

        switch (lex_char)
        {
        case '=':
            if (this->Lookahead() == '=')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::TOKEN_EQ, "==");
            }
            else
                result_token = Token(TokenType::TOKEN_ASSIGN, "=");
            break;
        case '!':
            if (this->Lookahead() == '=')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::TOKEN_NEQ, "!=");
            }
            else
                result_token = Token(TokenType::TOKEN_NOT, "!");
            break;
        case '&':
            if (this->Lookahead() == '&')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::TOKEN_AND, "&&");
            }
            else
                result_token = Token(TokenType::TOKEN_ILLEGAL, "ILLEGAL");
            break;
        case '|':
            if (this->Lookahead() == '|')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::TOKEN_OR, "||");
            }
            else
                result_token = Token(TokenType::TOKEN_ILLEGAL, "ILLEGAL");
            break;
        case '<':
            if (this->Lookahead() == '=')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::TOKEN_LTE, "<=");
            }
            else
                result_token = Token(TokenType::TOKEN_LT, "<");
            break;
        case '>':
            if (this->Lookahead() == '=')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::TOKEN_GTE, ">=");
            }
            else
                result_token = Token(TokenType::TOKEN_GT, ">");
            break;
        case '+':
            result_token = Token(TokenType::TOKEN_PLUS, "+");
            break;
        case '-':
            result_token = Token(TokenType::TOKEN_MINUS, "-");
            break;
        case '*':
            result_token = Token(TokenType::TOKEN_ASTERISK, "*");
            break;
        case '/':
            result_token = Token(TokenType::TOKEN_SLASH, "/");
            break;
        case ',':
            result_token = Token(TokenType::TOKEN_COMMA, ",");
            break;
        case ';':
            result_token = Token(TokenType::TOKEN_SEMICOLON, ";");
            break;
        case '(':
            result_token = Token(TokenType::TOKEN_LPAREN, "(");
            break;
        case ')':
            result_token = Token(TokenType::TOKEN_RPAREN, ")");
            break;
        case '{':
            result_token = Token(TokenType::TOKEN_LBRACE, "{");
            break;
        case '}':
            result_token = Token(TokenType::TOKEN_RBRACE, "}");
            break;
        case 0:
            result_token = Token(TokenType::TOKEN_EOF, "EOF");
            break;
        default:
            if (IsLetter(lex_char))
            {
                auto word = this->ReadWord();
                auto word_token_type = noscript::LookupIdentifier(word);
                result_token = Token(word_token_type, word);
                return result_token;
            }
            else if (IsDigit(lex_char))
            {
                auto word = this->ReadInteger();
                result_token = Token(TokenType::TOKEN_INT, word);
                return result_token;
            }
            else
                result_token = Token(TokenType::TOKEN_ILLEGAL, "ILLEGAL");
            break;
        }

        this->ConsumeChar();
        return result_token;
    }
}