#ifndef BIT_FIELD_MIN_ALLOCATION_H_
#define BIT_FIELD_MIN_ALLOCATION_H_

#include <cstddef>

#include "Size.h"

namespace bit
{
namespace field
{
namespace min
{

template<std::size_t N>
constexpr std::size_t Allocation()
{
    return bit::field::min::Size<N>() / 8;
}

} //!min

} //!field

} //!bit

#endif //!BIT_FIELD_MIN_ALLOCATION_H_
