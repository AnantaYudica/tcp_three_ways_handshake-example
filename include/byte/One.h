#ifndef BYTE_ONE_H_
#define BYTE_ONE_H_

#include <cstdint>

namespace byte
{

inline std::uint8_t One(const std::uint8_t & shiff, bool is_true = true)
{
    if (!is_true) return 0;
    std::uint8_t i = 1;
    i <<= shiff;
    return i;
}

} //!byte

#endif //!BYTE_ONE_H_
