#ifndef BYTE_H_
#define BYTE_H_

#include "Bit.h"

#include <cstdint>
#include <memory>

#include "bytes/ptr/Object.h"
#include "bytes/ptr/Segment.h"

class Byte
{
private:
    static inline void Default(Byte & b);
    static inline bool Validation(Byte & b);
private:
    std::uint8_t m_offset;
    std::size_t m_index;
    std::shared_ptr<bytes::ptr::Segment> m_segment;
public:
    inline Byte();
    inline Byte(const std::uint8_t & b);
    inline Byte(const std::shared_ptr<bytes::ptr::Segment> & b);
    inline Byte(const std::shared_ptr<bytes::ptr::Segment> & b,
        const std::size_t & i);
    inline Byte(const std::shared_ptr<bytes::ptr::Segment> & b,
        const std::size_t & i, const std::uint8_t & off);
public:
    inline ~Byte();
public:
    inline Byte(const Byte & cpy);
    inline Byte(Byte && mov);
public:
    inline Byte & operator=(Byte && b);
    inline Byte & operator=(const Byte & b);
    inline Byte & operator=(const std::uint8_t & b);
public:
    inline bool IsSameObject(const Byte & b) const;
    inline bool 
        IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const;
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
    inline Byte operator++(int);
public:
    inline Byte & operator--();
    inline Byte operator--(int);
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
public:
    inline void Swap(Byte & b);
};

inline void Byte::Default(Byte & b)
{
    b.m_segment = std::make_shared<bytes::ptr::Segment>(0, 1,
        std::make_shared<bytes::ptr::Object>(1));
    b.m_segment->ReverseAt(0) = 0;
    b.m_index = 0;
    b.m_offset = 0;
}

inline bool Byte::Validation(Byte & b)
{
    if (!b.m_segment && !*(b.m_segment)) 
    {
        Default(b);
        return false;
    }
    return true;
}

inline Byte::Byte() :
    m_segment(new bytes::ptr::Segment(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_index(0),
    m_offset(0)
{
    m_segment->ReverseAt(0) = 0;
}

inline Byte::Byte(const std::uint8_t & b) :
    m_segment(new bytes::ptr::Segment(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_index(0),
    m_offset(0)
{
    m_segment->ReverseAt(0) = b;
}

inline Byte::Byte(const std::shared_ptr<bytes::ptr::Segment> & b) :
    m_segment(b),
    m_index(0),
    m_offset(0)
{
    Validation(*this);
}

inline Byte::Byte(const std::shared_ptr<bytes::ptr::Segment> & b,
    const std::size_t & i) :
        m_segment(b),
        m_index(i),
        m_offset(0)
{
    Validation(*this);
}

inline Byte::Byte(const std::shared_ptr<bytes::ptr::Segment> & b,
    const std::size_t & i, const std::uint8_t & off) :
        m_segment(b),
        m_index(i),
        m_offset(off)
{
    Validation(*this);
}

inline Byte::~Byte()
{
    m_segment = nullptr;
    m_index = 0;
    m_offset = 0;
}

inline Byte::Byte(const Byte & cpy) :
    m_segment(new bytes::ptr::Segment(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_index(0),
    m_offset(0)
{
    (*this) = cpy;
}

inline Byte::Byte(Byte && mov) :
    m_segment(mov.m_segment),
    m_index(mov.m_index),
    m_offset(mov.m_offset)
{
    Default(mov);
}

inline Byte & Byte::operator=(Byte && b)
{
    return (*this = b.m_segment->ReverseAt(m_index, m_offset));
}

inline Byte & Byte::operator=(const Byte & b)
{
    return (*this = b.m_segment->ReverseAt(m_index, m_offset));
}

inline Byte & Byte::operator=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) = b;
    return *this;
}

inline bool Byte::IsSameObject(const Byte & b) const
{
    return m_segment->IsSameObject(*(b.m_segment));
}

inline bool 
    Byte::IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const
{
    return m_segment->IsSameObject(b);
}

inline Byte::operator std::uint8_t() const
{
    return m_segment->ReverseAt(m_index, m_offset);
}

inline Byte Byte::operator~() const
{
    Byte res(*this);
    res = ~static_cast<std::uint8_t>(res);
    return res;
}

inline Byte & Byte::operator|=(const Byte & b)
{
    return (*this |= static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator|=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) |= b;
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
    return (*this &= static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator&=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) &= b;
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
    return (*this ^= static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator^=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) ^= b;
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
    m_segment->ReverseAt(m_index, m_offset) >>= b;
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
    m_segment->ReverseAt(m_index, m_offset) <<= b;
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

inline Byte Byte::operator++(int)
{
    Byte res(*this);
    ++(*this);
    return res;
}

inline Byte & Byte::operator--()
{
    return (*this -= 1);
}

inline Byte Byte::operator--(int)
{
    Byte res(*this);
    --(*this);
    return res;
}

inline Byte & Byte::operator+=(const Byte & b)
{
    return (*this += static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator+=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) += b;
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
    return (*this -= static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator-=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) -= b;
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
    return (*this *= static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator*=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) *= b;
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
    return (*this /= static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator/=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) /= b;
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
    return (*this %= static_cast<std::uint8_t>(b));
}

inline Byte & Byte::operator%=(const std::uint8_t & b)
{
    m_segment->ReverseAt(m_index, m_offset) %= b;
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
    return {m_segment, i, m_index, m_offset};
}

inline const Bit Byte::operator[](const std::uint8_t & i) const
{
    Bit res{m_segment->ReverseAt(m_index, m_offset), i};
    return res;
}

inline bool Byte::operator==(const Byte & b) const
{
    return (*this == static_cast<std::uint8_t>(b));
}

inline bool Byte::operator==(const std::uint8_t & b) const
{
    return m_segment->ReverseAt(m_index, m_offset) == b;
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
    return (*this < static_cast<std::uint8_t>(b));
}

inline bool Byte::operator<(const std::uint8_t & b) const
{
    return m_segment->ReverseAt(m_index, m_offset) < b;
}

inline bool Byte::operator<=(const Byte & b) const
{
    return (*this <= static_cast<std::uint8_t>(b));
}

inline bool Byte::operator<=(const std::uint8_t & b) const
{
    return m_segment->ReverseAt(m_index, m_offset) <= b;
}

inline bool Byte::operator>(const Byte & b) const
{
    return (*this > static_cast<std::uint8_t>(b));
}

inline bool Byte::operator>(const std::uint8_t & b) const
{
    return m_segment->ReverseAt(m_index, m_offset) > b;
}

inline bool Byte::operator>=(const Byte & b) const
{
    return (*this >= static_cast<std::uint8_t>(b));
}

inline bool Byte::operator>=(const std::uint8_t & b) const
{
    return m_segment->ReverseAt(m_index, m_offset) >= b;
}

inline void Byte::Swap(Byte & b)
{
    auto segment = m_segment;
    auto index = m_index;
    auto offset = m_offset;
    m_segment = b.m_segment;
    m_index = b.m_index;
    m_offset = b.m_offset;
    b.m_segment = segment;
    b.m_index = index;
    b.m_offset = offset;
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