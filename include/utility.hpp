#ifndef UTILITY_HPP
#define UTILITY_HPP

namespace nolang
{
    [[nodiscard]] auto
    IsLetter(char p_byte) noexcept -> bool;

    [[nodiscard]] auto
    IsDigit(char p_byte) noexcept -> bool;
}

#endif