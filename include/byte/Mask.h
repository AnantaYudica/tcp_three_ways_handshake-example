#ifndef BYTE_MASK_H_
#define BYTE_MASK_H_

#include <cstdint>

namespace byte
{

inline std::uint8_t Mask(const int & v, const int & s = 0)
{
    return s < 0 ? std::uint8_t(v) >> -s: std::uint8_t(v) << s;
}

} //!byte

#endif //!BYTE_MASK_H_
