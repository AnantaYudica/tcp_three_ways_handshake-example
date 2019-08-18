#ifndef BYTES_ARITHMETIC_SUBTRACTION_H_
#define BYTES_ARITHMETIC_SUBTRACTION_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "../sys/Endian.h"
#include "../ptr/Segment.h"

namespace bytes
{
namespace arithmetic
{

class Subtraction
{
public:
    typedef bytes::ptr::Segment SegmentType;
    typedef const SegmentType ConstSegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
    typedef std::shared_ptr<ConstSegmentType> ConstSegmentPtrType;
public:
    static inline void Operator(ConstSegmentPtrType a_segment, 
        ConstSegmentPtrType b_segment, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment, 
        ConstSegmentPtrType b_segment, SegmentPtrType result_segment);
    static inline void Operator(ConstSegmentPtrType a_segment, 
        SegmentPtrType b_segment, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment, 
        SegmentPtrType b_segment, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_result_segment, 
        ConstSegmentPtrType b_segment);
    static inline void Operator(SegmentPtrType a_result_segment, 
        SegmentPtrType b_segment);
public:
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t * b, const std::size_t & b_size, 
        SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t * b, const std::size_t & b_size, 
        SegmentPtrType result_segment);
public:
    template<std::size_t N>
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t (&b)[N], SegmentPtrType result_segment);
    template<std::size_t N>
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t (&b)[N], SegmentPtrType result_segment);
public:
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t & b, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t & b, SegmentPtrType result_segment);
private:
    inline Subtraction() = delete;
public:
    inline ~Subtraction() = delete;
};

inline void Subtraction::Operator(ConstSegmentPtrType a_segment, 
    ConstSegmentPtrType b_segment, SegmentPtrType result_segment)
{
    const auto & endian = bytes::sys::Endian();
    std::uint8_t c = std::uint8_t(0);
    std::size_t i = 0;
    for (; i < result_segment->Size(); ++i)
    {
        std::uint16_t val = 0;
        if (!a_segment->IsEnd(i))
            val += a_segment->At(i);
        if (!b_segment->IsEnd(i))
            val -= b_segment->At(i);
        val -= c;
        std::uint8_t * pval = reinterpret_cast<std::uint8_t *>(&val);
        c = (~pval[endian.At(1, 0, 2)] + std::uint8_t(1));
        result_segment->At(i) = pval[endian.At(0, 0, 2)];
    }
}

inline void Subtraction::Operator(SegmentPtrType a_segment, 
    ConstSegmentPtrType b_segment, SegmentPtrType result_segment)
{
    Subtraction::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        b_segment, result_segment);
}

inline void Subtraction::Operator(ConstSegmentPtrType a_segment, 
    SegmentPtrType b_segment, SegmentPtrType result_segment)
{
    Subtraction::Operator(a_segment,
        std::const_pointer_cast<ConstSegmentType>(b_segment), result_segment);
}

inline void Subtraction::Operator(SegmentPtrType a_segment, 
    SegmentPtrType b_segment, SegmentPtrType result_segment)
{
    Subtraction::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        std::const_pointer_cast<ConstSegmentType>(b_segment), result_segment);
}

inline void Subtraction::Operator(SegmentPtrType a_result_segment, 
    ConstSegmentPtrType b_segment)
{
    Subtraction::Operator(a_result_segment, b_segment, a_result_segment);
}

inline void Subtraction::Operator(SegmentPtrType a_result_segment, 
    SegmentPtrType b_segment)
{
    Subtraction::Operator(a_result_segment, 
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline void Subtraction::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    SegmentPtrType result_segment)
{
    const auto & endian = bytes::sys::Endian();
    std::uint8_t c = std::uint8_t(0);
    std::size_t i = 0;
    for (; i < result_segment->Size(); ++i)
    {
        std::uint16_t val = 0;
        if (!a_segment->IsEnd(i))
            val += a_segment->At(i);
        if (i < b_size)
            val -= b[i];
        val -= c;
        std::uint8_t * pval = reinterpret_cast<std::uint8_t *>(&val);
        c = (~pval[endian.At(1, 0, 2)] + std::uint8_t(1));
        result_segment->At(i) = pval[endian.At(0, 0, 2)];
    }
}

inline void Subtraction::Operator(SegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    SegmentPtrType result_segment)
{
    Subtraction::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        b, b_size, result_segment);
}

template<std::size_t N>
inline void Subtraction::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t (&b)[N], SegmentPtrType result_segment)
{
    Subtraction::Operator(a_segment, b, N, result_segment);
}

template<std::size_t N>
inline void Subtraction::Operator(SegmentPtrType a_segment,
    const std::uint8_t (&b)[N], SegmentPtrType result_segment)
{
    Subtraction::Operator(a_segment, b, N, result_segment);
}

inline void Subtraction::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t & b, SegmentPtrType result_segment)
{
    Subtraction::Operator(a_segment, &b, 1, result_segment);
}

inline void Subtraction::Operator(SegmentPtrType a_segment,
    const std::uint8_t & b, SegmentPtrType result_segment)
{
    Subtraction::Operator(a_segment, &b, 1, result_segment);
}

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_SUBTRACTION_H_
