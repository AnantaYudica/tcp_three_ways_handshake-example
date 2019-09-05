#ifndef BYTES_ELEMENT_H_
#define BYTES_ELEMENT_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "Trait.h"
#include "ptr/Object.h"

namespace bytes
{

class Element
{
private:
    std::uint8_t m_offset;
    std::size_t m_index, m_begin, m_end;
    std::shared_ptr<bytes::ptr::Object> m_object;
    std::shared_ptr<bytes::Trait> m_trait;
public:
    inline Element();
    inline Element(const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed, const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
    inline Element(const std::size_t & i, const std::size_t & bg, 
        const std::size_t & ed, const std::uint8_t & off, 
        const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline ~Element();
public:
    inline Element(const Element & cpy);
    inline Element(Element && mov);
public:
    inline Element & operator=(const Element & cpy);
    inline Element & operator=(Element && mov);
    virtual inline Element & operator=(const std::uint8_t & v);
public:
    inline std::uint8_t GetOffset() const;
public:
    inline std::size_t GetIndex() const;
public:
    virtual inline std::size_t GetAbsoluteIndex() const;
public:
    inline std::size_t GetBeginIndex() const;
public:
    inline std::size_t GetEndIndex() const;
protected:
    inline std::shared_ptr<bytes::ptr::Object> GetObject();
    inline std::shared_ptr<const bytes::ptr::Object> GetObject() const;
protected:
    inline std::shared_ptr<bytes::Trait> GetTrait();
    inline std::shared_ptr<const bytes::Trait> GetTrait() const;
public:
    inline bool IsSameObject(const Element & elem) const;
    inline bool 
        IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const;
public:
    virtual inline operator std::uint8_t() const;
public:
    inline std::uint8_t operator~() const;
public:
    inline Element & operator|=(const Element & b);
    inline Element & operator|=(const std::uint8_t & b);
public:
    inline std::uint8_t operator|(const Element & b) const;
    inline std::uint8_t operator|(const std::uint8_t & b) const;
public:
    inline Element & operator&=(const Element & b);
    inline Element & operator&=(const std::uint8_t & b);
public:
    inline std::uint8_t operator&(const Element & b) const;
    inline std::uint8_t operator&(const std::uint8_t & b) const;
public:
    inline Element & operator^=(const Element & b);
    inline Element & operator^=(const std::uint8_t & b);
public:
    inline std::uint8_t operator^(const Element & b) const;
    inline std::uint8_t operator^(const std::uint8_t & b) const;
public:
    inline Element & operator>>=(const std::uint8_t & b);
public:
    inline std::uint8_t operator>>(const std::uint8_t & b) const;
public:
    inline Element & operator<<=(const std::uint8_t & b);
public:
    inline std::uint8_t operator<<(const std::uint8_t & b) const;
public:
    inline std::uint8_t operator+() const = delete;
public:
    inline std::uint8_t operator-() const = delete;
public:
    inline Element & operator++();
    inline std::uint8_t operator++(int);
public:
    inline Element & operator--();
    inline std::uint8_t operator--(int);
public:
    inline Element & operator+=(const Element & b);
    inline Element & operator+=(const std::uint8_t & b);
public:
    inline std::uint8_t operator+(const Element & b) const;
    inline std::uint8_t operator+(const std::uint8_t & b) const;
public:
    inline Element & operator-=(const Element & b);
    inline Element & operator-=(const std::uint8_t & b);
public:
    inline std::uint8_t operator-(const Element & b) const;
    inline std::uint8_t operator-(const std::uint8_t & b) const;
public:
    inline Element & operator*=(const Element & b);
    inline Element & operator*=(const std::uint8_t & b);
public:
    inline std::uint8_t operator*(const Element & b) const;
    inline std::uint8_t operator*(const std::uint8_t & b) const;
public:
    inline Element & operator/=(const Element & b);
    inline Element & operator/=(const std::uint8_t & b);
public:
    inline std::uint8_t operator/(const Element & b) const;
    inline std::uint8_t operator/(const std::uint8_t & b) const;
public:
    inline Element & operator%=(const Element & b);
    inline Element & operator%=(const std::uint8_t & b);
public:
    inline std::uint8_t operator%(const Element & b) const;
    inline std::uint8_t operator%(const std::uint8_t & b) const;
public:
    inline bool operator==(const Element & b) const;
    inline bool operator==(const std::uint8_t & b) const;
public:
    inline bool operator!=(const Element & b) const;
    inline bool operator!=(const std::uint8_t & b) const;
public:
    inline bool operator<(const Element & b) const;
    inline bool operator<(const std::uint8_t & b) const;
public:
    inline bool operator<=(const Element & b) const;
    inline bool operator<=(const std::uint8_t & b) const;
public:
    inline bool operator>(const Element & b) const;
    inline bool operator>(const std::uint8_t & b) const;
public:
    inline bool operator>=(const Element & b) const;
    inline bool operator>=(const std::uint8_t & b) const;
public:
    inline void Swap(Element & b);
};

inline Element::Element() :
    m_offset(0),
    m_index(0),
    m_begin(0),
    m_end(0),
    m_object(std::make_shared<bytes::ptr::Object>(1)),
    m_trait(std::make_shared<bytes::Trait>())
{}

inline Element::Element(const std::size_t & i, const std::size_t & bg,
    const std::size_t & ed, const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        m_offset(0),
        m_index(i),
        m_begin(bg),
        m_end(ed),
        m_object(o),
        m_trait(t)
{
    if (!m_object) m_object = std::make_shared<bytes::ptr::Object>(1);
    if (!m_trait) m_trait = std::make_shared<bytes::Trait>();
}

inline Element::Element(const std::size_t & i, const std::size_t & bg, 
    const std::size_t & ed, const std::uint8_t & off, 
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        m_offset(off),
        m_index(i),
        m_begin(bg),
        m_end(ed),
        m_object(o),
        m_trait(t)
{
    if (!m_object) m_object = std::make_shared<bytes::ptr::Object>(1);
    if (!m_trait) m_trait = std::make_shared<bytes::Trait>();
}

inline Element::~Element()
{
    m_offset = 0;
    m_index = 0;
    m_begin = 0;
    m_end = 0;
    m_object = nullptr;
    m_trait = nullptr;
}

inline Element::Element(const Element & cpy) :
    m_offset(cpy.m_offset),
    m_index(cpy.m_index),
    m_begin(cpy.m_begin),
    m_end(cpy.m_end),
    m_object(cpy.m_object),
    m_trait(cpy.m_trait)
{}

inline Element::Element(Element && mov) :
    m_offset(mov.m_offset),
    m_index(mov.m_index),
    m_begin(mov.m_begin),
    m_end(mov.m_end),
    m_object(mov.m_object),
    m_trait(mov.m_trait)
{
    mov.m_offset = 0;
    mov.m_index = 0;
    mov.m_begin = 0;
    mov.m_end = 0;
    mov.m_object = std::make_shared<bytes::ptr::Object>(1);
    mov.m_trait = std::make_shared<bytes::Trait>();
}

inline Element & Element::operator=(const Element & cpy)
{
    return (*this = static_cast<std::uint8_t>(cpy));
}

inline Element & Element::operator=(Element && mov)
{
    return (*this = static_cast<std::uint8_t>(mov));
}

inline Element & Element::operator=(const std::uint8_t & v)
{
    if (m_offset == 0)
        m_object->At(m_trait->At(m_index, m_begin, m_end)) = 
            m_trait->Set(v);
    else
         m_trait->ValueAt(m_object->At(m_trait->At(m_index, m_begin, m_end)), 
            m_object->At(m_trait->At(m_trait->Next(m_index, 1, m_begin, m_end),
            m_begin, m_end)), m_trait->Set(v), m_offset);
    return *this;
}

inline std::uint8_t Element::GetOffset() const
{
    return m_offset;
}

inline std::size_t Element::GetIndex() const
{
    return m_index;
}

inline std::size_t Element::GetAbsoluteIndex() const
{
    return m_trait->At(m_index, m_begin, m_end);
}

inline std::size_t Element::GetBeginIndex() const
{
    return m_begin;
}

inline std::size_t Element::GetEndIndex() const
{
    return m_end;
}

inline std::shared_ptr<bytes::ptr::Object> Element::GetObject()
{
    return m_object;
}

inline std::shared_ptr<const bytes::ptr::Object> Element::GetObject() const
{
    return std::dynamic_pointer_cast<const bytes::ptr::Object>(
        const_cast<Element &>(*this).m_object);
}

inline std::shared_ptr<bytes::Trait> Element::GetTrait()
{
    return m_trait;
}

inline std::shared_ptr<const bytes::Trait> Element::GetTrait() const
{
    return std::dynamic_pointer_cast<const bytes::Trait>(
        const_cast<Element &>(*this).m_trait);
}

inline bool Element::IsSameObject(const Element & elem) const
{
    return m_object == elem.m_object;
}

inline bool Element::
    IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const
{
    return m_object == b;
}

inline Element::operator std::uint8_t() const
{
    if (m_offset == 0)
        return m_trait->Get(m_object->At(m_trait->At(m_index, m_begin, m_end)));
    return m_trait->ValueAt(m_object->At(m_trait->At(m_index, m_begin, m_end)), 
        m_object->At(m_trait->At(m_trait->Next(m_index, 1, m_begin, m_end), 
        m_begin, m_end)), m_offset, 8);
}

inline std::uint8_t Element::operator~() const
{
    return ~static_cast<std::uint8_t>(*this);
}

inline Element & Element::operator|=(const Element & b)
{
    return (*this |= static_cast<std::uint8_t>(b));
}

inline Element & Element::operator|=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) | b);
}

inline std::uint8_t Element::operator|(const Element & b) const
{
    return (*this | static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator|(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) | b);
}

inline Element & Element::operator&=(const Element & b)
{
    return (*this &= static_cast<std::uint8_t>(b));
}

inline Element & Element::operator&=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) & b);
}

inline std::uint8_t Element::operator&(const Element & b) const
{
    return (*this & static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator&(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) & b);
}

inline Element & Element::operator^=(const Element & b)
{
    return (*this ^= static_cast<std::uint8_t>(b));
}

inline Element & Element::operator^=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) | b);
}

inline std::uint8_t Element::operator^(const Element & b) const
{
    return (*this ^ static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator^(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) ^ b);
}

inline Element & Element::operator>>=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) >> b);
}

inline std::uint8_t Element::operator>>(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) >> b);
}

inline Element & Element::operator<<=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) << b);
}

inline std::uint8_t Element::operator<<(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) << b);
}

inline Element & Element::operator++()
{
    *this = static_cast<std::uint8_t>(*this) + 1;
    return *this;
}

inline std::uint8_t Element::operator++(int)
{
    auto res = static_cast<std::uint8_t>(*this);
    ++(*this);
    return res;
}

inline Element & Element::operator--()
{
    *this = static_cast<std::uint8_t>(*this) - 1;
    return *this;
}

inline std::uint8_t Element::operator--(int)
{
    auto res = static_cast<std::uint8_t>(*this);
    --(*this);
    return res;
}

inline Element & Element::operator+=(const Element & b)
{
    return (*this += static_cast<std::uint8_t>(b));
}

inline Element & Element::operator+=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) + b);
}

inline std::uint8_t Element::operator+(const Element & b) const
{
    return (*this + static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator+(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) + b);
}

inline Element & Element::operator-=(const Element & b)
{
    return (*this -= static_cast<std::uint8_t>(b));
}

inline Element & Element::operator-=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) - b);
}

inline std::uint8_t Element::operator-(const Element & b) const
{
    return (*this - static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator-(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) - b);
}

inline Element & Element::operator*=(const Element & b)
{
    return (*this *= static_cast<std::uint8_t>(b));
}

inline Element & Element::operator*=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) * b);
}

inline std::uint8_t Element::operator*(const Element & b) const
{
    return (*this * static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator*(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) * b);
}

inline Element & Element::operator/=(const Element & b)
{
    return (*this /= static_cast<std::uint8_t>(b));
}

inline Element & Element::operator/=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) / b);
}

inline std::uint8_t Element::operator/(const Element & b) const
{
    return (*this / static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator/(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) / b);
}

inline Element & Element::operator%=(const Element & b)
{
    return (*this %= static_cast<std::uint8_t>(b));
}

inline Element & Element::operator%=(const std::uint8_t & b)
{
    return (*this = static_cast<std::uint8_t>(*this) % b);
}

inline std::uint8_t Element::operator%(const Element & b) const
{
    return (*this % static_cast<std::uint8_t>(b));
}

inline std::uint8_t Element::operator%(const std::uint8_t & b) const
{
    return (static_cast<std::uint8_t>(*this) % b);
}

inline bool Element::operator==(const Element & b) const
{
    return *this == static_cast<std::uint8_t>(b);
}

inline bool Element::operator==(const std::uint8_t & b) const
{
    return static_cast<std::uint8_t>(*this) == b;
}

inline bool Element::operator!=(const Element & b) const
{
    return !(*this == b);
}

inline bool Element::operator!=(const std::uint8_t & b) const
{
    return !(*this == b);
}

inline bool Element::operator<(const Element & b) const
{
    return *this < static_cast<std::uint8_t>(b);
}

inline bool Element::operator<(const std::uint8_t & b) const
{
    return static_cast<std::uint8_t>(*this) < b;
}

inline bool Element::operator<=(const Element & b) const
{
    return *this <= static_cast<std::uint8_t>(b);
}

inline bool Element::operator<=(const std::uint8_t & b) const
{
    return static_cast<std::uint8_t>(*this) <= b;
}

inline bool Element::operator>(const Element & b) const
{
    return *this > static_cast<std::uint8_t>(b);
}

inline bool Element::operator>(const std::uint8_t & b) const
{
    return static_cast<std::uint8_t>(*this) > b;
}

inline bool Element::operator>=(const Element & b) const
{
    return *this >= static_cast<std::uint8_t>(b);
}

inline bool Element::operator>=(const std::uint8_t & b) const
{
    return static_cast<std::uint8_t>(*this) >= b;
}

inline void Element::Swap(Element & b)
{
    auto offset = m_offset;
    auto index = m_index;
    auto begin = m_begin;
    auto end = m_end;
    auto object = m_object;
    auto trait = m_trait;
    m_offset = b.m_offset;
    m_index = b.m_index;
    m_begin = b.m_begin;
    m_end = b.m_end;
    m_object = b.m_object;
    m_trait = b.m_trait;
    b.m_offset = offset;
    b.m_index = index;
    b.m_begin = begin;
    b.m_end = end;
    b.m_object = object;
    b.m_trait = trait;
}

} //!bytes

inline std::uint8_t operator|(const std::uint8_t & a, const bytes::Element & b)
{
    return b | a;
}

inline std::uint8_t operator&(const std::uint8_t & a, const bytes::Element & b)
{
    return b & a;    
}

inline std::uint8_t operator^(const std::uint8_t & a, const bytes::Element & b)
{
    return b ^ a;
}

inline std::uint8_t operator+(const std::uint8_t & a, const bytes::Element & b)
{
    return b + a;
}

inline std::uint8_t operator-(const std::uint8_t & a, const bytes::Element & b)
{
    return a - static_cast<std::uint8_t>(b);
}

inline std::uint8_t operator*(const std::uint8_t & a, const bytes::Element & b)
{
    return b * a;
}

inline std::uint8_t operator/(const std::uint8_t & a, const bytes::Element & b)
{
    return a / static_cast<std::uint8_t>(b);
}

inline std::uint8_t operator%(const std::uint8_t & a, const bytes::Element & b)
{
    return a % static_cast<std::uint8_t>(b);
}

inline bool operator==(const std::uint8_t & a, const bytes::Element & b)
{
    return b == a;
}

inline bool operator!=(const std::uint8_t & a, const bytes::Element & b)
{
    return b != a;
}

inline bool operator<(const std::uint8_t & a, const bytes::Element & b)
{
    return b > a;
}

inline bool operator<=(const std::uint8_t & a, const bytes::Element & b)
{
    return b >= a;
}

inline bool operator>(const std::uint8_t & a, const bytes::Element & b)
{
    return b < a;
}

inline bool operator>=(const std::uint8_t & a, const bytes::Element & b)
{
    return b <= a;
}

#endif //!BYTES_ELEMENT_H_
