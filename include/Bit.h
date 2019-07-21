#ifndef BIT_H_
#define BIT_H_

#include <cstdint>
#include <memory>

#include "byte/One.h"
#include "bytes/Pointer.h"
#include "bytes/ptr/Segment.h"

class Bit
{
private:
    static inline void Default(Bit & b);
    static inline bool Validation(Bit & b);
private:
    std::uint8_t m_offset;
    std::shared_ptr<bytes::Pointer> m_ptr;
    std::shared_ptr<bytes::ptr::Segment> m_segment;
public:
    inline Bit();
    inline Bit(const bool & b);
    inline Bit(const std::uint8_t & b);
    inline Bit(const std::uint8_t & b, const std::uint8_t & off);
    inline Bit(const std::shared_ptr<bytes::Pointer> & b);
    inline Bit(const std::shared_ptr<bytes::Pointer> & b, 
        const std::uint8_t & off);
    inline Bit(const std::shared_ptr<bytes::Pointer> & b, 
        const std::uint8_t & off, 
        const std::shared_ptr<bytes::ptr::Segment> seg);
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
    inline bool IsSamePointer(const Bit & b) const;
    inline bool IsSamePointer(const std::shared_ptr<bytes::Pointer> & b) const;
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

inline void Bit::Default(Bit & b)
{
    b.m_ptr = std::make_shared<bytes::Pointer>(1);
    b.m_offset = 0;
    b.m_segment = b.m_ptr->Share(0, 1);
    b.m_ptr->At(0) = 0;
}

inline bool Bit::Validation(Bit & b)
{
    if (!b.m_ptr) 
    {  
        Default(b);
        return false;
    }
    return true;
}

inline Bit::Bit() :
    m_ptr(new bytes::Pointer(1)),
    m_offset(0),
    m_segment(m_ptr->Share(0, 1))
{
    m_ptr->At(0) = 0;
}

inline Bit::Bit(const bool & b) :
    m_ptr(new bytes::Pointer(1)),
    m_offset(0),
    m_segment(m_ptr->Share(0, 1))
{
    *this = b;
}

inline Bit::Bit(const std::uint8_t & b) :
    m_ptr(new bytes::Pointer(1)),
    m_offset(0),
    m_segment(m_ptr->Share(0, 1))
{
    *this = b;
}

inline Bit::Bit(const std::uint8_t & b, const std::uint8_t & off) :
    m_ptr(new bytes::Pointer(1)),
    m_offset(off),
    m_segment(m_ptr->Share(0, 1))
{
    m_ptr->At(0) = b;
}

inline Bit::Bit(const std::shared_ptr<bytes::Pointer> & b) :
    m_ptr(b),
    m_offset(0)
{
    if (Validation(*this)) m_segment = m_ptr->Share(0, 1);
}

inline Bit::Bit(const std::shared_ptr<bytes::Pointer> & b, 
    const std::uint8_t & off) :
        m_ptr(b),
        m_offset(off)
{
    if (Validation(*this)) m_segment = m_ptr->Share(0, 1);
}

inline Bit::Bit(const std::shared_ptr<bytes::Pointer> & b, 
    const std::uint8_t & off, const std::shared_ptr<bytes::ptr::Segment> seg) :
        m_ptr(b),
        m_offset(off)
{
    if (Validation(*this))
    {
        if (seg && m_ptr->Has(seg)) m_segment = seg;
        else if (seg)
            m_segment = m_ptr->Share(seg->Begin(), seg->End());
        else  m_segment = m_ptr->Share(0, 1);
    }
}

inline Bit::~Bit()
{
    if (m_ptr) m_ptr->Reset(m_segment);
    m_segment = nullptr;
    m_ptr = nullptr;
    m_offset = 0;
}

inline Bit::Bit(const Bit & cpy) :
    m_ptr(new bytes::Pointer(1)),
    m_offset(0)
{
    m_segment = m_ptr->Share(0, 1);
    *this = static_cast<bool>(cpy);
}

inline Bit::Bit(Bit && mov) :
    m_ptr(mov.m_ptr),
    m_offset(mov.m_offset),
    m_segment(mov.m_segment)
{
    Default(mov);
}

inline Bit & Bit::operator=(Bit && b)
{
    m_ptr = b.m_ptr;
    m_offset = b.m_offset;
    m_segment = b.m_segment;
    Default(b);
    return *this;
}

inline Bit & Bit::operator=(const Bit & b)
{
    return (*this = (static_cast<bool>(b)));
}

inline Bit & Bit::operator=(const bool & b)
{
    m_ptr->At(m_segment, 0) &= ~byte::One(m_offset);
    m_ptr->At(m_segment, 0) |= byte::One(m_offset, b);
    return *this;
}

inline Bit & Bit::operator=(const std::uint8_t & b)
{
    return (*this = (b >= 1));
}

inline bool Bit::IsSamePointer(const Bit & b) const
{
    return m_ptr == b.m_ptr;
}

inline bool 
    Bit::IsSamePointer(const std::shared_ptr<bytes::Pointer> & b) const
{
    return m_ptr == b;
}

inline Bit::operator bool() const
{
    return m_ptr->At(m_segment, 0) & byte::One(m_offset);
}

inline Bit::operator std::uint8_t() const
{
    if (m_ptr->At(m_segment, 0) & byte::One(m_offset))
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
    m_ptr->At(m_segment, 0) |= byte::One(m_offset, b);
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
    m_ptr->At(m_segment, 0) &= (byte::One(m_offset, b) | 
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
    m_ptr->At(m_segment, 0) ^= byte::One(m_offset, b);
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