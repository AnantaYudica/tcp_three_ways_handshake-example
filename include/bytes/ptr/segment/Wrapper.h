#ifndef BYTES_PTR_SEGMENT_WRAPPER_H_
#define BYTES_PTR_SEGMENT_WRAPPER_H_

#include <cstdint>
#include <memory>
#include <utility>

#include "../Segment.h"
#include "../Object.h"
#include "../../Trait.h"

namespace bytes
{
namespace ptr
{
namespace segment
{

class Warpper : public bytes::ptr::Segment
{
public:
    inline Warpper();
    inline Warpper(const std::size_t & bg, const std::size_t & ed,
        const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
    inline Warpper(const std::size_t & bg, const std::size_t & ed,
        const std::uint8_t & off, 
        const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline ~Warpper();
public:
    inline Warpper(const Warpper & cpy);
    inline Warpper(Warpper && mov);
public:
    inline Warpper & operator=(const Warpper & cpy);
    inline Warpper & operator=(Warpper && mov);
public:
    using bytes::ptr::Segment::GetTrait;
public:
    using bytes::ptr::Segment::Offset;
public:
    using bytes::ptr::Segment::Begin;
public:
    using bytes::ptr::Segment::End;
public:
    inline std::size_t Reallocate(const std::size_t & s);
    inline void Reallocate(const std::size_t & i, const std::size_t & s,
        const std::size_t & ns);
};

inline Warpper::Warpper()
{}

inline Warpper::Warpper(const std::size_t & bg, const std::size_t & ed,
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::ptr::Segment(bg, ed, o, t)
{} 

inline Warpper::Warpper(const std::size_t & bg, const std::size_t & ed,
    const std::uint8_t & off, 
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::ptr::Segment(bg, ed, off, o, t)
{}

inline Warpper::~Warpper()
{}

inline Warpper::Warpper(const Warpper & cpy) :
    bytes::ptr::Segment(cpy)
{}

inline Warpper::Warpper(Warpper && mov) :
    bytes::ptr::Segment(std::move(mov))
{}

inline Warpper & Warpper::operator=(const Warpper & cpy)
{
    bytes::ptr::Segment::operator=(cpy);
    return *this;
}

inline Warpper & Warpper::operator=(Warpper && mov)
{
    bytes::ptr::Segment::operator=(std::move(mov));
    return *this;
}

inline std::size_t Warpper::Reallocate(const std::size_t & s)
{
    return bytes::ptr::Segment::Reallocate(s);
}

inline void Warpper::Reallocate(const std::size_t & i, const std::size_t & s,
    const std::size_t & ns)
{
    if (s == ns) return;
    const bool isinc = s < ns;
    const std::size_t d = (isinc ? ns - s : s - ns), ied = i + ns;
    const bool isbg_after = Begin() >= ied, ised_before = End() <= i;

    if (isbg_after && isinc)
    {
        Begin(Begin() + d);
        End(End() + d);
    }
    else if (isbg_after && !isinc)
    {
        Begin(Begin() - d);
        End(End() - d);
    }
    else if (!ised_before && !isbg_after)
        Reallocate(ns);
}

} //!segment

} //!ptr

} //!bytes

#endif //!BYTES_PTR_SEGMENT_WRAPPER_H_
