#ifndef BYTES_PTR_OBJECT_H_
#define BYTES_PTR_OBJECT_H_

#include <cstdint>
#include <cstring>

#include "../Endian.h"

namespace bytes
{
namespace ptr
{

class Object
{
public:
    static inline std::uint8_t * Null();
public:
    static inline bool IsEnd(const std::uint8_t * ptr);
private:
    std::uint8_t * m_ptr;
    std::size_t m_size;
public:
    inline Object();
    inline Object(const std::size_t & s);
public:
    inline ~Object();
public:
    inline Object(const Object & cpy);
    inline Object(const Object & cpy, const std::size_t & bg,
        const std::size_t & ed);
    inline Object(Object && mov);
public:
    inline Object & operator=(const Object & cpy) = delete;
    inline Object & operator=(Object && mov) = delete;
public:
    inline void Reallocate(const std::size_t & sz,
        const bytes::Endian * endian);
    inline void Reallocate(const std::size_t & sz, 
        const std::size_t & bg, const std::size_t & ed,
        const bytes::Endian * endian);
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
    inline bool operator==(const Object & b) const;
public:
    inline bool operator!=(const Object & b) const;
};

inline std::uint8_t * Object::Null()
{
    static std::uint8_t instance = std::uint8_t(0);
    return &instance;
}

inline bool Object::IsEnd(const std::uint8_t * ptr)
{
    return ptr == Null();
}

inline Object::Object() :
    m_ptr(nullptr),
    m_size(0)
{}

inline Object::Object(const std::size_t & s) :
    m_ptr(nullptr),
    m_size(s)
{
    if (m_size > 0)m_ptr = new std::uint8_t[m_size];
}

inline Object::~Object()
{
    if (m_ptr) delete[] m_ptr;
    m_ptr = nullptr;
    m_size = 0;
}

inline Object::Object(const Object & cpy) :
    m_ptr(nullptr),
    m_size(cpy.m_size)
{
    if (cpy.m_ptr && m_size > 0)
    {
        m_ptr = new std::uint8_t[m_size];
        std::memcpy(m_ptr, cpy.m_ptr, m_size);
    }
}

inline Object::Object(const Object & cpy, const std::size_t & bg,
    const std::size_t & ed) :
        m_ptr(nullptr),
        m_size(ed > bg ? ed - bg : 0)
{
    if (cpy.m_ptr && m_size > 0)
    {
        m_ptr = new std::uint8_t[m_size];
        std::memcpy(m_ptr, cpy.m_ptr + (bg < m_size ? bg : 0), 
            (m_size < cpy.m_size ? m_size : cpy.m_size));
    }
}

inline Object::Object(Object && mov) :
    m_ptr(mov.m_ptr),
    m_size(mov.m_size)
{
    mov.m_ptr = nullptr;
    mov.m_size = 0;
}

inline void Object::Reallocate(const std::size_t & sz,
        const bytes::Endian * endian)
{
    return Reallocate(sz, 0, m_size, endian);
}

inline void Object::Reallocate(const std::size_t & sz, 
    const std::size_t & bg, const std::size_t & ed,
        const bytes::Endian * endian)
{
    if (m_size == sz) return;
    const std::size_t bs = bg, cs = ed - bg, as = m_size - ed,
        tsz = bs + sz + as, ned = bs + sz; 
    std::uint8_t * nptr = new std::uint8_t[tsz];
    if (*this)
    {
        std::memcpy(nptr, m_ptr, bg);
        endian->Copy(nptr + bg, sz, m_ptr + bg, cs);
        std::memcpy(nptr + ned, m_ptr + ed, as);
        delete[] m_ptr;
    }
    m_ptr = nptr;
    m_size = tsz;
}

inline std::size_t Object::Size() const
{
    return m_size;
}

inline std::uint8_t & Object::At(const std::size_t & i)
{
    if (i >= m_size) return *Null();
    return m_ptr[i];
}

inline const std::uint8_t & Object::At(const std::size_t & i) const
{
    if (i >= m_size) return *Null();
    return m_ptr[i];
}

inline std::uint8_t * Object::Get()
{
    if (m_ptr) return m_ptr;
    return Null();
}

inline const std::uint8_t * Object::Get() const
{
    if (m_ptr) return m_ptr;
    return Null();
}

inline Object::operator bool() const
{
    return m_ptr != nullptr && m_size != 0;
}

inline std::uint8_t & Object::operator[](const std::size_t & i)
{
    return At(i);
}

inline const std::uint8_t & Object::operator[](const std::size_t & i) const
{
    return At(i);
}

inline bool Object::operator==(const Object & b) const
{
    return m_ptr == b.m_ptr;
}

inline bool Object::operator!=(const Object & b) const
{
    return !(*this == b);
}

} //!ptr

} //!bytes

#endif //!BYTES_PTR_OBJECT_H_
