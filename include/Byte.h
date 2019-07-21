#ifndef BYTE_H_
#define BYTE_H_

#include "Bit.h"

#include <cstdint>
#include <memory>

#include "bytes/Pointer.h"
#include "bytes/ptr/Segment.h"

class Byte
{
private:
    static inline void Default(Byte & b);
    static inline bool Validation(Byte & b);
private:
    std::shared_ptr<bytes::Pointer> m_ptr;
    std::shared_ptr<bytes::ptr::Segment> m_segment;
public:
    inline Byte();
    inline Byte(const std::uint8_t & b);
    inline Byte(const std::shared_ptr<bytes::Pointer> & b);
    inline Byte(const std::shared_ptr<bytes::Pointer> & b, 
        const std::shared_ptr<bytes::ptr::Segment> & seg);
    inline ~Byte();
public:
    inline Byte(const Byte & cpy);
    inline Byte(Byte && mov);
public:
    inline Byte & operator=(Byte && b);
    inline Byte & operator=(const Byte & b);
    inline Byte & operator=(const std::uint8_t & b);
public:
    inline bool IsSamePointer(const Byte & b) const;
    inline bool IsSamePointer(const std::shared_ptr<bytes::Pointer> & b) const;
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
};

inline void Byte::Default(Byte & b)
{
    b.m_ptr = std::make_shared<bytes::Pointer>(1);
    b.m_ptr->At(0) = 0;
    b.m_segment = b.m_ptr->Share(0, 1);
}

inline bool Byte::Validation(Byte & b)
{
    if (!b.m_ptr && !*(b.m_ptr)) 
    {
        Default(b);
        return false;
    }
    return true;
}

inline Byte::Byte() :
    m_ptr(new bytes::Pointer(1)),
    m_segment(m_ptr->Share(0, 1))
{}

inline Byte::Byte(const std::uint8_t & b) :
    m_ptr(new bytes::Pointer(1)),
    m_segment(m_ptr->Share(0, 1))
{
    m_ptr->At(0) = b;
}

inline Byte::Byte(const std::shared_ptr<bytes::Pointer> & b) :
    m_ptr(b)
{
    if (Validation(*this)) m_segment = m_ptr->Share(0, 1);
}

inline Byte::Byte(const std::shared_ptr<bytes::Pointer> & b, 
    const std::shared_ptr<bytes::ptr::Segment> & seg) :
        m_ptr(b)
{
    if (Validation(*this))
    {
        if ((seg && *seg) && m_ptr->Has(seg))
            m_segment = seg;
        else if (seg && *seg)
            m_segment = m_ptr->Share(seg->Begin(), seg->End());
        else
            m_segment = m_ptr->Share(0, 1);
    }
}

inline Byte::~Byte()
{
    m_ptr->Reset(m_segment);
    m_segment = nullptr;
    m_ptr = nullptr;
}

inline Byte::Byte(const Byte & cpy) :
    m_ptr(new bytes::Pointer(1))
{
    m_segment = m_ptr->Share(0, 1);
    (*this) = cpy;
}

inline Byte::Byte(Byte && mov) :
    m_ptr(mov.m_ptr),
    m_segment(mov.m_segment)
{
    Default(mov);
}

inline Byte & Byte::operator=(Byte && b)
{
    m_ptr = b.m_ptr;
    m_segment = b.m_segment;
    Default(b);
    return *this;
}

inline Byte & Byte::operator=(const Byte & b)
{
    return (*this = b.m_ptr->At(m_segment, 0));
}

inline Byte & Byte::operator=(const std::uint8_t & b)
{
    m_ptr->At(m_segment, 0) = b;
    return *this;
}

inline bool Byte::IsSamePointer(const Byte & b) const
{
    return m_ptr == b.m_ptr;
}

inline bool 
    Byte::IsSamePointer(const std::shared_ptr<bytes::Pointer> & b) const
{
    return m_ptr == b;
}

inline Byte::operator std::uint8_t() const
{
    return m_ptr->At(m_segment, 0);
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
    m_ptr->At(m_segment, 0) |= b;
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
    m_ptr->At(m_segment, 0) &= b;
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
    m_ptr->At(m_segment, 0) ^= b;
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
    m_ptr->At(m_segment, 0) >>= b;
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
    m_ptr->At(m_segment, 0) <<= b;
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
    m_ptr->At(m_segment, 0) += b;
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
    m_ptr->At(m_segment, 0) -= b;
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
    m_ptr->At(m_segment, 0) *= b;
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
    m_ptr->At(m_segment, 0) /= b;
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
    m_ptr->At(m_segment, 0) %= b;
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
    return {m_ptr, i, m_ptr->Share(m_segment)};
}

inline const Bit Byte::operator[](const std::uint8_t & i) const
{
    Bit res{m_ptr->At(m_segment, 0), i};
    return res;
}

inline bool Byte::operator==(const Byte & b) const
{
    return (*this == static_cast<std::uint8_t>(b));
}

inline bool Byte::operator==(const std::uint8_t & b) const
{
    return m_ptr->At(m_segment, 0) == b;
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
    return m_ptr->At(m_segment, 0) < b;
}

inline bool Byte::operator<=(const Byte & b) const
{
    return (*this <= static_cast<std::uint8_t>(b));
}

inline bool Byte::operator<=(const std::uint8_t & b) const
{
    return m_ptr->At(m_segment, 0) <= b;
}

inline bool Byte::operator>(const Byte & b) const
{
    return (*this > static_cast<std::uint8_t>(b));
}

inline bool Byte::operator>(const std::uint8_t & b) const
{
    return m_ptr->At(m_segment, 0) > b;
}

inline bool Byte::operator>=(const Byte & b) const
{
    return (*this >= static_cast<std::uint8_t>(b));
}

inline bool Byte::operator>=(const std::uint8_t & b) const
{
    return m_ptr->At(m_segment, 0) >= b;
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