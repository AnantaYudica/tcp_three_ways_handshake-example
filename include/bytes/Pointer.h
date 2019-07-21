#ifndef BYTES_POINTER_H_
#define BYTES_POINTER_H_

#include <cstdint>
#include <memory>
#include <vector>
#include <utility>
#include <cstring>

#include "ptr/Counter.h"
#include "ptr/Segment.h"

namespace bytes
{

class Pointer
{
private:
    typedef bytes::ptr::Counter<std::shared_ptr<bytes::ptr::Segment>>
        CounterSegmentPtrType;
private:
    static inline std::uint8_t * Null();
public:
    static inline bool IsEnd(const std::uint8_t * ptr);
private:
    std::uint8_t * m_ptr;
    std::size_t m_size;
    std::vector<CounterSegmentPtrType> m_segments;
public:
    inline Pointer();
    inline Pointer(const std::size_t & s);
    inline ~Pointer();
public:
    inline Pointer(const Pointer & cpy);
    inline Pointer(Pointer && mov);
public:
    inline Pointer & operator=(const Pointer & cpy) = delete;
    inline Pointer & operator=(Pointer && mov) = delete;
public:
    inline void Reallocate(const std::size_t & sz);
    inline void Reallocate(const std::size_t & sz, 
        const std::shared_ptr<bytes::ptr::Segment> & seg);
private:
    inline void Reallocate(const std::size_t & sz, const std::size_t & bg,
        const std::size_t & ed);
public:
    inline std::shared_ptr<bytes::ptr::Segment> Share(const std::size_t & bg, 
        const std::size_t & ed);
public:
    inline void Reset(const std::shared_ptr<bytes::ptr::Segment> & seg);
public:
    inline std::size_t Size() const;
public:
    inline bool Has(const std::shared_ptr<bytes::ptr::Segment> & seg) const;
public:
    inline std::uint8_t & At(const std::size_t & i);
    inline const std::uint8_t & At(const std::size_t & i) const;
    inline std::uint8_t & At(const std::shared_ptr<bytes::ptr::Segment> & seg, 
        const std::size_t & i);
    inline const std::uint8_t & 
        At(const std::shared_ptr<bytes::ptr::Segment> & seg,
            const std::size_t & i) const;
public:
    inline std::uint8_t * Get();
    inline const std::uint8_t * Get() const;
    inline std::uint8_t * 
        Get(const std::shared_ptr<bytes::ptr::Segment> & seg);
    inline const std::uint8_t * 
        Get(const std::shared_ptr<bytes::ptr::Segment> & seg) const;
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

inline std::uint8_t * Pointer::Null()
{
    static std::uint8_t n = std::uint8_t(0);
    return &n;
}

inline bool Pointer::IsEnd(const std::uint8_t * ptr)
{
    return ptr == Null();
}

inline Pointer::Pointer() :
    m_ptr(nullptr),
    m_size(0)
{}

inline Pointer::Pointer(const std::size_t & s) :
    m_ptr(nullptr),
    m_size(s)
{
    if (m_size > 0)
        m_ptr = new std::uint8_t[m_size];
}

inline Pointer::~Pointer()
{
    if (m_ptr) delete[] m_ptr;
    m_size = 0;
    m_segments.clear();
}

inline Pointer::Pointer(const Pointer & cpy) :
    m_ptr(nullptr),
    m_size(cpy.m_size)
{
    if (cpy.m_ptr && m_size > 0)
    {
        m_ptr = new std::uint8_t[m_size];
        std::memcpy(m_ptr, cpy.m_ptr, m_size);
    }
}

inline Pointer::Pointer(Pointer && mov) :
    m_ptr(mov.m_ptr),
    m_size(mov.m_size),
    m_segments(mov.m_segments)
{
    mov.m_ptr = nullptr;
    mov.m_size = 0;
    mov.m_segments.clear();
}

inline void Pointer::Reallocate(const std::size_t & sz)
{
    return Reallocate(sz, 0, m_size);
}

inline void Pointer::Reallocate(const std::size_t & sz, 
    const std::shared_ptr<bytes::ptr::Segment> & seg)
{
    if(!seg || !*seg) return;
    Reallocate(sz, seg->Begin(), seg->End());
    for(auto it = m_segments.begin(); it != m_segments.end(); ++it)
    {
        if ((*it).Get() == seg) continue;
        (*it).Get()->Resize(seg->Begin(), seg->Size(), sz);
    }
    seg->End(seg->Begin() + sz);
}

inline void Pointer::Reallocate(const std::size_t & sz, const std::size_t & bg,
    const std::size_t & ed)
{
    if (m_size == sz) return;
    const std::size_t tsz = sz + bg + (m_size - ed); 
    std::uint8_t * nptr = new std::uint8_t[tsz];
    if (*this)
    {
        std::memcpy(nptr, m_ptr, bg);
        std::memcpy(nptr + bg, m_ptr + m_size, ed - bg);
        std::memcpy(nptr + ed, m_ptr + m_size, (m_size - ed));
    }
    if (m_ptr) delete[] m_ptr;
    m_ptr = nptr;
    m_size = tsz;
}

inline std::shared_ptr<bytes::ptr::Segment> 
    Pointer::Share(const std::size_t & bg, const std::size_t & ed)
{
    if (!*this) return std::make_shared<bytes::ptr::Segment>();
    for(auto it = m_segments.begin(); it != m_segments.end(); ++it)
    {
        if ((*it).Get()->Begin() == bg && (*it).Get()->End() == ed)
            return (++(*it)).Get();
    }
    auto nseg = std::make_shared<bytes::ptr::Segment>(bg, ed);
    m_segments.push_back(nseg);
    return nseg;
}

inline void Pointer::Reset(const std::shared_ptr<bytes::ptr::Segment> & seg)
{
    if (!*this) return;
    for(auto it = m_segments.begin(); it != m_segments.end(); ++it)
    {
        if ((*it).Get() == seg)
        {
            if (--(*it)) m_segments.erase(it);
            break;
        } 
    }
}

inline std::size_t Pointer::Size() const
{
    return m_size;
}

inline bool Pointer::Has(const std::shared_ptr<bytes::ptr::Segment> & seg) const
{
    for(auto it = m_segments.begin(); it != m_segments.end(); ++it)
    {
        if ((*it).Get() == seg) return true;
    }
    return false;
}

inline std::uint8_t & Pointer::At(const std::size_t & i)
{
    if (i >= m_size) return *Null();
    return m_ptr[i];
}

inline const std::uint8_t & Pointer::At(const std::size_t & i) const
{
    if (i >= m_size) return *Null();
    return m_ptr[i];
}

inline std::uint8_t & 
    Pointer::At(const std::shared_ptr<bytes::ptr::Segment> & seg, 
        const std::size_t & i)
{
    if (!seg && i < seg->Begin() && i >= seg->End() && i >= m_size) 
        return *Null();
    return m_ptr[seg->Begin() + i];
}

inline const std::uint8_t & 
    Pointer::At(const std::shared_ptr<bytes::ptr::Segment> & seg, 
        const std::size_t & i) const
{
    if (!seg && i < seg->Begin() && i >= seg->End() && i >= m_size) 
        return *Null();
    return m_ptr[seg->Begin() + i];
}

inline std::uint8_t * Pointer::Get()
{
    if (m_ptr) return m_ptr;
    return Null();
}

inline const std::uint8_t * Pointer::Get() const
{
    if (m_ptr) return m_ptr;
    return Null();
}

inline std::uint8_t * 
    Pointer::Get(const std::shared_ptr<bytes::ptr::Segment> & seg)
{
    if (seg && seg->Begin() < m_size) return m_ptr + seg->Begin();
    return Null();
}

inline const std::uint8_t * 
    Pointer::Get(const std::shared_ptr<bytes::ptr::Segment> & seg) const
{
    if (seg && seg->Begin() < m_size) return m_ptr + seg->Begin();
    return Null();
}

inline Pointer::operator bool() const
{
    return m_ptr != nullptr && m_size != 0;
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
    if (m_ptr == b.m_ptr) return true;
    if (m_ptr == nullptr || b.m_ptr == nullptr || m_size != b.m_size) 
        return false;
    for (std::size_t i = 0; i < m_size; ++i)
    {
        if (m_ptr[i] != b[i]) return false;
    }
    return true;
}

inline bool Pointer::operator!=(const Pointer & b) const
{
    return !(*this == b);
}

} //!bytes

#endif //!BYTES_POINTER_H_
