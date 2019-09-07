#ifndef BIT_FIELD_MIN_SIZE_H_
#define BIT_FIELD_MIN_SIZE_H_

#include <cstddef>

namespace bit
{
namespace field
{
namespace min
{

template<std::size_t N>
constexpr std::size_t Size()
{
    return N <= 0 ? 0 :
        N <= 8 ? 8 :
        N <= 16 ? 16 :
        N <= 32 ? 32 :
        N <= 64 ? 64 : 128;
}

} //!min

} //!field

} //!bit

#endif //!BIT_FIELD_MIN_SIZE_H_
