#ifndef BYTE_H_
#define BYTE_H_

#include "Bit.h"

#include <cstdint>
#include <memory>

#include "bytes/Pointer.h"

class Byte
{
private:
    std::shared_ptr<std::uint8_t> m_ptr;
    std::size_t m_index;
public:
    inline Byte();
    inline Byte(const std::uint8_t & b);
    inline Byte(const std::shared_ptr<std::uint8_t> & b);
    inline Byte(const std::shared_ptr<std::uint8_t> & b, 
        const std::size_t & i);
    inline ~Byte();
public:
    inline Byte(const Byte & cpy);
    inline Byte(Byte && mov);
public:
    inline Byte & operator=(Byte && b);
    inline Byte & operator=(const Byte & b);
    inline Byte & operator=(const std::uint8_t & b);
public:
    inline operator std::uint8_t() const;
public:
    inline Byte operator~() const;
public:
    inline Byte & operator|=(const Byte & b);
    inline Byte & operator|=(const std::uint8_t & b);
public:
    inline Byte operator|(const Byte & b) const;
    inline Byte operator|(const std::uint8_t & b) const;
public:
    inline Byte & operator&=(const Byte & b);
    inline Byte & operator&=(const std::uint8_t & b);
public:
    inline Byte operator&(const Byte & b) const;
    inline Byte operator&(const std::uint8_t & b) const;
public:
    inline Byte & operator^=(const Byte & b);
    inline Byte & operator^=(const std::uint8_t & b);
public:
    inline Byte operator^(const Byte & b) const;
    inline Byte operator^(const std::uint8_t & b) const;
public:
    inline Byte & operator>>=(const std::uint8_t & b);
public:
    inline Byte operator>>(const std::uint8_t & b) const;
public:
    inline Byte & operator<<=(const std::uint8_t & b);
public:
    inline Byte operator<<(const std::uint8_t & b) const;
public:
    inline Byte operator+() const = delete;
public:
    inline Byte operator-() const = delete;
public:
    inline Byte & operator++();
    inline Byte operator++(int) const;
public:
    inline Byte & operator--();
    inline Byte operator--(int) const;
public:
    inline Byte & operator+=(const Byte & b);
    inline Byte & operator+=(const std::uint8_t & b);
public:
    inline Byte operator+(const Byte & b) const;
    inline Byte operator+(const std::uint8_t & b) const;
public:
    inline Byte & operator-=(const Byte & b);
    inline Byte & operator-=(const std::uint8_t & b);
public:
    inline Byte operator-(const Byte & b) const;
    inline Byte operator-(const std::uint8_t & b) const;
public:
    inline Byte & operator*=(const Byte & b);
    inline Byte & operator*=(const std::uint8_t & b);
public:
    inline Byte operator*(const Byte & b) const;
    inline Byte operator*(const std::uint8_t & b) const;
public:
    inline Byte & operator/=(const Byte & b);
    inline Byte & operator/=(const std::uint8_t & b);
public:
    inline Byte operator/(const Byte & b) const;
    inline Byte operator/(const std::uint8_t & b) const;
public:
    inline Byte & operator%=(const Byte & b);
    inline Byte & operator%=(const std::uint8_t & b);
public:
    inline Byte operator%(const Byte & b) const;
    inline Byte operator%(const std::uint8_t & b) const;
public:
    inline Bit operator[](const std::uint8_t & i);
    inline const Bit operator[](const std::uint8_t & i) const;
public:
    inline bool operator==(const Byte & b) const;
    inline bool operator==(const std::uint8_t & b) const;
public:
    inline bool operator!=(const Byte & b) const;
    inline bool operator!=(const std::uint8_t & b) const;
public:
    inline bool operator<(const Byte & b) const;
    inline bool operator<(const std::uint8_t & b) const;
public:
    inline bool operator<=(const Byte & b) const;
    inline bool operator<=(const std::uint8_t & b) const;
public:
    inline bool operator>(const Byte & b) const;
    inline bool operator>(const std::uint8_t & b) const;
public:
    inline bool operator>=(const Byte & b) const;
    inline bool operator>=(const std::uint8_t & b) const;
};

inline Byte::Byte() :
    m_ptr(new std::uint8_t(0)),
    m_index(0)
{}

inline Byte::Byte(const std::uint8_t & b) :
    m_ptr(new std::uint8_t(b)),
    m_index(0)
{}

inline Byte::Byte(const std::shared_ptr<std::uint8_t> & b) :
    m_ptr(b),
    m_index(0)
{}

inline Byte::Byte(const std::shared_ptr<std::uint8_t> & b, 
    const std::size_t & i) :
        m_ptr(b),
        m_index(i)
{}

inline Byte::~Byte()
{
    m_ptr = nullptr;
    m_index = 0;
}

inline Byte::Byte(const Byte & cpy) :
    m_ptr(new std::uint8_t(*(cpy.m_ptr))),
    m_index(0)
{}

inline Byte::Byte(Byte && mov) :
    m_ptr(mov.m_ptr),
    m_index(mov.m_index)
{
    mov.m_ptr = std::make_shared<std::uint8_t>(0);
    mov.m_index = 0;
}

inline Byte & Byte::operator=(Byte && b)
{
    m_ptr = b.m_ptr;
    m_index = b.m_index;
    b.m_ptr = std::make_shared<std::uint8_t>(0);
    b.m_index = 0;
    return *this;
}

inline Byte & Byte::operator=(const Byte & b)
{
    return (*this = *bytes::Pointer(b.m_ptr, m_index));
}

inline Byte & Byte::operator=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) = b;
    return *this;
}

inline Byte::operator std::uint8_t() const
{
    return *bytes::Pointer(m_ptr, m_index);
}

inline Byte Byte::operator~() const
{
    Byte res(*this);
    res = ~*bytes::Pointer(res.m_ptr, res.m_index);
    return res;
}

inline Byte & Byte::operator|=(const Byte & b)
{
    return (*this |= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator|=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) |= b;
    return *this;
}

inline Byte Byte::operator|(const Byte & b) const
{
    Byte res(*this);
    res |= b;
    return res;
}

inline Byte Byte::operator|(const std::uint8_t & b) const
{
    Byte res(*this);
    res |= b;
    return res;
}

inline Byte & Byte::operator&=(const Byte & b)
{
    return (*this &= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator&=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) &= b;
    return *this;
}

inline Byte Byte::operator&(const Byte & b) const
{
    Byte res(*this);
    res &= b;
    return res;
}

inline Byte Byte::operator&(const std::uint8_t & b) const
{
    Byte res(*this);
    res &= b;
    return res;
}

inline Byte & Byte::operator^=(const Byte & b)
{
    return (*this ^= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator^=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) ^= b;
    return *this;
}

inline Byte Byte::operator^(const Byte & b) const
{
    Byte res(*this);
    res ^= b;
    return res;
}

inline Byte Byte::operator^(const std::uint8_t & b) const
{
    Byte res(*this);
    res ^= b;
    return res;
}

inline Byte & Byte::operator>>=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) >>= b;
    return *this;
}

inline Byte Byte::operator>>(const std::uint8_t & b) const
{
    Byte res(*this);
    res >>= b;
    return res;
}

inline Byte & Byte::operator<<=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) <<= b;
    return *this;
}

inline Byte Byte::operator<<(const std::uint8_t & b) const
{
    Byte res(*this);
    res <<= b;
    return res;
}

inline Byte & Byte::operator++()
{
    return (*this += 1);
}

inline Byte Byte::operator++(int) const
{
    Byte res(*this);
    ++res;
    return res;
}

inline Byte & Byte::operator--()
{
    return (*this -= 1);
}

inline Byte Byte::operator--(int) const
{
    Byte res(*this);
    --res;
    return res;
}

inline Byte & Byte::operator+=(const Byte & b)
{
    return (*this += *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator+=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) += b;
    return *this;
}

inline Byte Byte::operator+(const Byte & b) const
{
    Byte res(*this);
    res += b;
    return res;
}

inline Byte Byte::operator+(const std::uint8_t & b) const
{
    Byte res(*this);
    res += b;
    return res;
}

inline Byte & Byte::operator-=(const Byte & b)
{
    return (*this -= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator-=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) -= b;
    return *this;
}

inline Byte Byte::operator-(const Byte & b) const
{
    Byte res(*this);
    res -= b;
    return res;
}

inline Byte Byte::operator-(const std::uint8_t & b) const
{
    Byte res(*this);
    res -= b;
    return res;
}

inline Byte & Byte::operator*=(const Byte & b)
{
    return (*this *= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator*=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) *= b;
    return *this;
}

inline Byte Byte::operator*(const Byte & b) const
{
    Byte res(*this);
    res *= b;
    return res;
}

inline Byte Byte::operator*(const std::uint8_t & b) const
{
    Byte res(*this);
    res *= b;
    return res;
}

inline Byte & Byte::operator/=(const Byte & b)
{
    return (*this /= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator/=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) /= b;
    return *this;
}

inline Byte Byte::operator/(const Byte & b) const
{
    Byte res(*this);
    res /= b;
    return res;
}

inline Byte Byte::operator/(const std::uint8_t & b) const
{
    Byte res(*this);
    res /= b;
    return res;
}

inline Byte & Byte::operator%=(const Byte & b)
{
    return (*this %= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline Byte & Byte::operator%=(const std::uint8_t & b)
{
    *bytes::Pointer(m_ptr, m_index) %= b;
    return *this;
}

inline Byte Byte::operator%(const Byte & b) const
{
    Byte res(*this);
    res %= b;
    return res;
}

inline Byte Byte::operator%(const std::uint8_t & b) const
{
    Byte res(*this);
    res %= b;
    return res;
}

inline Bit Byte::operator[](const std::uint8_t & i)
{
    return {m_ptr, i, m_index};
}

inline const Bit Byte::operator[](const std::uint8_t & i) const
{
    return {const_cast<std::shared_ptr<std::uint8_t> &>(m_ptr), i, m_index};
}

inline bool Byte::operator==(const Byte & b) const
{
    return (*this == *bytes::Pointer(b.m_ptr, b.m_index));
}

inline bool Byte::operator==(const std::uint8_t & b) const
{
    return *bytes::Pointer(m_ptr, m_index) == b;
}

inline bool Byte::operator!=(const Byte & b) const
{
    return !(*this == b);
}

inline bool Byte::operator!=(const std::uint8_t & b) const
{
    return !(*this == b);
}

inline bool Byte::operator<(const Byte & b) const
{
    return (*this < *bytes::Pointer(b.m_ptr, b.m_index));
}

inline bool Byte::operator<(const std::uint8_t & b) const
{
    return *bytes::Pointer(m_ptr, m_index) < b;
}

inline bool Byte::operator<=(const Byte & b) const
{
    return (*this <= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline bool Byte::operator<=(const std::uint8_t & b) const
{
    return *bytes::Pointer(m_ptr, m_index) <= b;
}

inline bool Byte::operator>(const Byte & b) const
{
    return (*this > *bytes::Pointer(b.m_ptr, b.m_index));
}

inline bool Byte::operator>(const std::uint8_t & b) const
{
    return *bytes::Pointer(m_ptr, m_index) > b;
}

inline bool Byte::operator>=(const Byte & b) const
{
    return (*this >= *bytes::Pointer(b.m_ptr, b.m_index));
}

inline bool Byte::operator>=(const std::uint8_t & b) const
{
    return *bytes::Pointer(m_ptr, m_index) >= b;
}

inline Byte operator|(const std::uint8_t & a, const Byte & b)
{
    return b | a;
}

inline Byte operator&(const std::uint8_t & a, const Byte & b)
{
    return b & a;    
}

inline Byte operator^(const std::uint8_t & a, const Byte & b)
{
    return b ^ a;
}

inline Byte operator+(const std::uint8_t & a, const Byte & b)
{
    return b + a;
}

inline Byte operator-(const std::uint8_t & a, const Byte & b)
{
    return Byte(a) - b;
}

inline Byte operator*(const std::uint8_t & a, const Byte & b)
{
    return b * a;
}

inline Byte operator/(const std::uint8_t & a, const Byte & b)
{
    return Byte(a) / b;
}

inline Byte operator%(const std::uint8_t & a, const Byte & b)
{
    return Byte(a) % b;
}

inline bool operator==(const std::uint8_t & a, const Byte & b)
{
    return b == a;
}

inline bool operator!=(const std::uint8_t & a, const Byte & b)
{
    return b != a;
}

inline bool operator<(const std::uint8_t & a, const Byte & b)
{
    return b > a;
}

inline bool operator<=(const std::uint8_t & a, const Byte & b)
{
    return b >= a;
}

inline bool operator>(const std::uint8_t & a, const Byte & b)
{
    return b < a;
}

inline bool operator>=(const std::uint8_t & a, const Byte & b)
{
    return b <= a;
}

#endif //!BYTE_H_