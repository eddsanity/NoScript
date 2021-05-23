#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <Token.hpp>

namespace nolang
{
    [[nodiscard]] auto
    IsLetter(char p_byte) noexcept -> bool;

    [[nodiscard]] auto
    IsDigit(char p_byte) noexcept -> bool;

    [[nodiscard]] auto
    EnumAsString(TokenType p_token) noexcept -> std::string;
}

#endif