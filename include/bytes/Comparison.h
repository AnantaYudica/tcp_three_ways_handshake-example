#ifndef BYTES_COMPARISON_H_
#define BYTES_COMPARISON_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "sys/Endian.h"
#include "ptr/Segment.h"

namespace bytes
{

class Comparison
{
public:
    typedef bytes::ptr::Segment SegmentType;
    typedef const SegmentType ConstSegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
    typedef std::shared_ptr<ConstSegmentType> ConstSegmentPtrType;
public:
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size, 
        ConstSegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size, 
        ConstSegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size, 
        SegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size, 
        SegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size,
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, const std::size_t & a_size,
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg,
        SegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg,
        SegmentPtrType b_segment, const std::size_t & b_bg,
        const std::size_t & b_size);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, 
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, 
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, 
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, 
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(ConstSegmentPtrType a_segment,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(SegmentPtrType a_segment,
        ConstSegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(ConstSegmentPtrType a_segment,
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(SegmentPtrType a_segment,
        SegmentPtrType b_segment, const std::size_t & b_bg);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, ConstSegmentPtrType b_segment);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, ConstSegmentPtrType b_segment);
    static inline int Operation(ConstSegmentPtrType a_segment,
        const std::size_t & a_bg, SegmentPtrType b_segment);
    static inline int Operation(SegmentPtrType a_segment,
        const std::size_t & a_bg, SegmentPtrType b_segment);
    static inline int Operation(ConstSegmentPtrType a_segment,
        ConstSegmentPtrType b_segment);
    static inline int Operation(SegmentPtrType a_segment,
        ConstSegmentPtrType b_segment);
    static inline int Operation(ConstSegmentPtrType a_segment,
        SegmentPtrType b_segment);
    static inline int Operation(SegmentPtrType a_segment,
        SegmentPtrType b_segment);
private:
    inline Comparison() = delete;
public:
    inline ~Comparison() = delete;
};

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size, 
    ConstSegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    std::size_t i_st = a_bg, j_st = b_bg;
    for (std::size_t k = a_size - 1, l = b_size - 1; 
        k < a_size && l < b_size;)
    {
        const std::size_t i = a_segment->Next(0, i_st),
            j = a_segment->Next(0, j_st);
        if (k != l)
        {
            if (k > l)
            {
                if (a_segment->At(i) != std::uint8_t(0)) return 1;
                ++i_st; --k; 
            }
            else
            {
                if (b_segment->At(j) != std::uint8_t(0)) return -1;
                ++j_st; --l; 
            }
            continue;
        }
        if (a_segment->At(i) == b_segment->At(j)) 
        {
            const bool is_a_end = a_segment->IsEnd(i) && k >= a_size, 
                is_b_end = a_segment->IsEnd(j) && l >= b_size;
            if (!is_a_end && !is_b_end)
            {
                ++i_st; ++j_st;
                --k; --l;
            } 
            else if (!is_a_end) return 1;
            else return -1;
        }
        else return a_segment->At(i) > b_segment->At(j) ? 1 : -1;
    }
    return 0;
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size, 
    ConstSegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        a_bg, a_size, b_segment, b_bg, b_size);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size, 
    SegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    return Comparison::Operation(a_segment, a_bg, a_size, 
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg, b_size);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size, 
    SegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        a_bg, a_size, std::const_pointer_cast<ConstSegmentType>(b_segment), 
        b_bg, b_size);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(a_segment, a_bg, a_size,
        b_segment, b_bg, b_segment->Size());
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        a_bg, a_size, b_segment, b_bg);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size,
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(a_segment, a_bg, a_size,
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, const std::size_t & a_size,
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment), 
        a_bg, a_size, std::const_pointer_cast<ConstSegmentType>(b_segment), 
        b_bg);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    return Comparison::Operation(a_segment, a_bg, a_segment->Size(),
        b_segment, b_bg, b_size);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment), 
        a_bg, b_segment, b_bg, b_size);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg,
    SegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    return Comparison::Operation(a_segment, a_bg, 
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg, b_size);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg,
    SegmentPtrType b_segment, const std::size_t & b_bg,
    const std::size_t & b_size)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment), 
        a_bg, std::const_pointer_cast<ConstSegmentType>(b_segment), 
        b_bg, b_size);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, 
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(a_segment, a_bg, a_segment->Size(),
        b_segment, b_bg, b_segment->Size());
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, 
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment), a_bg,
        b_segment, b_bg);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, 
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(a_segment, a_bg,
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, 
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment), a_bg,
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(a_segment, 0, b_segment, b_bg);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    ConstSegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        b_segment, b_bg);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(a_segment,
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    SegmentPtrType b_segment, const std::size_t & b_bg)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        std::const_pointer_cast<ConstSegmentType>(b_segment), b_bg);
}


inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, ConstSegmentPtrType b_segment)
{
    return Comparison::Operation(a_segment, a_bg, b_segment, 0);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, ConstSegmentPtrType b_segment)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        a_bg, b_segment);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    const std::size_t & a_bg, SegmentPtrType b_segment)
{
    return Comparison::Operation(a_segment,
        a_bg, std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    const std::size_t & a_bg, SegmentPtrType b_segment)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment), a_bg, 
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    ConstSegmentPtrType b_segment)
{
    return Comparison::Operation(a_segment, 0, b_segment, 0);
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    ConstSegmentPtrType b_segment)
{
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        b_segment);
}

inline int Comparison::Operation(ConstSegmentPtrType a_segment,
    SegmentPtrType b_segment)
{
    return Comparison::Operation(a_segment,
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline int Comparison::Operation(SegmentPtrType a_segment,
    SegmentPtrType b_segment)
{
    
    return Comparison::Operation(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

} //!bytes

#endif //!BYTES_COMPARISON_H_
