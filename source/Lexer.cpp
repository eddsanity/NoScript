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

    [[nodiscard]] auto
    Lexer::ReadWord() noexcept -> std::string
    {
        uint32_t start_pos = m_LexerCurrPos;
        while(IsLetter(m_LexerChar) || IsDigit(m_LexerChar))
            this->ConsumeChar();

        return m_LexerInput.substr(start_pos, m_LexerCurrPos - start_pos);
    }

    [[nodiscard]] auto
    Lexer::ReadInteger() noexcept -> std::string
    {
        uint32_t start_pos = m_LexerCurrPos;
        while(IsDigit(m_LexerChar))
            this->ConsumeChar();

        return m_LexerInput.substr(start_pos, m_LexerCurrPos - start_pos);
    }

    [[nodiscard]] auto
    Lexer::Lookahead() const noexcept -> char
    {
        if(m_LexerPeekPos >= m_LexerInput.length())
            return 0;
        return m_LexerInput[m_LexerPeekPos];
    }

    [[nodiscard]] auto
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
                result_token = Token(TokenType::EQ, "==");
            }
            else
                result_token = Token(TokenType::ASSIGN, "=");
            break;
        case '!':
            if (this->Lookahead() == '=')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::NEQ, "!=");
            }
            else
                result_token = Token(TokenType::NOT, "!");
            break;
        case '&':
            if (this->Lookahead() == '&')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::AND, "&&");
            }
            else
                result_token = Token(TokenType::ILLEGAL, "ILLEGAL");
            break;
        case '|':
            if (this->Lookahead() == '|')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::OR, "||");
            }
            else
                result_token = Token(TokenType::ILLEGAL, "ILLEGAL");
            break;
        case '<':
            if (this->Lookahead() == '=')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::LTE, "<=");
            }
            else
                result_token = Token(TokenType::LT, "<");
            break;
        case '>':
            if (this->Lookahead() == '=')
            {
                this->ConsumeChar();
                result_token = Token(TokenType::GTE, ">=");
            }
            else
                result_token = Token(TokenType::GT, ">");
            break;
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
            result_token = Token(TokenType::EndOfFile, "EOF");
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
                result_token = Token(TokenType::INT, word);
                return result_token;
            }
            else
                result_token = Token(TokenType::ILLEGAL, "ILLEGAL");
            break;
        }

        this->ConsumeChar();
        return result_token;
    }
}