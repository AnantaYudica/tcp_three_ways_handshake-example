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
    std::shared_ptr<bytes::ptr::Object> m_object;
    std::shared_ptr<bytes::Trait> m_trait;
    std::size_t m_index;
public:
    inline Element();
    inline Element(const std::size_t & i, 
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
    inline Element & operator=(const std::uint8_t & v);
public:
    inline std::size_t Index() const;
public:
    inline operator std::uint8_t() const;
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
};

inline Element::Element() :
    m_object(std::make_shared<bytes::ptr::Object>(1)),
    m_trait(std::make_shared<bytes::Trait>()),
    m_index(0)
{}

inline Element::Element(const std::size_t & i, 
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        m_object(o),
        m_trait(t),
        m_index(i)
{
    if (!m_object) m_object = std::make_shared<bytes::ptr::Object>(1);
    if (!m_trait) m_trait = std::make_shared<bytes::Trait>();
}

inline Element::~Element()
{
    m_object = nullptr;
    m_trait = nullptr;
    m_index = -1;
}

inline Element::Element(const Element & cpy) :
    m_object(cpy.m_object),
    m_trait(cpy.m_trait),
    m_index(cpy.m_index)
{}

inline Element::Element(Element && mov) :
    m_object(mov.m_object),
    m_trait(mov.m_trait),
    m_index(mov.m_index)
{
    mov.m_object = std::make_shared<bytes::ptr::Object>(1);
    mov.m_trait = std::make_shared<bytes::Trait>();
    mov.m_index = 0;
}

inline Element & Element::operator=(const Element & cpy)
{
    return (*this = static_cast<std::uint8_t>(cpy));
}

inline Element & Element::operator=(Element && mov)
{
    m_object = mov.m_object;
    m_trait = mov.m_trait;
    m_index = mov.m_index;
    if (!m_object)
    {
        m_object = std::make_shared<bytes::ptr::Object>(1);
        m_index = 0;
    }
    if (!m_trait) m_trait = std::make_shared<bytes::Trait>();
    mov.m_object = std::make_shared<bytes::ptr::Object>(1);
    mov.m_trait = std::make_shared<bytes::Trait>();
    mov.m_index = 0;
    return *this;
}

inline Element & Element::operator=(const std::uint8_t & v)
{
    m_object->At(m_index) = m_trait->Set(v);
    return *this;
}

inline std::size_t Element::Index() const
{
    return m_index;
}

inline Element::operator std::uint8_t() const
{
    return m_trait->Get(m_object->At(m_index));
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
