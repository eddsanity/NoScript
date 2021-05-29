#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <Token.hpp>

namespace noscript
{
    auto
    IsLetter(char p_byte) noexcept -> bool;

    auto
    IsDigit(char p_byte) noexcept -> bool;

    auto
    EnumAsString(TokenType p_token) noexcept -> std::string;
}

#endif