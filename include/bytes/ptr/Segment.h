#ifndef BYTES_PTR_SEGMENT_H_
#define BYTES_PTR_SEGMENT_H_

#include <cstdint>
#include <utility>
#include <memory>

#include "Object.h"
#include "../Endian.h"
#include "../Trait.h"
#include "../Element.h"
#include "../ReverseElement.h"

namespace bytes
{
namespace ptr
{

class Segment
{
private:
    static inline std::shared_ptr<bytes::Trait> Trait();
    static inline std::shared_ptr<bytes::Trait> 
        Trait(const std::shared_ptr<bytes::Trait> & t);
private:
    std::uint8_t m_offset;
    std::size_t m_begin;
    std::size_t m_end;
    std::shared_ptr<bytes::ptr::Object> m_object;
    std::shared_ptr<bytes::Trait> m_trait;
public:
    inline Segment();
    inline Segment(const std::size_t & bg, const std::size_t & ed,
        const std::shared_ptr<bytes::ptr::Object> & o);
    inline Segment(const std::size_t & bg, const std::size_t & ed,
        const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
    inline Segment(const std::size_t & bg, const std::size_t & ed,
        const std::uint8_t & off, 
        const std::shared_ptr<bytes::ptr::Object> & o);
    inline Segment(const std::size_t & bg, const std::size_t & ed,
        const std::uint8_t & off, 
        const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline ~Segment();
public:
    inline Segment(const Segment & cpy);
    inline Segment(Segment && mov);
public:
    inline Segment & operator=(const Segment & cpy);
    inline Segment & operator=(Segment && mov);
public:
    inline const bytes::Trait & GetTrait() const; 
public:
    inline bool IsSameObject(const Segment & seg) const;
    inline bool 
        IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const;
public:
    inline std::uint8_t Offset() const;
protected:
    inline void Offset(const std::uint8_t & off);
public:
    inline std::size_t Begin() const;
protected:
    inline void Begin(const std::size_t & bg);
public:
    inline std::size_t End() const;
protected:
    inline void End(const std::size_t & ed);
public:
    inline std::size_t Size() const;
protected:
    inline std::size_t Reallocate(const std::size_t & s);
public:
    inline bytes::Element At(const std::size_t & i);
    inline bytes::Element At(const std::size_t & i, const std::uint8_t & sz);
    inline const bytes::Element At(const std::size_t & i) const;
    inline const bytes::Element At(const std::size_t & i, 
        const std::uint8_t & sz) const;
public:
    inline bytes::ReverseElement ReverseAt(const std::size_t & i);
    inline bytes::ReverseElement ReverseAt(const std::size_t & i, 
        const std::uint8_t & sz);
    inline const bytes::ReverseElement ReverseAt(const std::size_t & i) const;
    inline const bytes::ReverseElement ReverseAt(const std::size_t & i,
        const std::uint8_t & sz) const;
public:
    inline std::size_t Next(const std::size_t & i, 
        const std::size_t & st = 1) const;
public:
    inline std::size_t Previous(const std::size_t & i,
        const std::size_t & st = 1) const;
public:
    inline bool IsEnd(const std::size_t & i) const;
public:
    inline bool IsReverseEnd(const std::size_t & i) const;
public:
    inline std::uint8_t * Get();
    inline const std::uint8_t * Get() const;
public:
    inline operator bool() const;
public:
    inline bytes::Element operator[](const std::size_t & i);
    inline const bytes::Element operator[](const std::size_t & i) const;
public:
    inline bool operator==(const Segment & b) const;
public:
    inline bool operator!=(const Segment & b) const;
};

inline std::shared_ptr<bytes::Trait> Segment::Trait()
{
    return std::make_shared<bytes::Trait>();
}

inline std::shared_ptr<bytes::Trait> 
    Segment::Trait(const std::shared_ptr<bytes::Trait> & t)
{
    if (t) return t;
    return Trait();
}
    
inline Segment::Segment() :
    m_offset(0),
    m_begin(0),
    m_end(0),
    m_object(nullptr),
    m_trait(nullptr)
{}

inline Segment::Segment(const std::size_t & bg, const std::size_t & ed,
    const std::shared_ptr<bytes::ptr::Object> & o) :
        m_offset(0),
        m_begin(bg),
        m_end(ed),
        m_object(o),
        m_trait(Trait())
{}

inline Segment::Segment(const std::size_t & bg, const std::size_t & ed,
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        m_offset(0),
        m_begin(bg),
        m_end(ed),
        m_object(o),
        m_trait(Trait(t))
{}

inline Segment::Segment(const std::size_t & bg, const std::size_t & ed,
    const std::uint8_t & off, 
    const std::shared_ptr<bytes::ptr::Object> & o) :
        m_offset(off % 8),
        m_begin(bg + (off / 8)),
        m_end(ed + (off / 8)),
        m_object(o),
        m_trait(Trait())
{}

inline Segment::Segment(const std::size_t & bg, const std::size_t & ed,
    const std::uint8_t & off, 
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        m_offset(off % 8),
        m_begin(bg + (off / 8)),
        m_end(ed + (off / 8)),
        m_object(o),
        m_trait(Trait(t))
{}

inline Segment::~Segment()
{
    m_offset = 0;
    m_begin = 0;
    m_end = 0;
    m_object = nullptr;
    m_trait = nullptr;
}

inline Segment::Segment(const Segment & cpy) :
    m_offset(0),
    m_begin(0),
    m_end(cpy.Size()),
    m_object(nullptr),
    m_trait(nullptr)
{
    if (cpy.m_object)
        m_object = std::make_shared<bytes::ptr::Object>(*(cpy.m_object), 
            m_begin, m_end);
    if (cpy.m_trait) m_trait = std::make_shared<bytes::Trait>(*(cpy.m_trait));
    else m_trait = Trait();
}

inline Segment::Segment(Segment && mov) :
    m_offset(mov.m_offset),
    m_begin(mov.m_begin),
    m_end(mov.m_end),
    m_object(mov.m_object),
    m_trait(mov.m_trait)
{
    mov.m_offset = 0;
    mov.m_begin = 0;
    mov.m_end = 0;
    mov.m_object = nullptr;
    mov.m_trait = nullptr;
}

inline Segment & Segment::operator=(const Segment & cpy)
{
    m_offset = 0;
    m_begin = 0;
    m_end = cpy.Size();
    m_object = nullptr;
    m_trait = nullptr;
    if (cpy.m_object) 
        m_object = std::make_shared<bytes::ptr::Object>(*(cpy.m_object),
            m_begin, m_end);
    if (cpy.m_trait) m_trait = std::make_shared<bytes::Trait>(*(cpy.m_trait));
    else m_trait = Trait();
    return *this;
}

inline Segment & Segment::operator=(Segment && mov)
{
    m_offset = mov.m_offset;
    m_begin = mov.m_begin;
    m_end = mov.m_end;
    m_object = mov.m_object;
    m_trait = mov.m_trait;
    mov.m_offset = 0;
    mov.m_begin = 0;
    mov.m_end = 0;
    mov.m_object = nullptr;
    mov.m_trait = nullptr;
    return *this;
}

inline const bytes::Trait & Segment::GetTrait() const
{
    static bytes::Trait t;
    if (m_trait) return *m_trait;
    return t;
}

inline bool Segment::IsSameObject(const Segment & seg) const
{
    return seg.m_object == m_object;
}

inline bool Segment::
    IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const
{
    return b == m_object;
}

inline std::uint8_t Segment::Offset() const
{
    return m_offset;
}

inline void Segment::Offset(const std::uint8_t & off)
{
    m_offset = off % 8;
    m_begin += off / 8;
}

inline std::size_t Segment::Begin() const
{
    return m_begin;
}

inline void Segment::Begin(const std::size_t & bg)
{
    m_begin = bg;
}

inline std::size_t Segment::End() const
{
    return m_end - (m_offset == 0 ? 0 : 1);
}

inline void Segment::End(const std::size_t & ed)
{
    m_end = ed;
}

inline std::size_t Segment::Size() const
{
    if (m_end > m_begin)
    {
        const std::size_t size = m_end - m_begin;
        if (m_offset == 0) return size;
        return size - 1;
    }
    return 0;
}

inline std::size_t Segment::Reallocate(const std::size_t & s)
{
    const std::size_t cs = Size();
    if (cs == s) return cs;
    const std::size_t ns = m_trait->Resize(cs, s);
    if (cs == ns) return cs;
    if (m_offset == 0)
    {
        m_end = m_begin + ns;
        return ns;
    }
    const std::size_t next_ns = ns + 1;
    m_end = m_begin + next_ns;
    return next_ns;
}

inline bytes::Element Segment::At(const std::size_t & i)
{
    if (!m_object || !m_trait) return bytes::Element();
    return bytes::Element(i, m_begin, m_end, m_offset, m_object, m_trait);
}

inline bytes::Element Segment::At(const std::size_t & i, 
    const std::uint8_t & sz)
{
    if (!m_object || !m_trait) return bytes::Element();
    return bytes::Element(i, m_begin, m_end, m_offset, sz, m_object, m_trait);
}

inline const bytes::Element Segment::At(const std::size_t & i) const
{
    if (!m_object || !m_trait) return bytes::Element();
    return bytes::Element(i, m_begin, m_end, m_offset, m_object, m_trait);
}

inline const bytes::Element Segment::At(const std::size_t & i, 
    const std::uint8_t & sz) const
{
    if (!m_object || !m_trait) return bytes::Element();
    return bytes::Element(i, m_begin, m_end, m_offset, sz, m_object, m_trait);
}

inline bytes::ReverseElement Segment::ReverseAt(const std::size_t & i)
{
    if (!m_object || !m_trait) return bytes::ReverseElement();
    return bytes::ReverseElement(i, m_begin, m_end, m_offset, m_object, 
        m_trait);
}

inline bytes::ReverseElement Segment::ReverseAt(const std::size_t & i,
    const std::uint8_t & sz)
{
    if (!m_object || !m_trait) return bytes::ReverseElement();
    return bytes::ReverseElement(i, m_begin, m_end, m_offset, sz, m_object, 
        m_trait);
}

inline const bytes::ReverseElement 
    Segment::ReverseAt(const std::size_t & i) const
{
    if (!m_object || !m_trait) return bytes::ReverseElement();
    return bytes::ReverseElement(i, m_begin, m_end, m_object, m_trait);
}

inline const bytes::ReverseElement Segment::ReverseAt(const std::size_t & i,
    const std::uint8_t & sz) const
{
    if (!m_object || !m_trait) return bytes::ReverseElement();
    return bytes::ReverseElement(i, m_begin, m_end, m_offset, sz, m_object, 
        m_trait);
}

inline std::size_t Segment::Next(const std::size_t & i, 
    const std::size_t & st) const
{
    if (!m_object || !m_trait) return End();
    return m_trait->Next(i, st, Begin(), End());
}

inline std::size_t Segment::Previous(const std::size_t & i,
    const std::size_t & st) const
{
    if (!m_object || !m_trait) return -1;
    return m_trait->Previous(i, st, Begin(), End());
}

inline bool Segment::IsEnd(const std::size_t & i) const
{
    if (!m_object || !m_trait) return true;
    return m_trait->IsEnd(i, Begin(), End());
}

inline bool Segment::IsReverseEnd(const std::size_t & i) const
{
    if (!m_object || !m_trait) return true;
    return m_trait->IsReverseEnd(i, Begin(), End());
}

inline std::uint8_t * Segment::Get()
{
    if (!m_object) return bytes::ptr::Object::Null();
    return m_object->Get() + m_begin;
}

inline const std::uint8_t * Segment::Get() const
{
    if (!m_object) return bytes::ptr::Object::Null();
    return m_object->Get() + m_begin;
}

inline Segment::operator bool() const
{
    return Begin() < End() && !m_object && !*m_object;
}

inline bytes::Element Segment::operator[](const std::size_t & i)
{
    return At(i);
}

inline const bytes::Element Segment::operator[](const std::size_t & i) const
{
    return At(i);
}

inline bool Segment::operator==(const Segment & b) const
{
    const bool ca = static_cast<bool>(*this),
        cb = static_cast<bool>(b);
    return (!ca && !cb) || (ca && cb && 
        IsSameObject(b.m_object) &&
        m_offset == b.m_offset &&
        m_begin == b.m_begin &&
        m_end == b.m_end && 
        m_trait == b.m_trait);
}

inline bool Segment::operator!=(const Segment & b) const
{
    return !(*this == b);
}

} //!ptr

} //!bytes

#endif //!BYTES_PTR_SEGMENT_H_
