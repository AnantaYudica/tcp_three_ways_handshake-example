#ifndef BYTES_ASSIGN_H_
#define BYTES_ASSIGN_H_

#include <cstdint>
#include <cstddef>
#include <memory>
#include <limits>

#include "sys/Endian.h"
#include "Pointer.h"
#include "ptr/Segment.h"

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
    for(std::size_t i = a_bg, j = b_bg; i < a_size; ++i, ++j)
    {
        if (b_segment->IsEnd(j) || j >= b_size) 
            a_segment->At(i) = std::uint8_t(0);
        else a_segment->At(i) = b_segment->At(j);
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
    for(std::size_t i = a_bg, j = 0; i < a_size; ++i, ++j) 
    {
        if (j >= b_size) 
            a_segment->At(i) = std::uint8_t(0);
        else a_segment->At(i) = b_ptr[j];
    }
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment, const std::size_t & a_bg,
    const std::uint8_t * b_ptr, const std::size_t & b_size)
{
    const std::size_t a_size = a_segment->Size() - a_bg;
    if (b_size > a_size)
        a_ptr->Reallocate(a_bg + b_size, a_segment);
    Assign::Operator(a_ptr, a_segment, a_bg, b_ptr, b_size);
}

inline void Assign::Operator(PointerPtrType a_ptr,
    SegmentPtrType a_segment,
    const std::uint8_t * b_ptr, const std::size_t & b_size)
{
    Assign::Operator(a_ptr, a_segment, 0, b_ptr, b_size);
}

} //!bytes

#endif //!BYTES_ASSIGN_H_
