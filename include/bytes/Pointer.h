#ifndef BYTES_POINTER_H_
#define BYTES_POINTER_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <utility>
#include <cstring>
#include <queue>

#include "Endian.h"
#include "Trait.h"
#include "ptr/Object.h"
#include "ptr/Segment.h"
#include "ptr/Segment/Wrapper.h"

namespace bytes
{

class Pointer
{
public:
    static inline bool IsEnd(const std::uint8_t * ptr);
private:
    std::shared_ptr<bytes::ptr::Object> m_object;
    std::vector<std::shared_ptr<bytes::ptr::segment::Warpper>> m_segments;
public:
    inline Pointer();
    inline Pointer(const std::size_t & s);
    inline ~Pointer();
public:
    inline Pointer(const Pointer & cpy);
    inline Pointer(Pointer && mov);
public:
    inline Pointer & operator=(const Pointer & cpy);
    inline Pointer & operator=(Pointer && mov);
public:
    inline bool IsSameObject(const Pointer & b) const;
    inline bool 
        IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const;
public:
    inline bool Reallocate(const std::size_t & sz, 
        const std::shared_ptr<bytes::ptr::Segment> & seg);
public:
    inline std::shared_ptr<bytes::ptr::Segment> Share(const std::size_t & bg, 
        const std::size_t & ed, const std::shared_ptr<bytes::Trait> & t);
public:
    inline std::size_t Size() const;
public:
    inline bool Has(const std::shared_ptr<bytes::ptr::Segment> & seg) const;
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
    inline bool operator==(const Pointer & b) const;
public:
    inline bool operator!=(const Pointer & b) const;
};

inline bool Pointer::IsEnd(const std::uint8_t * ptr)
{
    return ptr == bytes::ptr::Object::Null();
}

inline Pointer::Pointer() :
    m_object(nullptr)
{}

inline Pointer::Pointer(const std::size_t & s) :
    m_object(nullptr)
{
    if (s > 0) m_object = std::make_shared<bytes::ptr::Object>(s);
}

inline Pointer::~Pointer()
{
    m_object = nullptr;
    m_segments.clear();
}

inline Pointer::Pointer(const Pointer & cpy) :
    m_object(nullptr)
{
    if(cpy) m_object = std::make_shared<bytes::ptr::Object>(*(cpy.m_object));
}

inline Pointer::Pointer(Pointer && mov) :
    m_object(mov.m_object),
    m_segments(mov.m_segments)
{
    mov.m_object = nullptr;
    mov.m_segments.clear();
}

inline Pointer & Pointer::operator=(const Pointer & cpy)
{
    if (cpy)
        m_object = std::make_shared<bytes::ptr::Object>(*(cpy.m_object));
    else
        m_object = nullptr;
    m_segments.clear();
    return *this;
}

inline Pointer & Pointer::operator=(Pointer && mov)
{
    m_object = mov.m_object;
    m_segments = mov.m_segments;
    mov.m_object = nullptr;
    mov.m_segments.clear();
    return *this;
}

inline bool Pointer::IsSameObject(const Pointer & b) const
{
    return (*this) && *m_object == *b.m_object;
}

inline bool 
    Pointer::IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const
{
    return (*this) && *m_object == *b;
}

inline bool Pointer::Reallocate(const std::size_t & sz, 
    const std::shared_ptr<bytes::ptr::Segment> & seg)
{
    if(!*this || !seg || !*seg) return false;
    std::size_t ns;
    const std::size_t od = seg->Size();
    bool f = false;
    std::queue<std::shared_ptr<bytes::ptr::segment::Warpper>> q;
    for(auto it = m_segments.begin(); it != m_segments.end(); )
    {
        if ((*it).use_count() == 1)
        {
            it = m_segments.erase(it);
            continue;
        }
        if ((**it) == *seg)
        {
            ns = (*it)->Resize(sz);
            if (ns == od) return false;
            m_object->Reallocate(ns, seg->Begin(), seg->Begin() + od, 
                &((*it)->Trait().GetEndian()));
            f = true;
            while (!q.empty())
            {
                q.front()->Resize(seg->Begin(), od, ns);
                q.pop();
            }
        }
        else 
        {
            if (!f) q.push(*it);
            else (*it)->Resize(seg->Begin(), od, ns);
        }
        ++it;
    }
    return true;
}

inline std::shared_ptr<bytes::ptr::Segment> 
    Pointer::Share(const std::size_t & bg, const std::size_t & ed,
        const std::shared_ptr<bytes::Trait> & t)
{
    if (!*this) return std::make_shared<bytes::ptr::Segment>();
    for(auto it = m_segments.begin(); it != m_segments.end(); ++it)
    {
        if ((*it)->Begin() == bg && (*it)->End() == ed && (*it)->Trait() == *t)
            return (*it);
    }
    auto nseg = std::make_shared<bytes::ptr::segment::Warpper>(bg, ed, 
        m_object, t);
    m_segments.push_back(nseg);
    return nseg;
}

inline std::size_t Pointer::Size() const
{
    return m_object->Size();
}

inline bool Pointer::Has(const std::shared_ptr<bytes::ptr::Segment> & seg) const
{
    return seg && seg->IsSameObject(m_object);
}

inline std::uint8_t & Pointer::At(const std::size_t & i)
{
    return m_object->At(0);
}

inline const std::uint8_t & Pointer::At(const std::size_t & i) const
{
     return m_object->At(0);
}

inline std::uint8_t * Pointer::Get()
{
    return m_object->Get();
}

inline const std::uint8_t * Pointer::Get() const
{
    return m_object->Get();
}

inline Pointer::operator bool() const
{
    return m_object && static_cast<bool>(*m_object);
}

inline std::uint8_t & Pointer::operator[](const std::size_t & i)
{
    return At(i);
}

inline const std::uint8_t & Pointer::operator[](const std::size_t & i) const
{
    return At(i);
}

inline bool Pointer::operator==(const Pointer & b) const
{
    const bool ca = static_cast<bool>(*this),
        cb = static_cast<bool>(b);
    return (!ca && !cb) || (ca && cb && m_object == b.m_object &&
        m_segments == b.m_segments);
}

inline bool Pointer::operator!=(const Pointer & b) const
{
    return !(*this == b);
}

} //!bytes

#endif //!BYTES_POINTER_H_
