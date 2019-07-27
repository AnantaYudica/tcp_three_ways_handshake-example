#ifndef BYTES_TRAIT_H_
#define BYTES_TRAIT_H_

#include <cstdint>
#include <memory>
#include <utility>

#include "Endian.h"
#include "sys/Endian.h"
#include "trait/Capacity.h"
#include "trait/Element.h"
#include "trait/Modifier.h"
#include "trait/capacity/Fixed.h"
#include "trait/element/Direct.h"
#include "trait/modifier/Direct.h"

namespace bytes
{

class Trait
{
private:
    static inline const bytes::Endian * GetEndian();
    static inline const bytes::Endian * 
        GetEndian(const bytes::Endian::CategoryEnum & e);
private:
    static inline std::shared_ptr<bytes::trait::Capacity>
        GetCapacity();
    static inline std::shared_ptr<bytes::trait::Capacity>
        GetCapacity(const std::shared_ptr<bytes::trait::Capacity> & c);
private:
    static inline std::shared_ptr<bytes::trait::Element>
        GetElement();
    static inline std::shared_ptr<bytes::trait::Element>
        GetElement(const std::shared_ptr<bytes::trait::Element> & e);
private:
    static inline std::shared_ptr<bytes::trait::Modifier>
        GetModifier();
    static inline std::shared_ptr<bytes::trait::Modifier>
        GetModifier(const std::shared_ptr<bytes::trait::Modifier> & m);
private:
    const bytes::Endian * m_endian;
    std::shared_ptr<bytes::trait::Capacity> m_capacity;
    std::shared_ptr<bytes::trait::Element> m_element;
    std::shared_ptr<bytes::trait::Modifier> m_modifier;
protected:
    inline Trait();
    inline Trait(const bytes::Endian::CategoryEnum & e);
    inline Trait(const std::shared_ptr<bytes::trait::Capacity> & c,
        const std::shared_ptr<bytes::trait::Element> & e,
        const std::shared_ptr<bytes::trait::Modifier> & m);
    inline Trait(const bytes::Endian::CategoryEnum & e,
        const std::shared_ptr<bytes::trait::Capacity> & c,
        const std::shared_ptr<bytes::trait::Element> & e,
        const std::shared_ptr<bytes::trait::Modifier> & m);
public:
    inline ~Trait();
protected:
    inline Trait(const Trait & cpy);
    inline Trait(Trait && mov);
public:
    inline Trait & operator=(const Trait & cpy);
    inline Trait & operator=(Trait && mov);
public:
    inline const bytes::Endian & Endian() const;
public:
    inline std::size_t Size() const;
    inline std::size_t Size(const std::size_t & s) const;
public:
    inline std::size_t Resize(const std::size_t & cs,
        const std::size_t & ns) const;
public:
    inline std::size_t At(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline bool IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline bool IsReverseEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline std::uint8_t OnSet(const std::uint8_t & v, 
        const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed) const;
public:
    inline std::uint8_t OnGet(const std::uint8_t & v, 
        const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed) const;
public:
    inline bool operator==(const Trait & b) const;
public:
    inline bool operator!=(const Trait & b) const;
};

inline const bytes::Endian * Trait::GetEndian()
{
    return &bytes::sys::Endian();
}

inline const bytes::Endian * 
    Trait::GetEndian(const bytes::Endian::CategoryEnum & e)
{
    switch (e)
    {
    case bytes::Endian::big:
        return &bytes::endian::Big::Instance();
    case bytes::Endian::little:
        return &bytes::endian::Little::Instance();
    default:
        break;
    }
    return GetEndian();
}

inline std::shared_ptr<bytes::trait::Capacity> Trait::GetCapacity()
{
    return std::make_shared<bytes::trait::capacity::Fixed>();
}

inline std::shared_ptr<bytes::trait::Capacity>
    Trait::GetCapacity(const std::shared_ptr<bytes::trait::Capacity> & c)
{
    if (c) return c;
    return GetCapacity();
}

inline std::shared_ptr<bytes::trait::Element> Trait::GetElement()
{
    return std::make_shared<bytes::trait::element::Direct>();
}

inline std::shared_ptr<bytes::trait::Element>
    Trait::GetElement(const std::shared_ptr<bytes::trait::Element> & e)
{
    if (e) return e;
    return GetElement();
}

inline std::shared_ptr<bytes::trait::Modifier> GetModifier()
{
    return std::make_shared<bytes::trait::modifier::Direct>();
}

inline std::shared_ptr<bytes::trait::Modifier>
    Trait::GetModifier(const std::shared_ptr<bytes::trait::Modifier> & m)
{
    if (m) return m;
    return GetModifier();
}

inline Trait::Trait() :
    m_endian(GetEndian()),
    m_capacity(GetCapacity()),
    m_element(GetElement()),
    m_modifier(GetModifier())
{}

inline Trait::Trait(const bytes::Endian::CategoryEnum & e) :
    m_endian(GetEndian(e)),
    m_capacity(GetCapacity()),
    m_element(GetElement()),
    m_modifier(GetModifier())
{}

inline Trait::Trait(const std::shared_ptr<bytes::trait::Capacity> & c,
    const std::shared_ptr<bytes::trait::Element> & e,
    const std::shared_ptr<bytes::trait::Modifier> & m) :
        m_endian(GetEndian()),
        m_capacity(GetCapacity(c)),
        m_element(GetElement(e)),
        m_modifier(GetModifier(m))
{}

inline Trait::Trait(const bytes::Endian::CategoryEnum & e,
    const std::shared_ptr<bytes::trait::Capacity> & c,
    const std::shared_ptr<bytes::trait::Element> & e,
    const std::shared_ptr<bytes::trait::Modifier> & m) :
        m_endian(GetEndian(e)),
        m_capacity(GetCapacity(c)),
        m_element(GetElement(e)),
        m_modifier(GetModifier(m))
{}

inline Trait::~Trait()
{
    m_capacity = nullptr;
    m_element = nullptr;
    m_modifier = nullptr;
}

inline Trait::Trait(const Trait & cpy) :
    m_endian(cpy.m_endian),
    m_capacity(cpy.m_capacity.Copy()),
    m_element(cpy.m_element.Copy()),
    m_modifier(cpy.m_modifier.Copy())
{}

inline Trait::Trait(Trait && mov) :
    m_endian(mov.m_endian),
    m_capacity(mov.m_capacity),
    m_element(mov.m_element),
    m_modifier(mov.m_modifier)
{
    mov.m_endian = GetEndian();
    mov.m_capacity = GetCapacity();
    mov.m_element = GetElement();
    mov.m_modifier = GetModifier();
}

inline Trait & Trait::operator=(const Trait & cpy)
{
    m_endian = cpy.m_endian;
    m_capacity = cpy.m_capacity.Copy();
    m_element = cpy.m_element.Copy();
    m_modifier = cpy.m_modifier.Copy();
    return *this;
}

inline Trait & Trait::operator=(Trait && mov)
{
    m_endian = mov.m_endian;
    m_capacity = cpy.m_capacity;
    m_element = cpy.m_element;
    m_modifier = cpy.m_modifier;
    mov.m_endian = GetEndian();
    mov.m_capacity = GetCapacity();
    mov.m_element = GetElement();
    mov.m_modifier = GetModifier();
    return *this;
}

inline const bytes::Endian & Trait::Endian() const
{
    return *m_endian;
}

inline std::size_t Trait::Size() const
{
    return m_capacity->OnSize(0);
}

inline std::size_t Trait::Size(const std::size_t & s) const
{
    return m_capacity->OnSize(s);
}

inline std::size_t Trait::Resize(const std::size_t & cs,
    const std::size_t & ns) const
{
    return m_capacity->OnResize(cs, ns);
}

inline std::size_t Trait::At(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return m_endian->At(m_element->OnAt(i, bg, ed), bg, ed);
}

inline bool Trait::IsEnd(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return m_element->OnIsEnd(i, bg, ed);
}

inline bool Trait::IsReverseEnd(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return m_element->OnIsReverseEnd(i, bg, ed);
}

inline std::uint8_t Trait::Set(const std::uint8_t & v, 
    const std::size_t & i, const std::size_t & bg,
    const std::size_t & ed) const
{
    return m_modifier->OnSet(v, i, bg, ed);
}

inline std::uint8_t Trait::Get(const std::uint8_t & v, 
    const std::size_t & i, const std::size_t & bg,
    const std::size_t & ed) const
{
    return m_modifier->OnGet(v, i, bg, ed);
}

inline bool Trait::operator==(const Trait & b) const
{
    return m_endian == b.m_endian &&
        m_capacity == b.m_capacity &&
        m_element == b.m_element &&
        m_modifier == b.m_modifier;
}

inline bool Trait::operator!=(const Trait & b) const
{
    return !(*this == b);
}

} //!bytes

#endif //!BYTES_TRAIT_H_
