#ifndef BIT_H_
#define BIT_H_

#include <cstdint>
#include <memory>

#include "byte/One.h"
#include "bytes/Pointer.h"

class Bit
{
private:
    std::uint8_t m_offset;
    std::shared_ptr<std::uint8_t> m_ptr;
    std::size_t m_index;
public:
    inline Bit();
    inline Bit(const std::uint8_t & b);
    inline Bit(const std::uint8_t & b, const std::uint8_t & off);
    inline Bit(const std::shared_ptr<std::uint8_t> & b);
    inline Bit(const std::shared_ptr<std::uint8_t> & b, const std::uint8_t & off);
    inline Bit(const std::shared_ptr<std::uint8_t> & b, const std::uint8_t & off,
        const std::size_t i);
    inline ~Bit();
public:
    inline Bit(const Bit & cpy);
    inline Bit(Bit && mov);
public:
    inline Bit & operator=(Bit && b);
    inline Bit & operator=(const Bit & b);
    inline Bit & operator=(const bool & b);
    inline Bit & operator=(const std::uint8_t & b);
public:
    inline operator bool() const;
    inline operator std::uint8_t() const;
public:
    inline Bit operator~() const;
public:
    inline Bit & operator|=(const Bit & b);
    inline Bit & operator|=(const bool & b);
    inline Bit & operator|=(const std::uint8_t & b);
public:
    inline Bit operator|(const Bit & b) const;
    inline Bit operator|(const bool & b) const;
    inline Bit operator|(const std::uint8_t & b) const;
public:
    inline Bit & operator&=(const Bit & b);
    inline Bit & operator&=(const bool & b);
    inline Bit & operator&=(const std::uint8_t & b);
public:
    inline Bit operator&(const Bit & b) const;
    inline Bit operator&(const bool & b) const;
    inline Bit operator&(const std::uint8_t & b) const;
public:
    inline Bit & operator^=(const Bit & b);
    inline Bit & operator^=(const bool & b);
    inline Bit & operator^=(const std::uint8_t & b);
public:
    inline Bit operator^(const Bit & b) const;
    inline Bit operator^(const bool & b) const;
    inline Bit operator^(const std::uint8_t & b) const;
public:
    inline bool operator!() const;
public:
    inline bool operator||(const Bit & b) const;
    inline bool operator||(const bool & b) const;
    inline bool operator||(const std::uint8_t & b) const;
public:
    inline bool operator&&(const Bit & b) const;
    inline bool operator&&(const bool & b) const;
    inline bool operator&&(const std::uint8_t & b) const;
public:
    inline bool operator==(const Bit & b) const;
    inline bool operator==(const bool & b) const;
    inline bool operator==(const std::uint8_t & b) const;
public:
    inline bool operator!=(const Bit & b) const;
    inline bool operator!=(const bool & b) const;
    inline bool operator!=(const std::uint8_t & b) const;
};

inline Bit::Bit() :
    m_ptr(new std::uint8_t(0)),
    m_offset(0),
    m_index(0)
{}

inline Bit::Bit(const std::uint8_t & b) :
    m_ptr(new std::uint8_t(b)),
    m_offset(0),
    m_index(0)
{}

inline Bit::Bit(const std::uint8_t & b, const std::uint8_t & off) :
    m_ptr(new std::uint8_t(b)),
    m_offset(off),
    m_index(0)
{}

inline Bit::Bit(const std::shared_ptr<std::uint8_t> & b) :
    m_ptr(b),
    m_offset(0),
    m_index(0)
{}

inline Bit::Bit(const std::shared_ptr<std::uint8_t> & b, const std::uint8_t & off) :
    m_ptr(b),
    m_offset(off),
    m_index(0)
{}

inline Bit::Bit(const std::shared_ptr<std::uint8_t> & b, const std::uint8_t & off,
    const std::size_t i) :
        m_ptr(b),
        m_offset(off),
        m_index(i)
{}

inline Bit::~Bit()
{
    m_ptr = nullptr;
    m_offset = 0;
    m_index = 0;
}

inline Bit::Bit(const Bit & cpy) :
    m_ptr(new std::uint8_t(static_cast<std::uint8_t>(cpy))),
    m_offset(0),
    m_index(0)
{}

inline Bit::Bit(Bit && mov) :
    m_ptr(mov.m_ptr),
    m_offset(mov.m_offset),
    m_index(mov.m_index)
{
    mov.m_ptr = std::make_shared<std::uint8_t>(0);
    mov.m_offset = 0;
    mov.m_index = 0;
}

inline Bit & Bit::operator=(Bit && b)
{
    m_ptr = b.m_ptr;
    m_offset = b.m_offset;
    m_index = b.m_index;
    b.m_ptr = std::make_shared<std::uint8_t>(0);
    b.m_offset = 0;
    b.m_index = 0;
    return *this;
}

inline Bit & Bit::operator=(const Bit & b)
{
    return (*this = (static_cast<bool>(b)));
}

inline Bit & Bit::operator=(const bool & b)
{
    *bytes::Pointer(m_ptr, m_index) &= ~byte::One(m_offset);
    *bytes::Pointer(m_ptr, m_index) |= byte::One(m_offset, b);
    return *this;
}

inline Bit & Bit::operator=(const std::uint8_t & b)
{
    return (*this = (b >= 1));
}

inline Bit::operator bool() const
{
    return *bytes::Pointer(m_ptr, m_index) & byte::One(m_offset);
}

inline Bit::operator std::uint8_t() const
{
    if (*bytes::Pointer(m_ptr, m_index) & byte::One(m_offset)) 
        return std::uint8_t(1);
    return std::uint8_t(0);
}

inline Bit Bit::operator~() const
{
    Bit res(*this);
    *bytes::Pointer(res.m_ptr, m_index) = 
        ~*(bytes::Pointer(res.m_ptr, m_index));
    *bytes::Pointer(res.m_ptr, m_index) &= byte::One(m_offset);
    return res;
}

inline Bit & Bit::operator|=(const Bit & b)
{
    return (*this |= static_cast<bool>(b));
}

inline Bit & Bit::operator|=(const bool & b)
{
    *bytes::Pointer(m_ptr, m_index) |= byte::One(m_offset, b);
    return *this;
}

inline Bit & Bit::operator|=(const std::uint8_t & b)
{
    return (*this |= (b >= 1));
}

inline Bit Bit::operator|(const Bit & b) const
{
    Bit res(*this);
    res |= b;
    return res;
}

inline Bit Bit::operator|(const bool & b) const
{
    Bit res(*this);
    res |= b;
    return res;
}

inline Bit Bit::operator|(const std::uint8_t & b) const
{
    Bit res(*this);
    res |= b;
    return res;
}

inline Bit & Bit::operator&=(const Bit & b)
{
    return (*this &= static_cast<bool>(b));
}

inline Bit & Bit::operator&=(const bool & b)
{
    *bytes::Pointer(m_ptr, m_index) &= (byte::One(m_offset, b) | 
        ~byte::One(m_offset));
    return *this;
}

inline Bit & Bit::operator&=(const std::uint8_t & b)
{
    return (*this &= (b >= 1));
}

inline Bit Bit::operator&(const Bit & b) const
{
    Bit res(*this);
    res &= b;
    return res;
}

inline Bit Bit::operator&(const bool & b) const
{
    Bit res(*this);
    res &= b;
    return res;
}

inline Bit Bit::operator&(const std::uint8_t & b) const
{
    Bit res(*this);
    res &= b;
    return res;
}

inline Bit & Bit::operator^=(const Bit & b)
{
    return (*this ^= static_cast<bool>(b));
}

inline Bit & Bit::operator^=(const bool & b)
{
    *bytes::Pointer(m_ptr, m_index) ^= byte::One(m_offset, b);
    return *this;
}

inline Bit & Bit::operator^=(const std::uint8_t & b)
{
    return (*this ^= (b >= 1));
}

inline Bit Bit::operator^(const Bit & b) const
{
    Bit res(*this);
    res ^= b;
    return res;
}

inline Bit Bit::operator^(const bool & b) const
{
    Bit res(*this);
    res ^= b;
    return res;
}

inline Bit Bit::operator^(const std::uint8_t & b) const
{
    Bit res(*this);
    res ^= b;
    return res;
}

inline bool Bit::operator!() const
{
    return !static_cast<bool>(*this);
}

inline bool Bit::operator||(const Bit & b) const
{
    return static_cast<bool>(*this) || static_cast<bool>(b);
}

inline bool Bit::operator||(const bool & b) const
{
    return static_cast<bool>(*this) || b;
}

inline bool Bit::operator||(const std::uint8_t & b) const
{
    return static_cast<bool>(*this) || (b >= 1);
}

inline bool Bit::operator&&(const Bit & b) const
{
    return static_cast<bool>(*this) && static_cast<bool>(b);
}

inline bool Bit::operator&&(const bool & b) const
{
    return static_cast<bool>(*this) && b;
}

inline bool Bit::operator&&(const std::uint8_t & b) const
{
    return static_cast<bool>(*this) && (b >= 1);
}

inline bool Bit::operator==(const Bit & b) const
{
    return static_cast<bool>(*this) == static_cast<bool>(b);
}

inline bool Bit::operator==(const bool & b) const
{
    return static_cast<bool>(*this) == b;
}

inline bool Bit::operator==(const std::uint8_t & b) const
{
    return static_cast<bool>(*this) == (b >= 1);
}

inline bool Bit::operator!=(const Bit & b) const
{
    return !(*this == b);
}

inline bool Bit::operator!=(const bool & b) const
{
    return !(*this == b);
}

inline bool Bit::operator!=(const std::uint8_t & b) const
{
    return !(*this == b);
}

inline Bit operator|(const bool & a, const Bit & b)
{
    return b | a;
}

inline Bit operator|(const std::uint8_t & a, const Bit & b)
{
    return b | a;
}

inline Bit operator&(const bool & a, const Bit & b)
{
    return b & a;
}

inline Bit operator&(const std::uint8_t & a, const Bit & b)
{
    return b & a;
}

inline Bit operator^(const bool & a, const Bit & b)
{
    return b ^ a;
}

inline Bit operator^(const std::uint8_t & a, const Bit & b)
{
    return b ^ a;
}

inline bool operator||(const bool & a, const Bit & b)
{
    return b || a;
}

inline bool operator||(const std::uint8_t & a, const Bit & b)
{
    return b || a;
}

inline bool operator&&(const bool & a, const Bit & b)
{
    return b && a;
}

inline bool operator&&(const std::uint8_t & a, const Bit & b)
{
    return b && a;
}

inline bool operator==(const bool & a, const Bit & b)
{
    return b == a;
}

inline bool operator==(const std::uint8_t & a, const Bit & b)
{
    return b == a;
}

inline bool operator!=(const bool & a, const Bit & b)
{
    return b != a;
}

inline bool operator!=(const std::uint8_t & a, const Bit & b)
{
    return b != a;
}

#endif //!BIT_H_