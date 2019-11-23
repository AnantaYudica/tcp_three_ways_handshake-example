#ifndef HEADER_IPV4_ADDRESS_H_
#define HEADER_IPV4_ADDRESS_H_

#include <cstdint>
#include <string>
#include <cstddef>
#include <cstdio>

#include "../../bytes/sys/Endian.h"

namespace header
{
namespace ipv4
{

class Address
{
private:
    union Value
    {
        std::uint8_t uint8[4];
        std::uint32_t  uint32;
        inline Value(const std::uint8_t & val1, const std::uint8_t & val2,
            const std::uint8_t & val3, const std::uint8_t & val4);
        inline Value(const std::uint32_t & val);
    };
private:
    Value m_value;
public:
    inline Address();
    inline Address(const std::uint32_t & val);
    inline Address(const std::uint8_t & val1, const std::uint8_t & val2,
        const std::uint8_t & val3, const std::uint8_t & val4);
public:
    inline ~Address();
public:
    inline Address(const Address & cpy);
    inline Address(Address && mov);
public:
    inline Address & operator=(const Address & cpy);
    inline Address & operator=(Address && mov);
public:
    inline std::uint32_t & GetValue();
    inline const std::uint32_t & GetValue() const;
public:
    inline std::uint8_t * Get();
    inline const std::uint8_t * Get() const;
public:
    inline bool FromString(std::string str);
public:
    inline std::string ToString() const;
public:
    inline std::uint8_t & operator[](const std::uint8_t & i);
    inline const std::uint8_t & operator[](const std::uint8_t & i) const;
};

inline Address::Value::Value(const std::uint8_t & val1, 
    const std::uint8_t & val2, const std::uint8_t & val3, 
    const std::uint8_t & val4)
{
    uint8[bytes::sys::Endian().At(0, 0, 4)] = val1;
    uint8[bytes::sys::Endian().At(1, 0, 4)] = val2;
    uint8[bytes::sys::Endian().At(2, 0, 4)] = val3;
    uint8[bytes::sys::Endian().At(3, 0, 4)] = val4;
}

inline Address::Value::Value(const std::uint32_t & val) :
    uint32(val)
{}

inline Address::Address() :
    m_value(0)
{}

inline Address::Address(const std::uint32_t & val) :
    m_value(val)
{}

inline Address::Address(const std::uint8_t & val1, const std::uint8_t & val2,
    const std::uint8_t & val3, const std::uint8_t & val4) :
        m_value(val1, val2, val3, val4)
{}

inline Address::~Address()
{
    m_value.uint32 = 0;
}

inline Address::Address(const Address & cpy) :
    m_value(cpy.m_value.uint32)
{}

inline Address::Address(Address && mov) :
    m_value(mov.m_value.uint32)
{
    mov.m_value.uint32 = 0;
}

inline Address & Address::operator=(const Address & cpy)
{
    m_value.uint32 = cpy.m_value.uint32;
    return *this;
}

inline Address & Address::operator=(Address && mov)
{
    m_value.uint32 = mov.m_value.uint32;
    mov.m_value.uint32 = 0;
    return *this;
}

inline std::uint32_t & Address::GetValue()
{
    return m_value.uint32;
}

inline const std::uint32_t & Address::GetValue() const
{
    return m_value.uint32;
}

inline std::uint8_t * Address::Get()
{
    return m_value.uint8; 
}

inline const std::uint8_t * Address::Get() const
{
    return m_value.uint8;
}

inline bool Address::FromString(std::string str)
{
    std::uint8_t val[4];
    auto ret = sscanf(str.c_str(), "%llu.%llu.%llu.%llu", &val[0], 
        &val[1], &val[2], &val[3]);
    if (ret != 4) return false;
    (*this)[0] = val[0];
    (*this)[1] = val[1];
    (*this)[2] = val[2];
    (*this)[3] = val[3];
    return true;
}

inline std::string Address::ToString() const
{
    std::string str = "";
    str += std::to_string((*this)[0]);
    str += ".";
    str += std::to_string((*this)[1]);
    str += ".";
    str += std::to_string((*this)[2]);
    str += ".";
    str += std::to_string((*this)[3]);
    return str;
}

inline std::uint8_t & Address::operator[](const std::uint8_t & i)
{
    return m_value.uint8[bytes::sys::Endian().At(i, 0, 4)];
}

inline const std::uint8_t & Address::operator[](const std::uint8_t & i) const
{
    return m_value.uint8[bytes::sys::Endian().At(i, 0, 4)];
}

} //ipv4

} // header


#endif //!HEADER_IPV4_ADDRESS_H_
