#ifndef BYTES_BASE_H_
#define BYTES_BASE_H_

#include <memory>

#include "Trait.h"
#include "trait/Capacity.h"
#include "trait/capacity/Extended.h"
#include "trait/capacity/Fixed.h"
#include "trait/Element.h"
#include "trait/element/Direct.h"
#include "trait/Modifier.h"
#include "trait/modifier/Direct.h"
#include "Endian.h"
#include "Pointer.h"
#include "ptr/Segment.h"
#include "Assign.h"

namespace bytes
{

class Base
{
private:
    static inline void Default(Base & b);
private:
    static inline bool Validation(Base & b);
protected:
    static inline std::shared_ptr<bytes::Trait> GetTrait();
    static inline std::shared_ptr<bytes::Trait> 
        GetTrait(const bytes::Endian::CategoryEnum & e);
    static inline std::shared_ptr<bytes::Trait> 
        GetTrait(const bytes::Trait & t);
protected:
    template<typename TCapacity>
    static inline std::shared_ptr<bytes::Trait> 
        SetCapacityTrait(const bytes::Trait & t);
private:
    std::shared_ptr<bytes::Pointer> m_ptr;
    std::shared_ptr<bytes::ptr::Segment> m_segment;
public:
    inline Base();
    inline Base(const bytes::Endian::CategoryEnum & e);
    inline Base(const bytes::Trait & t);
    inline Base(const std::shared_ptr<bytes::Trait> & t);
public:
    inline Base(const std::size_t & s);
    inline Base(const std::size_t & s, const bytes::Endian::CategoryEnum & e);
    inline Base(const std::size_t & s, const bytes::Trait & t);
    inline Base(const std::size_t & s, const std::shared_ptr<bytes::Trait> & t);
public:
    template<std::size_t N>
    inline Base(const std::uint8_t (&b)[N]);
    template<std::size_t N>
    inline Base(const std::uint8_t (&b)[N], 
        const bytes::Endian::CategoryEnum & e);
    template<std::size_t N>
    inline Base(const std::uint8_t (&b)[N], const bytes::Trait & t);
    template<std::size_t N>
    inline Base(const std::uint8_t (&b)[N], 
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline Base(const std::uint8_t * ptr, const std::size_t & s);
    inline Base(const std::uint8_t * ptr, const std::size_t & s,
        const bytes::Endian::CategoryEnum & e);
    inline Base(const std::uint8_t * ptr, const std::size_t & s, 
        const bytes::Trait & t);
    inline Base(const std::uint8_t * ptr, const std::size_t & s, 
        const std::shared_ptr<bytes::Trait> & t);
protected: 
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s);
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const bytes::Endian::CategoryEnum & e);
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const bytes::Trait & t);
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const std::shared_ptr<bytes::Trait> & t);
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const bytes::Endian::CategoryEnum & e,
        const std::shared_ptr<bytes::Trait> & t);
protected:
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed);
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed, 
        const bytes::Endian::CategoryEnum & e);
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed, 
        const bytes::Trait & t);
    inline Base(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed, 
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline ~Base();
public:
    inline Base(const Base & cpy);
    inline Base(Base && mov);
public:
    inline Base & operator=(const Base & b) = delete;
    inline Base & operator=(Base && b);
protected:
    std::shared_ptr<bytes::Pointer> GetPointer();
    std::shared_ptr<const bytes::Pointer> GetPointer() const;
protected:
    std::shared_ptr<bytes::ptr::Segment> GetSegment();
    std::shared_ptr<const bytes::ptr::Segment> GetSegment() const;
};

inline void Base::Default(Base & b)
{
    b.m_ptr = std::make_shared<bytes::Pointer>(GetTrait()->Size());
    b.m_segment = b.m_ptr->Share(0, b.m_ptr->Size(), GetTrait());
}

inline bool Base::Validation(Base & b)
{
    if (!b.m_ptr) 
    {
        Default(b);
        return false;
    }
    return true;
}

inline std::shared_ptr<bytes::Trait> Base::GetTrait()
{
    static std::shared_ptr<bytes::Trait> instance(new bytes::Trait(
        std::make_shared<bytes::trait::capacity::Extended>(),
        std::make_shared<bytes::trait::element::Direct>(),
        std::make_shared<bytes::trait::modifier::Direct>()));
    return instance;
}

inline std::shared_ptr<bytes::Trait> 
    Base::GetTrait(const bytes::Endian::CategoryEnum & e)
{
    return std::make_shared<bytes::Trait>(e,
        std::make_shared<bytes::trait::capacity::Extended>(),
        std::make_shared<bytes::trait::element::Direct>(),
        std::make_shared<bytes::trait::modifier::Direct>());
}

inline std::shared_ptr<bytes::Trait> 
    Base::GetTrait(const bytes::Trait & t)
{
    return std::make_shared<bytes::Trait>(t);
}

template<typename TCapacity>
inline std::shared_ptr<bytes::Trait> 
    Base::SetCapacityTrait(const bytes::Trait & t)
{
    return std::make_shared<bytes::Trait>(std::make_shared<TCapacity>(),
        t.GetElement()->Copy(), t.GetModifier()->Copy());
}

inline Base::Base() :
    m_ptr(std::make_shared<bytes::Pointer>(GetTrait()->Size())),
    m_segment(m_ptr->Share(0, m_ptr->Size(), GetTrait()))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

inline Base::Base(const bytes::Endian::CategoryEnum & e) :
    m_ptr(std::make_shared<bytes::Pointer>(GetTrait()->Size())),
    m_segment(m_ptr->Share(0, m_ptr->Size(), GetTrait(e)))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

inline Base::Base(const bytes::Trait & t) :
    m_ptr(std::make_shared<bytes::Pointer>(t.Size())),
    m_segment(m_ptr->Share(0, m_ptr->Size(), GetTrait(t)))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

inline Base::Base(const std::shared_ptr<bytes::Trait> & t) :
    m_ptr(std::make_shared<bytes::Pointer>(t->Size())),
    m_segment(m_ptr->Share(0, m_ptr->Size(), t))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

inline Base::Base(const std::size_t & s) :
    m_ptr(std::make_shared<bytes::Pointer>(s)),
    m_segment(m_ptr->Share(0, s, GetTrait()))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

inline Base::Base(const std::size_t & s, 
    const bytes::Endian::CategoryEnum & e) :
        m_ptr(std::make_shared<bytes::Pointer>(s)),
        m_segment(m_ptr->Share(0, s, GetTrait(e)))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

inline Base::Base(const std::size_t & s, const bytes::Trait & t) :
    m_ptr(std::make_shared<bytes::Pointer>(s)),
    m_segment(m_ptr->Share(0, s, GetTrait(t)))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

inline Base::Base(const std::size_t & s, 
    const std::shared_ptr<bytes::Trait> & t) :
        m_ptr(std::make_shared<bytes::Pointer>(s)),
        m_segment(m_ptr->Share(0, s, t))
{
    bytes::Assign::Operator(m_segment, std::uint8_t(0));
}

template<std::size_t N>
inline Base::Base(const std::uint8_t (&b)[N]) :
    m_ptr(std::make_shared<bytes::Pointer>(N)),
    m_segment(m_ptr->Share(0, N, GetTrait()))
{
    bytes::Assign::Operator(m_ptr, m_segment, b);
}
template<std::size_t N>
inline Base::Base(const std::uint8_t (&b)[N], 
    const bytes::Endian::CategoryEnum & e) :
        m_ptr(std::make_shared<bytes::Pointer>(N)),
        m_segment(m_ptr->Share(0, N, GetTrait(e)))
{
    bytes::Assign::Operator(m_ptr, m_segment, b);
}

template<std::size_t N>
inline Base::Base(const std::uint8_t (&b)[N], const bytes::Trait & t) :
    m_ptr(std::make_shared<bytes::Pointer>(N)),
    m_segment(m_ptr->Share(0, N, GetTrait(t)))
{
    bytes::Assign::Operator(m_ptr, m_segment, b);
}

template<std::size_t N>
inline Base::Base(const std::uint8_t (&b)[N], 
    const std::shared_ptr<bytes::Trait> & t) :
        m_ptr(std::make_shared<bytes::Pointer>(N)),
        m_segment(m_ptr->Share(0, N, t))
{
    bytes::Assign::Operator(m_ptr, m_segment, b);
}

inline Base::Base(const std::uint8_t * ptr, const std::size_t & s) :
    m_ptr(std::make_shared<bytes::Pointer>(s)),
    m_segment(m_ptr->Share(0, s, GetTrait()))
{
    bytes::Assign::Operator(m_ptr, m_segment, ptr, s);
}

inline Base::Base(const std::uint8_t * ptr, const std::size_t & s,
    const bytes::Endian::CategoryEnum & e) :
        m_ptr(std::make_shared<bytes::Pointer>(s)),
        m_segment(m_ptr->Share(0, s, GetTrait(e)))
{
    bytes::Assign::Operator(m_ptr, m_segment, ptr, s);
}

inline Base::Base(const std::uint8_t * ptr, const std::size_t & s, 
    const bytes::Trait & t) :
        m_ptr(std::make_shared<bytes::Pointer>(s)),
        m_segment(m_ptr->Share(0, s, GetTrait(t)))
{
    bytes::Assign::Operator(m_ptr, m_segment, ptr, s);
}

inline Base::Base(const std::uint8_t * ptr, const std::size_t & s,
    const std::shared_ptr<bytes::Trait> & t) :
        m_ptr(std::make_shared<bytes::Pointer>(s)),
        m_segment(m_ptr->Share(0, s, t))
{
    bytes::Assign::Operator(m_ptr, m_segment, ptr, s);
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(0, s, GetTrait());
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s, const bytes::Endian::CategoryEnum & e) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(0, s, GetTrait(e));
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s, const bytes::Trait & t) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(0, s, GetTrait(t));
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s, const std::shared_ptr<bytes::Trait> & t) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(0, s, t);
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(bg, ed, GetTrait());
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed, 
    const bytes::Endian::CategoryEnum & e) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(bg, ed, GetTrait(e));
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed, 
    const bytes::Trait & t) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(bg, ed, GetTrait(t));
}

inline Base::Base(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed, 
    const std::shared_ptr<bytes::Trait> & t) :
        m_ptr(ptr),
        m_segment(nullptr)
{
    if (Validation(*this)) m_segment = m_ptr->Share(bg, ed, t);
}

inline Base::~Base()
{
    m_ptr = nullptr;
    m_segment = nullptr;
}

inline Base::Base(const Base & cpy) :
    m_ptr(std::make_shared<bytes::Pointer>(cpy.m_segment->Size())),
    m_segment(m_ptr->Share(0, cpy.m_segment->Size(), 
        GetTrait(cpy.m_segment->Trait())))
{
    if (Validation(*this)) bytes::Assign::Operator(m_ptr, m_segment, 
        cpy.m_segment);
}

inline Base::Base(Base && mov) :
    m_ptr(mov.m_ptr),
    m_segment(mov.m_segment)
{
    Default(mov);
}

inline Base & Base::operator=(Base && b)
{
    m_ptr = b.m_ptr;
    m_segment = b.m_segment;
    Default(b);
    return *this;
}

std::shared_ptr<bytes::Pointer> Base::GetPointer()
{
    return m_ptr;
}

std::shared_ptr<const bytes::Pointer> Base::GetPointer() const
{
    return std::const_pointer_cast<const bytes::Pointer>(m_ptr);
}

std::shared_ptr<bytes::ptr::Segment> Base::GetSegment()
{
    return m_segment;
}

std::shared_ptr<const bytes::ptr::Segment> Base::GetSegment() const
{
    return std::const_pointer_cast<const bytes::ptr::Segment>(m_segment);
}

} //!bytes

#endif //!BYTES_BASE_H_
