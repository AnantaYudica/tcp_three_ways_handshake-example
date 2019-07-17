#ifndef BYTE_H_
#define BYTE_H_

#include "Bit.h"

#include <cstdint>
#include <memory>

class Byte
{
private:
    std::shared_ptr<std::uint8_t> m_ptr;
public:
    inline Byte();
    inline Byte(const std::uint8_t & b);
    inline Byte(const std::shared_ptr<std::uint8_t> & b);
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
    m_ptr(new std::uint8_t(0))
{}

inline Byte::Byte(const std::uint8_t & b) :
    m_ptr(new std::uint8_t(b))
{}

inline Byte::Byte(const std::shared_ptr<std::uint8_t> & b) :
    m_ptr(b)
{}

inline Byte::~Byte()
{
    m_ptr = nullptr;
}

inline Byte::Byte(const Byte & cpy) :
    m_ptr(new std::uint8_t(*(cpy.m_ptr)))
{}

inline Byte::Byte(Byte && mov) :
    m_ptr(mov.m_ptr)
{
    mov.m_ptr = std::make_shared<std::uint8_t>(0);
}

inline Byte & Byte::operator=(Byte && b)
{
    auto cpy = m_ptr;
    m_ptr = b.m_ptr;
    b.m_ptr = cpy;
    *b.m_ptr = 0;
    return *this;
}

inline Byte & Byte::operator=(const Byte & b)
{
    return (*this = *(b.m_ptr));
}

inline Byte & Byte::operator=(const std::uint8_t & b)
{
    *m_ptr = b;
    return *this;
}

inline Byte::operator std::uint8_t() const
{
    return *m_ptr;
}

inline Byte Byte::operator~() const
{
    Byte res(*this);
    *res.m_ptr = ~*(res.m_ptr);
    return res;
}

inline Byte & Byte::operator|=(const Byte & b)
{
    return (*this |= *(b.m_ptr));
}

inline Byte & Byte::operator|=(const std::uint8_t & b)
{
    *m_ptr |= b;
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
    return (*this &= *(b.m_ptr));
}

inline Byte & Byte::operator&=(const std::uint8_t & b)
{
    *m_ptr &= b;
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
    return (*this ^= *(b.m_ptr));
}

inline Byte & Byte::operator^=(const std::uint8_t & b)
{
    *m_ptr ^= b;
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
    *m_ptr >>= b;
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
    *m_ptr <<= b;
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
    return (*this += *(b.m_ptr));
}

inline Byte & Byte::operator+=(const std::uint8_t & b)
{
    *m_ptr += b;
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
    return (*this -= *(b.m_ptr));
}

inline Byte & Byte::operator-=(const std::uint8_t & b)
{
    *m_ptr -= b;
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
    return (*this *= *(b.m_ptr));
}

inline Byte & Byte::operator*=(const std::uint8_t & b)
{
    *m_ptr *= b;
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
    return (*this /= *(b.m_ptr));
}

inline Byte & Byte::operator/=(const std::uint8_t & b)
{
    *m_ptr /= b;
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
    return (*this %= *(b.m_ptr));
}

inline Byte & Byte::operator%=(const std::uint8_t & b)
{
    *m_ptr %= b;
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
    return {m_ptr, i};
}

inline const Bit Byte::operator[](const std::uint8_t & i) const
{
    return {m_ptr, i};
}

inline bool Byte::operator==(const Byte & b) const
{
    return (*this == *(b.m_ptr));
}

inline bool Byte::operator==(const std::uint8_t & b) const
{
    return *m_ptr == b;
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
    return (*this < *(b.m_ptr));
}

inline bool Byte::operator<(const std::uint8_t & b) const
{
    return *m_ptr < b;
}

inline bool Byte::operator<=(const Byte & b) const
{
    return (*this <= *(b.m_ptr));
}

inline bool Byte::operator<=(const std::uint8_t & b) const
{
    return *m_ptr <= b;
}

inline bool Byte::operator>(const Byte & b) const
{
    return (*this > *(b.m_ptr));
}

inline bool Byte::operator>(const std::uint8_t & b) const
{
    return *m_ptr > b;
}

inline bool Byte::operator>=(const Byte & b) const
{
    return (*this >= *(b.m_ptr));
}

inline bool Byte::operator>=(const std::uint8_t & b) const
{
    return *m_ptr >= b;
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