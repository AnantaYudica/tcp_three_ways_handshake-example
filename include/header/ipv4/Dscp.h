#ifndef HEADER_IPV4_DSCP_H_
#define HEADER_IPV4_DSCP_H_

#include <cstdint>

namespace header
{
namespace ipv4
{

enum class Dscp : std::uint8_t
{
    expedited_forwarding = 46,
    ef = 46,
    best_effort = 0,
    _default = 0,
    af11 = 10,
    af12 = 11,
    af13 = 14,
    af21 = 18,
    af22 = 20,
    af23 = 22,
    af31 = 26,
    af32 = 28,
    af33 = 30,
    af41 = 34,
    af42 = 36,
    af43 = 38,
    cs1 = 8,
    cs2 = 16,
    cs3 = 24,
    cs4 = 32,
    cs5 = 40,
    cs6 = 48,
    cs7 = 56
};

namespace dscp
{

inline constexpr std::uint8_t ToValue(const Dscp & dscp_enum)
{
    return static_cast<std::uint8_t>(dscp_enum);
}

inline ipv4::Dscp ToEnum(const std::uint8_t & dscp_value)
{
    switch (dscp_value)
    {
        case ToValue(ipv4::Dscp::ef): 
            return ipv4::Dscp::ef;
        case ToValue(ipv4::Dscp::af11):
            return ipv4::Dscp::af11;
        case ToValue(ipv4::Dscp::af12):
            return ipv4::Dscp::af12;
        case ToValue(ipv4::Dscp::af13):
            return ipv4::Dscp::af13;
        case ToValue(ipv4::Dscp::af21):
            return ipv4::Dscp::af21;
        case ToValue(ipv4::Dscp::af22):
            return ipv4::Dscp::af22;
        case ToValue(ipv4::Dscp::af23):
            return ipv4::Dscp::af23;
        case ToValue(ipv4::Dscp::af31):
            return ipv4::Dscp::af31;
        case ToValue(ipv4::Dscp::af32):
            return ipv4::Dscp::af32;
        case ToValue(ipv4::Dscp::af33):
            return ipv4::Dscp::af33;
        case ToValue(ipv4::Dscp::af41):
            return ipv4::Dscp::af41;
        case ToValue(ipv4::Dscp::af42):
            return ipv4::Dscp::af42;
        case ToValue(ipv4::Dscp::af43):
            return ipv4::Dscp::af43;
        case ToValue(ipv4::Dscp::cs1):
            return ipv4::Dscp::cs1;
        case ToValue(ipv4::Dscp::cs2):
            return ipv4::Dscp::cs2;
        case ToValue(ipv4::Dscp::cs3):
            return ipv4::Dscp::cs3;
        case ToValue(ipv4::Dscp::cs4):
            return ipv4::Dscp::cs4;
        case ToValue(ipv4::Dscp::cs5):
            return ipv4::Dscp::cs5;
        case ToValue(ipv4::Dscp::cs6):
            return ipv4::Dscp::cs6;
        case ToValue(ipv4::Dscp::cs7):
            return ipv4::Dscp::cs7;
    }
    return ipv4::Dscp::_default;
}


} //!dscp

} //!ipv4

} //!header

#endif //!HEADER_IPV4_DSCP_H_
