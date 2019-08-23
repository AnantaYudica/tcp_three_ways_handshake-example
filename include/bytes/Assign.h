#ifndef BYTES_ASSIGN_H_
#define BYTES_ASSIGN_H_

#include <cstdint>
#include <cstddef>
#include <memory>
#include <limits>

#include "sys/Endian.h"
#include "Pointer.h"
#include "ptr/Segment.h"
#include "endian/Big.h"

namespace bytes
{

class Assign
{
public:
    typedef std::shared_ptr<bytes::Pointer> PointerPtrType;
    typedef bytes::ptr::Segment SegmentType;
    typedef const SegmentType ConstSegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
    typedef std::shared_ptr<ConstSegmentType> ConstSegmentPtrType;
public:
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg, 
        const std::size_t & b_size);
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        SegmentPtrType b_segment, const std::size_t & b_bg, 
        const std::size_t & b_size);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg, 
        const std::size_t & b_size);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        SegmentPtrType b_segment, const std::size_t & b_bg, 
        const std::size_t & b_size);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg, 
        const std::size_t & b_size);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment,
        SegmentPtrType b_segment, const std::size_t & b_bg, 
        const std::size_t & b_size);
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment,
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        ConstSegmentPtrType b_segment);
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        SegmentPtrType b_segment);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        ConstSegmentPtrType b_segment);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        SegmentPtrType b_segment);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, ConstSegmentPtrType b_segment);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, SegmentPtrType b_segment);
public:
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        const std::uint8_t * b_ptr, const std::size_t & b_size);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        const std::uint8_t * b_ptr, const std::size_t & b_size);
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment,
        const std::uint8_t * b_ptr, const std::size_t & b_size);
public:
    template<std::size_t N>
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        const std::uint8_t (&b)[N]);
    template<std::size_t N>
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::size_t & a_bg,
        const std::uint8_t (&b)[N]);
    template<std::size_t N>
    static inline void Operator(PointerPtrType a_ptr,
        SegmentPtrType a_segment, const std::uint8_t (&b)[N]);
public:
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::size_t & a_size,
        const std::uint8_t & b);
    static inline void Operator(SegmentPtrType a_segment, 
        const std::size_t & a_bg, const std::uint8_t & b);
    static inline void Operator(SegmentPtrType a_segment, 
        const std::uint8_t & b);
private:
    inline Assign() = delete;
public:
    inline ~Assign() = delete;
};

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg, 
    const std::size_t & b_size)
{
    std::size_t i = a_segment->Next(0, a_bg), 
        j = b_segment->Next(0, b_bg);
    for(std::size_t k = a_bg, l = b_bg; k < a_size; ++k, ++l)
    {
        if (b_segment->IsReverseEnd(j) || k >= b_size) 
            a_segment->ReverseAt(i) = std::uint8_t(0);
        else a_segment->ReverseAt(i) = b_segment->ReverseAt(j);
        i = a_segment->Next(i);
        j = b_segment->Next(j);
    }
}

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    SegmentPtrType b_segment, const std::size_t & b_bg, 
    const std::size_t & b_size)
{
    Assign::Operator(a_segment, a_bg, a_size,
        std::const_pointer_cast<ConstSegmentType>(b_segment),
        b_bg, b_size);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg, 
    const std::size_t & b_size)
{
    const std::size_t a_size = a_segment->Size() - a_bg;
    if (b_size > a_size)
        a_ptr->Reallocate(a_bg + b_size, a_segment);
    Assign::Operator(a_segment, a_bg, b_size, b_segment, b_bg, b_size);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    SegmentPtrType b_segment, const std::size_t & b_bg, 
    const std::size_t & b_size)
{
    Assign::Operator(a_ptr, a_segment, a_bg, 
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg, b_size);
}  

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg, 
    const std::size_t & b_size)
{
    Assign::Operator(a_ptr, a_segment, 0, b_segment, b_bg, b_size);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment,
    SegmentPtrType b_segment, const std::size_t & b_bg, 
    const std::size_t & b_size)
{
    Assign::Operator(a_ptr, a_segment, 0, 
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg, b_size);
}

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    Assign::Operator(a_segment, a_bg, a_size, b_segment, b_bg,
        std::numeric_limits<std::size_t>::max());
}

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    Assign::Operator(a_segment, a_bg, a_size,
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    Assign::Operator(a_ptr, a_segment, a_bg, b_segment, b_bg,
        b_segment->Size() - b_bg);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    
    Assign::Operator(a_ptr, a_segment, a_bg,
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    Assign::Operator(a_ptr, a_segment, 0, b_segment, b_bg);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment,
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    Assign::Operator(a_ptr, a_segment, 
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}
    
inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    ConstSegmentPtrType b_segment)
{

    Assign::Operator(a_segment, a_bg, a_size, b_segment, 0);
}

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    SegmentPtrType b_segment)
{
    Assign::Operator(a_segment, a_bg, a_size, 
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    ConstSegmentPtrType b_segment)
{
    Assign::Operator(a_ptr, a_segment, a_bg, b_segment, 0);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    SegmentPtrType b_segment)
{
    Assign::Operator(a_ptr, a_segment, a_bg, 
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, ConstSegmentPtrType b_segment)
{
    Assign::Operator(a_ptr, a_segment, 0, b_segment);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, SegmentPtrType b_segment)
{
    Assign::Operator(a_ptr, a_segment, 
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    const std::uint8_t * b_ptr, const std::size_t & b_size)
{
    std::size_t i = a_segment->Next(0, a_bg);
    for(std::size_t i = a_bg, j = 0, l = 0; l < a_size; ++j, ++l) 
    {
        if (j >= b_size) 
            a_segment->ReverseAt(i) = std::uint8_t(0);
        else a_segment->ReverseAt(i) = 
            b_ptr[bytes::endian::Big::Instance().ReverseAt(j, 0, b_size)];
        i = a_segment->Next(i);
    }
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    const std::uint8_t * b_ptr, const std::size_t & b_size)
{
    const std::size_t a_size = a_segment->Size() - a_bg;
    if (b_size > a_size)
        a_ptr->Reallocate(a_bg + b_size, a_segment);
    Assign::Operator(a_segment, a_bg, a_segment->Size(), b_ptr, b_size);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment,
    const std::uint8_t * b_ptr, const std::size_t & b_size)
{
    Assign::Operator(a_ptr, a_segment, 0, b_ptr, b_size);
}

template<std::size_t N>
inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    const std::uint8_t (&b)[N])
{
    Assign::Operator(a_segment, a_bg, a_size, b, N);
}

template<std::size_t N>
inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    const std::uint8_t (&b)[N])
{
    Assign::Operator(a_ptr, a_segment, a_bg, b, N);
}

template<std::size_t N>
inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::uint8_t (&b)[N])
{
    Assign::Operator(a_ptr, a_segment, b, N);
}

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::size_t & a_size,
    const std::uint8_t & b)
{
    for(std::size_t i = a_bg, j = 0; i < a_size; ++i, ++j) 
        a_segment->At(i) = b;
}

inline void Assign::Operator( SegmentPtrType a_segment, 
    const std::size_t & a_bg, const std::uint8_t & b)
{
    Assign::Operator(a_segment, a_bg, a_segment->Size(), b);
}

inline void Assign::Operator(SegmentPtrType a_segment, 
    const std::uint8_t & b)
{
    Assign::Operator(a_segment, 0, b);
}

} //!bytes

#endif //!BYTES_ASSIGN_H_
