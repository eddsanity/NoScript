#include <utility.hpp>

namespace nolang
{
    [[nodiscard]] auto
    IsLetter(char p_byte) noexcept -> bool
    {
        return (p_byte >= 'a' && p_byte <= 'z') ||
               (p_byte >= 'A' && p_byte <= 'Z') ||
               (p_byte == '_');
    }

    [[nodiscard]] auto
    IsDigit(char p_byte) noexcept -> bool
    {
        return (p_byte >= '0' && p_byte <= '9');
    }
}