#ifndef BYTES_POINTER_H_
#define BYTES_POINTER_H_

#include <cstdint>
#include <memory>

namespace bytes
{

inline std::uint8_t * Pointer(std::shared_ptr<std::uint8_t> & ptr, 
    const std::size_t & i = 0)
{
    return ptr.get() + i;
}

inline const std::uint8_t * Pointer(const std::shared_ptr<std::uint8_t> & ptr, 
    const std::size_t & i = 0)
{
    return ptr.get() + i;
}

} //!bytes

#endif //!BYTES_POINTER_H_
