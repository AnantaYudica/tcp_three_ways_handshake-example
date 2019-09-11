#ifndef HEADER_IPV4_FLAG_H_
#define HEADER_IPV4_FLAG_H_

#include <cstdint>

namespace header
{
namespace ipv4
{

enum class Flag : std::uint8_t
{
    _default = 0,
    df = 1,
    mf = 2
};

namespace flag
{

inline constexpr std::uint8_t ToValue(const header::ipv4::Flag & flag_enum)
{
    return static_cast<std::uint8_t>(flag_enum);
}

inline header::ipv4::Flag ToEnum(const std::uint8_t & flag_value)
{
    switch(flag_value)
    {
        case ToValue(header::ipv4::Flag::df) :
            return header::ipv4::Flag::df;
        case ToValue(header::ipv4::Flag::mf) :
            return header::ipv4::Flag::mf;
    }
    return header::ipv4::Flag::_default;
}

} //!flag

} //ipv4

} //!header

#endif //!HEADER_IPV4_FLAG_H_
