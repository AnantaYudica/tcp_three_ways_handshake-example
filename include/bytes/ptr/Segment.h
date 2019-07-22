#ifndef BYTES_PTR_SEGMENT_H_
#define BYTES_PTR_SEGMENT_H_

#include <cstdint>
#include <utility>
#include <memory>

#include "Object.h"

namespace bytes
{
namespace ptr
{

class Segment
{
private:
    std::size_t m_begin;
    std::size_t m_end;
    std::shared_ptr<bytes::ptr::Object> m_object;
public:
    inline Segment();
    inline Segment(const std::size_t & bg, const std::size_t & ed,
        const std::shared_ptr<bytes::ptr::Object> & o);
    inline ~Segment();
public:
    inline Segment(const Segment & cpy);
    inline Segment(Segment && mov);
public:
    inline Segment & operator=(const Segment & cpy);
    inline Segment & operator=(Segment && mov);
public:
    inline bool IsSameObject(const Segment & seg) const;
public:
    inline std::size_t Begin() const;
public:
    inline std::size_t End() const;
public:
    inline std::size_t Size() const;
public:
    inline std::uint8_t & At(const std::size_t & i);
    inline const std::uint8_t & At(const std::size_t & i) const;
public:
    inline std::uint8_t * Get();
    inline const std::uint8_t * Get() const;
public:
    inline operator bool() const;
public:
    inline std::uint8_t & operator[](const std::size_t & i);
    inline const std::uint8_t & operator[](const std::size_t & i) const;
public:
    inline bool operator==(const Segment & b) const;
public:
    inline bool operator!=(const Segment & b) const;
};

inline Segment::Segment() :
    m_begin(0),
    m_end(0),
    m_object(nullptr)
{}

inline Segment::Segment(const std::size_t & bg, const std::size_t & ed,
    const std::shared_ptr<bytes::ptr::Object> & o) :
        m_begin(bg),
        m_end(ed),
        m_object(o)
{}

inline Segment::~Segment()
{
    m_begin = 0;
    m_end = 0;
    m_object = nullptr;
}

inline Segment::Segment(const Segment & cpy) :
    m_begin(cpy.m_begin),
    m_end(cpy.m_end),
    m_object(std::make_shared<bytes::ptr::Object>(cpy.m_object, 
        m_begin, m_end))
{}

inline Segment::Segment(Segment && mov) :
    m_begin(mov.m_begin),
    m_end(mov.m_end),
    m_object(mov.m_object)
{
    mov.m_begin = 0;
    mov.m_end = 0;
    mov.m_object = nullptr;
}

inline Segment & Segment::operator=(const Segment & cpy)
{
    m_begin = cpy.m_begin;
    m_end = cpy.m_end;
    m_object = std::make_shared<bytes::ptr::Object>(cpy.m_object,
        m_begin, m_end);
    return *this;
}

inline Segment & Segment::operator=(Segment && mov)
{
    m_begin = mov.m_begin;
    m_end = mov.m_end;
    m_object = mov.m_object;
    mov.m_begin = 0;
    mov.m_end = 0;
    mov.m_object = nullptr;
    return *this;
}

inline bool Segment::IsSameObject(const Segment & seg) const
{
    return seg.m_object == m_object;
}

inline std::size_t Segment::Begin() const
{
    return m_begin;
}

inline std::size_t Segment::End() const
{
    return m_end;
}

inline std::size_t Segment::Size() const
{
    return m_end - m_begin;
}

inline std::uint8_t & Segment::At(const std::size_t & i)
{
    if (!m_object) return *bytes::ptr::Object::Null();
    return m_object->At(m_begin + i);
}

inline const std::uint8_t & Segment::At(const std::size_t & i) const
{
    if (!m_object) return *bytes::ptr::Object::Null();
    return m_object->At(m_begin + i);
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
    return Begin() != End() && !m_object && !*m_object;
}

inline std::uint8_t & Segment::operator[](const std::size_t & i)
{
    return At(i);
}

inline const std::uint8_t & Segment::operator[](const std::size_t & i) const
{
    return At(i);
}

inline bool Segment::operator==(const Segment & b) const
{
    return m_object && b.m_object && m_begin == b.m_begin && 
        m_end == b.m_end;
}

inline bool Segment::operator!=(const Segment & b) const
{
    return !(*this == b);
}

} //!ptr

} //!bytes

#endif //!BYTES_PTR_SEGMENT_H_
