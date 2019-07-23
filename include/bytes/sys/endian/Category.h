#ifndef BYTES_SYS_ENDIAN_CATEGORY_H_
#define BYTES_SYS_ENDIAN_CATEGORY_H_

#include "../../Endian.h"

#include <cstdint>

namespace bytes
{
namespace sys
{
namespace endian
{

inline bytes::Endian::CategoryEnum Category()
{
    const std::uint16_t one = 1;
    const std::uint8_t * bytes = reinterpret_cast<const std::uint8_t *>(&one);
    if (bytes[0] == std::uint8_t(1)) return bytes::Endian::little;
    return bytes::Endian::big;
}

} //!endian

} //!sys

} //!bytes

#endif //!BYTES_SYS_ENDIAN_CATEGORY_H_
