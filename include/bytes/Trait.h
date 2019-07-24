#ifndef BYTES_TRAIT_H_
#define BYTES_TRAIT_H_

#include <cstdint>
#include <memory>

#include "Endian.h"
#include "sys/Endian.h"
#include "Pointer.h"
#include "ptr/Segment.h"

namespace bytes
{

class Trait
{
private:
static inline const bytes::Endian * 
    GetEndian(const bytes::Endian::CategoryEnum & e);
private:
    const bytes::Endian * m_endian;
protected:
    inline Trait();
    inline Trait(const bytes::Endian::CategoryEnum & e);
public:
    virtual inline ~Trait();
protected:
    inline Trait(const Trait & cpy);
    inline Trait(Trait && mov);
public:
    virtual inline Trait & operator=(const Trait & cpy) = 0;
    virtual inline Trait & operator=(Trait && mov) = 0;
public:
    virtual inline std::shared_ptr<Trait> Copy() const = 0;
    virtual inline std::shared_ptr<Trait> Move() = 0;
public:
    virtual inline std::size_t Size(const std::size_t & s) const = 0;
public:
    inline std::size_t Size() const;
protected:
    virtual inline std::size_t Resize(const std::size_t & cs,
        const std::size_t & ns) const = 0;
public:
    inline std::size_t Resize(std::shared_ptr<bytes::Pointer> & ptr,
        std::shared_ptr<bytes::ptr::Segment> & seg, 
        const std::size_t & s) const;
protected:
    virtual inline std::size_t At(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    inline std::uint8_t & At(std::shared_ptr<bytes::ptr::Segment> & seg,
        const std::size_t & i) const;
    inline const std::uint8_t & 
        At(const std::shared_ptr<bytes::ptr::Segment> & seg, 
            const std::size_t & i) const;
protected:
    virtual inline bool IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    inline bool IsEnd(std::shared_ptr<bytes::ptr::Segment> & seg,
        const std::size_t & i) const;
};

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
    return &bytes::sys::Endian();
}

inline Trait::Trait() :
    m_endian(&bytes::sys::Endian())
{}

inline Trait::Trait(const bytes::Endian::CategoryEnum & e) :
    m_endian(GetEndian(e))
{}

inline Trait::~Trait()
{}

inline Trait::Trait(const Trait & cpy) :
    m_endian(cpy.m_endian)
{}

inline Trait::Trait(Trait && mov) :
    m_endian(mov.m_endian)
{
    mov.m_endian = &bytes::sys::Endian();
}

inline std::size_t Trait::Resize(std::shared_ptr<bytes::Pointer> & ptr,
    std::shared_ptr<bytes::ptr::Segment> & seg, 
    const std::size_t & s) const
{
    if (!ptr && !seg) return 0;
    const std::size_t cs = seg->Size();
    if (cs == s) return s;
    const std::size_t  ns = Resize(cs, s);
    if (cs == ns) return cs;
    ptr->Reallocate(ns, seg, m_endian);
    return ns;
}

inline std::uint8_t & Trait::At(std::shared_ptr<bytes::ptr::Segment> & seg,
    const std::size_t & i) const
{
    return seg->At(At(m_endian->At(i, seg->Size()), seg->Begin(), seg->End()));
}

inline const std::uint8_t &
    Trait::At(const std::shared_ptr<bytes::ptr::Segment> & seg, 
        const std::size_t & i) const
{
    return seg->At(At(m_endian->At(i, seg->Size()), seg->Begin(), seg->End()));
}

inline bool Trait::IsEnd(std::shared_ptr<bytes::ptr::Segment> & seg,
    const std::size_t & i) const
{
    return IsEnd(i, seg->Begin(), seg->End());
}

} //!bytes

#endif //!BYTES_TRAIT_H_
