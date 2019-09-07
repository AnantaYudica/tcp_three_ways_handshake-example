#ifndef BIT_FIELD_VALUE_H_
#define BIT_FIELD_VALUE_H_

#include <cstddef>
#include <cstdint>

#include "min/Size.h"
#include "min/Value.h"

namespace bit
{
namespace field
{

template<std::size_t N>
struct Value
{
    inline Value() = delete;
    typedef typename bit::field::min::Value<bit::field::min::Size<N>()>::Type Type;
};

} //!field

} //!bit

#endif //!BIT_FIELD_VALUE_H_
