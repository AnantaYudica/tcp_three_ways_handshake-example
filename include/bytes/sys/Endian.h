#ifndef BYTES_SYS_ENDIAN_H_
#define BYTES_SYS_ENDIAN_H_

#include "endian/Category.h"
#include "../Endian.h"
#include "../endian/Big.h"
#include "../endian/Little.h"

#include <cstdint>

namespace bytes
{
namespace sys
{

inline const bytes::Endian & Endian()
{
    if (bytes::sys::endian::Category() == bytes::Endian::big)
        return bytes::endian::Big::Instance();
    return bytes::endian::Little::Instance();
}

} //!sys

} //!bytes

#endif //!BYTES_SYS_ENDIAN_H_
