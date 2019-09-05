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
    static inline const bytes::Endian * Endian();
    static inline const bytes::Endian * 
        Endian(const bytes::Endian::CategoryEnum & e);
private:
    static inline std::shared_ptr<bytes::trait::Capacity> Capacity();
    static inline std::shared_ptr<bytes::trait::Capacity>
        Capacity(const std::shared_ptr<bytes::trait::Capacity> & c);
private:
    static inline std::shared_ptr<bytes::trait::Element> Element();
    static inline std::shared_ptr<bytes::trait::Element>
        Element(const std::shared_ptr<bytes::trait::Element> & e);
private:
    static inline std::shared_ptr<bytes::trait::Modifier> Modifier();
    static inline std::shared_ptr<bytes::trait::Modifier>
        Modifier(const std::shared_ptr<bytes::trait::Modifier> & m);
private:
    const bytes::Endian * m_endian;
    std::shared_ptr<bytes::trait::Capacity> m_capacity;
    std::shared_ptr<bytes::trait::Element> m_element;
    std::shared_ptr<bytes::trait::Modifier> m_modifier;
public:
    inline Trait();
    inline Trait(const bytes::Endian::CategoryEnum & e);
    inline Trait(const std::shared_ptr<bytes::trait::Capacity> & c,
        const std::shared_ptr<bytes::trait::Element> & e,
        const std::shared_ptr<bytes::trait::Modifier> & m);
    inline Trait(const bytes::Endian::CategoryEnum & e,
        const std::shared_ptr<bytes::trait::Capacity> & c,
        const std::shared_ptr<bytes::trait::Element> & el,
        const std::shared_ptr<bytes::trait::Modifier> & m);
public:
    inline ~Trait();
public:
    inline Trait(const Trait & cpy);
    inline Trait(Trait && mov);
public:
    inline Trait & operator=(const Trait & cpy);
    inline Trait & operator=(Trait && mov);
public:
    inline const bytes::Endian & GetEndian() const;
public:
    inline std::shared_ptr<const bytes::trait::Capacity> GetCapacity() const;
public:
    inline std::shared_ptr<const bytes::trait::Element> GetElement() const;
public:
    inline std::shared_ptr<const bytes::trait::Modifier> GetModifier() const;
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
    inline std::size_t ReverseAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline std::size_t Next(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline std::size_t Previous(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline bool IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline bool IsReverseEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline std::uint8_t Set(const std::uint8_t & v) const;
public:
    inline std::uint8_t Get(const std::uint8_t & v) const;
public:
    inline std::uint8_t ValueAt(const std::uint8_t & v_at_0,
        const std::uint8_t & v_at_1, const std::uint8_t & off,
        const std::uint8_t & sz) const;
    inline void ValueAt(std::uint8_t & v_at_0, 
        std::uint8_t & v_at_1, const std::uint8_t & v_in, 
        const std::uint8_t & off, const std::uint8_t & sz) const;
public:
    inline std::uint8_t ValueReverseAt(const std::uint8_t & v_r_at_0, 
        const std::uint8_t & v_r_at_1, const std::uint8_t & off, 
        const std::uint8_t & sz) const;
    inline void ValueReverseAt(std::uint8_t & v_r_at_0, 
        std::uint8_t & v_r_at_1, const std::uint8_t & v_in, 
        const std::uint8_t & off, const std::uint8_t & sz) const;
public:
    inline bool operator==(const Trait & b) const;
public:
    inline bool operator!=(const Trait & b) const;
};

inline const bytes::Endian * Trait::Endian()
{
    return &bytes::sys::Endian();
}

inline const bytes::Endian * 
    Trait::Endian(const bytes::Endian::CategoryEnum & e)
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
    return Endian();
}

inline std::shared_ptr<bytes::trait::Capacity> Trait::Capacity()
{
    return std::make_shared<bytes::trait::capacity::Fixed>();
}

inline std::shared_ptr<bytes::trait::Capacity>
    Trait::Capacity(const std::shared_ptr<bytes::trait::Capacity> & c)
{
    if (c) return c;
    return Capacity();
}

inline std::shared_ptr<bytes::trait::Element> Trait::Element()
{
    return std::make_shared<bytes::trait::element::Direct>();
}

inline std::shared_ptr<bytes::trait::Element>
    Trait::Element(const std::shared_ptr<bytes::trait::Element> & e)
{
    if (e) return e;
    return Element();
}

inline std::shared_ptr<bytes::trait::Modifier> Trait::Modifier()
{
    return std::make_shared<bytes::trait::modifier::Direct>();
}

inline std::shared_ptr<bytes::trait::Modifier>
    Trait::Modifier(const std::shared_ptr<bytes::trait::Modifier> & m)
{
    if (m) return m;
    return Modifier();
}

inline Trait::Trait() :
    m_endian(Endian()),
    m_capacity(Capacity()),
    m_element(Element()),
    m_modifier(Modifier())
{}

inline Trait::Trait(const bytes::Endian::CategoryEnum & e) :
    m_endian(Endian(e)),
    m_capacity(Capacity()),
    m_element(Element()),
    m_modifier(Modifier())
{}

inline Trait::Trait(const std::shared_ptr<bytes::trait::Capacity> & c,
    const std::shared_ptr<bytes::trait::Element> & e,
    const std::shared_ptr<bytes::trait::Modifier> & m) :
        m_endian(Endian()),
        m_capacity(Capacity(c)),
        m_element(Element(e)),
        m_modifier(Modifier(m))
{}

inline Trait::Trait(const bytes::Endian::CategoryEnum & e,
    const std::shared_ptr<bytes::trait::Capacity> & c,
    const std::shared_ptr<bytes::trait::Element> & el,
    const std::shared_ptr<bytes::trait::Modifier> & m) :
        m_endian(Endian(e)),
        m_capacity(Capacity(c)),
        m_element(Element(el)),
        m_modifier(Modifier(m))
{}

inline Trait::~Trait()
{
    m_capacity = nullptr;
    m_element = nullptr;
    m_modifier = nullptr;
}

inline Trait::Trait(const Trait & cpy) :
    m_endian(cpy.m_endian),
    m_capacity(cpy.m_capacity->Copy()),
    m_element(cpy.m_element->Copy()),
    m_modifier(cpy.m_modifier->Copy())
{}

inline Trait::Trait(Trait && mov) :
    m_endian(mov.m_endian),
    m_capacity(mov.m_capacity),
    m_element(mov.m_element),
    m_modifier(mov.m_modifier)
{
    mov.m_endian = Endian();
    mov.m_capacity = Capacity();
    mov.m_element = Element();
    mov.m_modifier = Modifier();
}

inline Trait & Trait::operator=(const Trait & cpy)
{
    m_endian = cpy.m_endian;
    m_capacity = cpy.m_capacity->Copy();
    m_element = cpy.m_element->Copy();
    m_modifier = cpy.m_modifier->Copy();
    return *this;
}

inline Trait & Trait::operator=(Trait && mov)
{
    m_endian = mov.m_endian;
    m_capacity = mov.m_capacity;
    m_element = mov.m_element;
    m_modifier = mov.m_modifier;
    mov.m_endian = Endian();
    mov.m_capacity = Capacity();
    mov.m_element = Element();
    mov.m_modifier = Modifier();
    return *this;
}

inline const bytes::Endian & Trait::GetEndian() const
{
    return *m_endian;
}

inline std::shared_ptr<const bytes::trait::Capacity> 
    Trait::GetCapacity() const
{
    return std::const_pointer_cast<const bytes::trait::Capacity>(m_capacity);
}

inline std::shared_ptr<const bytes::trait::Element> 
    Trait::GetElement() const
{
    return std::const_pointer_cast<const bytes::trait::Element>(m_element);
}

inline std::shared_ptr<const bytes::trait::Modifier> 
    Trait::GetModifier() const
{
    return std::const_pointer_cast<const bytes::trait::Modifier>(m_modifier);
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

inline std::size_t Trait::ReverseAt(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return m_endian->ReverseAt(m_element->OnReverseAt(i, bg, ed),
        bg, ed);
}

inline std::size_t Trait::Next(const std::size_t & i, 
    const std::size_t & st, const std::size_t & bg, 
    const std::size_t & ed) const
{
    return m_element->OnNext(i, st, bg, ed);
}

inline std::size_t Trait::Previous(const std::size_t & i, 
    const std::size_t & st, const std::size_t & bg, 
    const std::size_t & ed) const
{
    return m_element->OnPrevious(i, st, bg, ed);
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

inline std::uint8_t Trait::Set(const std::uint8_t & v) const
{
    return m_modifier->OnSet(v);
}

inline std::uint8_t Trait::Get(const std::uint8_t & v) const
{
    return m_modifier->OnGet(v);
}

inline std::uint8_t Trait::ValueAt(const std::uint8_t & v_at_0,
    const std::uint8_t & v_at_1, const std::uint8_t & off,
    const std::uint8_t & sz) const
{
    return m_endian->ValueAt(v_at_0, v_at_1, off, sz);
}

inline void Trait::ValueAt(std::uint8_t & v_at_0, 
    std::uint8_t & v_at_1, const std::uint8_t & v_in, 
    const std::uint8_t & off, const std::uint8_t & sz) const
{
    m_endian->ValueAt(v_at_0, v_at_1, v_in, off, sz);
}

inline std::uint8_t Trait::ValueReverseAt(const std::uint8_t & v_r_at_0, 
    const std::uint8_t & v_r_at_1, const std::uint8_t & off, 
    const std::uint8_t & sz) const
{
    return m_endian->ValueReverseAt(v_r_at_0, v_r_at_1, off, sz);
}

inline void Trait::ValueReverseAt(std::uint8_t & v_r_at_0, 
    std::uint8_t & v_r_at_1, const std::uint8_t & v_in, 
    const std::uint8_t & off, const std::uint8_t & sz) const
{
    m_endian->ValueReverseAt(v_r_at_0, v_r_at_1, v_in, off, sz);
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
