#ifndef HEADER_IPV4_ECN_H_
#define HEADER_IPV4_ECN_H_

#include <cstdint>

namespace header
{
namespace ipv4
{

enum class Ecn : std::uint8_t
{
    disable = 0,
    _0 = 2,
    _1 = 1,
    ce = 3
};

namespace ecn
{

inline constexpr std::uint8_t ToValue(const header::ipv4::Ecn & ecn_enum)
{
    return static_cast<std::uint8_t>(ecn_enum);
}

inline header::ipv4::Ecn ToEnum(const std::uint8_t & ecn_value)
{
    switch (ecn_value)
    {
        case ToValue(header::ipv4::Ecn::disable) :
            return header::ipv4::Ecn::disable;
        case ToValue(header::ipv4::Ecn::_0) :
            return header::ipv4::Ecn::_0;
        case ToValue(header::ipv4::Ecn::_1) :
            return header::ipv4::Ecn::_1;
        case ToValue(header::ipv4::Ecn::ce) :
            return header::ipv4::Ecn::ce;
    }
    return header::ipv4::Ecn::disable;
}

} //!ecn

} //!ipv4

} //!header

#endif //!HEADER_IPV4_ECN_H_
