#ifndef BIT_H_
#define BIT_H_

#include <cstdint>
#include <memory>

#include "byte/One.h"
#include "bytes/ptr/Segment.h"
#include "bytes/ptr/Object.h"

class Bit
{
private:
    static inline void Default(Bit & b);
    static inline bool Validation(Bit & b);
private:
    std::uint8_t m_offset;
    std::size_t m_index;
    std::shared_ptr<bytes::ptr::Segment> m_segment;
public:
    inline Bit();
    inline Bit(const bool & b);
    inline Bit(const std::uint8_t & b);
    inline Bit(const std::uint8_t & b, const std::uint8_t & off);
    inline Bit(const std::shared_ptr<bytes::ptr::Segment> & b);
    inline Bit(const std::shared_ptr<bytes::ptr::Segment> & b, 
        const std::uint8_t & off);
    inline Bit(const std::shared_ptr<bytes::ptr::Segment> & b, 
        const std::uint8_t & off, const std::size_t & i);
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
    inline bool IsSameObject(const Bit & b) const;
    inline bool 
        IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const;
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
public:
    inline void Swap(Bit & b);
};

inline void Bit::Default(Bit & b)
{
    b.m_offset = 0;
    b.m_index = 0;
    b.m_segment = std::make_shared<bytes::ptr::Segment>(0, 1, 
        std::make_shared<bytes::ptr::Object>(1));
    b.m_segment->ReverseAt(0) = 0;
}

inline bool Bit::Validation(Bit & b)
{
    if (!b.m_segment && !*(b.m_segment)) 
    {  
        Default(b);
        return false;
    }
    return true;
}

inline Bit::Bit() :
    m_segment(std::make_shared<bytes::ptr::Segment>(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_offset(0),
    m_index(0)
{
    m_segment->ReverseAt(0) = 0;
}

inline Bit::Bit(const bool & b) :
    m_segment(std::make_shared<bytes::ptr::Segment>(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_offset(0),
    m_index(0)
{
    *this = b;
}

inline Bit::Bit(const std::uint8_t & b) :
    m_segment(std::make_shared<bytes::ptr::Segment>(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_offset(0),
    m_index(0)
{
    *this = b;
}

inline Bit::Bit(const std::uint8_t & b, const std::uint8_t & off) :
    m_segment(std::make_shared<bytes::ptr::Segment>(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_offset(off),
    m_index(0)
{
    m_segment->ReverseAt(0) = b;
}

inline Bit::Bit(const std::shared_ptr<bytes::ptr::Segment> & b) :
    m_segment(b),
    m_offset(0),
    m_index(0)
{
    Validation(*this);
}

inline Bit::Bit(const std::shared_ptr<bytes::ptr::Segment> & b, 
    const std::uint8_t & off) :
        m_segment(b),
        m_offset(off),
        m_index(0)
{
    Validation(*this);
}

inline Bit::Bit(const std::shared_ptr<bytes::ptr::Segment> & b, 
    const std::uint8_t & off, const std::size_t & i) :
        m_segment(b),
        m_offset(off),
        m_index(i)
{
    Validation(*this);
}

inline Bit::~Bit()
{
    m_segment = nullptr;
    m_offset = 0;
    m_index = 0;
}

inline Bit::Bit(const Bit & cpy) :
    m_segment(std::make_shared<bytes::ptr::Segment>(0, 1, 
        std::make_shared<bytes::ptr::Object>(1))),
    m_offset(0),
    m_index(0)
{
    *this = static_cast<bool>(cpy);
}

inline Bit::Bit(Bit && mov) :
    m_segment(mov.m_segment),
    m_offset(mov.m_offset),
    m_index(mov.m_index)
{
    Default(mov);
}

inline Bit & Bit::operator=(Bit && b)
{
    return (*this = (static_cast<bool>(b)));
}

inline Bit & Bit::operator=(const Bit & b)
{
    return (*this = (static_cast<bool>(b)));
}

inline Bit & Bit::operator=(const bool & b)
{
    m_segment->ReverseAt(m_index) &= ~byte::One(m_offset);
    m_segment->ReverseAt(m_index) |= byte::One(m_offset, b);
    return *this;
}

inline Bit & Bit::operator=(const std::uint8_t & b)
{
    return (*this = (b >= 1));
}

inline bool Bit::IsSameObject(const Bit & b) const
{
    return m_segment->IsSameObject(*(b.m_segment));
}

inline bool Bit::
    IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const
{
    return m_segment->IsSameObject(b);
}

inline Bit::operator bool() const
{
    return m_segment->ReverseAt(m_index) & byte::One(m_offset);
}

inline Bit::operator std::uint8_t() const
{
    if (m_segment->ReverseAt(m_index) & byte::One(m_offset)) 
        return std::uint8_t(1);
    return std::uint8_t(0);
}

inline Bit Bit::operator~() const
{
    Bit res(*this);
    res = !res;
    return res;
}

inline Bit & Bit::operator|=(const Bit & b)
{
    return (*this |= static_cast<bool>(b));
}

inline Bit & Bit::operator|=(const bool & b)
{
    m_segment->ReverseAt(m_index) |= byte::One(m_offset, b);
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
    m_segment->ReverseAt(m_index) &= 
        (byte::One(m_offset, b) | ~byte::One(m_offset));
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
    m_segment->ReverseAt(m_index) ^= byte::One(m_offset, b);
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

inline void Bit::Swap(Bit & b)
{
    auto offset = m_offset;
    auto index = m_index;
    auto segment = m_segment;
    m_offset = b.m_offset;
    m_index = b.m_index;
    m_segment = b.m_segment;
    b.m_offset = offset;
    b.m_index = index;
    b.m_segment = segment; 
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