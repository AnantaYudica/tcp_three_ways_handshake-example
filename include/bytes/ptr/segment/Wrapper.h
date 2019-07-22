#ifndef BYTES_PTR_SEGMENT_WRAPPER_H_
#define BYTES_PTR_SEGMENT_WRAPPER_H_

#include <cstdint>
#include <memory>
#include <utility>

#include "../Segment.h"
#include "../Object.h"

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
        const std::shared_ptr<bytes::ptr::Object> & o);
public:
    inline ~Warpper();
public:
    inline Warpper(const Warpper & cpy);
    inline Warpper(Warpper && mov);
public:
    inline Warpper & operator=(const Warpper & cpy);
    inline Warpper & operator=(Warpper && mov);
public:
    using bytes::ptr::Segment::Begin;
public:
    using bytes::ptr::Segment::End;
public:
    inline void Resize(const std::size_t & i, const std::size_t & s,
        const std::size_t & ns);
};

inline Warpper::Warpper()
{}

inline Warpper::Warpper(const std::size_t & bg, const std::size_t & ed,
    const std::shared_ptr<bytes::ptr::Object> & o) :
        bytes::ptr::Segment(bg, ed, o)
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

inline void Warpper::Resize(const std::size_t & i, const std::size_t & s,
    const std::size_t & ns)
{
    if (s == ns) return;
    const bool isinc = s < ns;
    const std::size_t d = (isinc ? ns - s : s - ns);
    const bool isbg  = Begin() > (i + d), ised = End() > (i + d);
    if (isbg && isinc)
        Begin(Begin() + d);
    else if(isbg && !isinc) 
        Begin(Begin() - d);
    if (ised && isinc)
        End(End() + d);
    else if (ised && !isinc)
        End(End() - d);
}

} //!segment

} //!ptr

} //!bytes

#endif //!BYTES_PTR_SEGMENT_WRAPPER_H_
