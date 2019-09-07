#ifndef BIT_FIELD_MIN_VALUE_H_
#define BIT_FIELD_MIN_VALUE_H_

#include <cstddef>
#include <cstdint>

namespace bit
{
namespace field
{
namespace min
{

template<std::size_t N>
struct Value
{
    inline Value() = delete;
};

template<>
struct Value<8>
{
    inline Value() = delete;
    typedef std::uint8_t Type;
};

template<>
struct Value<16>
{
    inline Value() = delete;
    typedef std::uint16_t Type;
};

template<>
struct Value<32>
{
    inline Value() = delete;
    typedef std::uint32_t Type;
};

template<>
struct Value<64>
{
    inline Value() = delete;
    typedef std::uint64_t Type;
};

} //!min

} //field

} //!bit

#endif //!BIT_FIELD_MIN_VALUE_H_
