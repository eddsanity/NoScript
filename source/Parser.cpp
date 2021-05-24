#include <Parser.hpp>

namespace noscript
{
    Parser::Parser(Lexer *p_Lexer) noexcept
    {
        m_Lexer = std::make_unique<Lexer>(p_Lexer);

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
    Parser::ParseProgram() -> Program *
    {
        return nullptr;
    }
}