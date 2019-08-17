#ifndef BYTES_ARITHMETIC_DIVISION_H_
#define BYTES_ARITHMETIC_DIVISION_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "../sys/Endian.h"
#include "../Pointer.h"
#include "../ptr/Segment.h"
#include "division/NewtonRaphson.h"

namespace bytes
{
namespace arithmetic
{

class Division
{
public:
    typedef std::shared_ptr<bytes::Pointer> PointerPtrType;
    typedef bytes::ptr::Segment SegmentType;
    typedef const SegmentType ConstSegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
    typedef std::shared_ptr<ConstSegmentType> ConstSegmentPtrType;
public:
    static inline void Operator(ConstSegmentPtrType numerator_segment, 
        ConstSegmentPtrType denominator_segment, 
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType numerator_segment, 
        ConstSegmentPtrType denominator_segment, 
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(ConstSegmentPtrType numerator_segment, 
        SegmentPtrType denominator_segment, 
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType numerator_segment, 
        SegmentPtrType denominator_segment, 
        PointerPtrType result_ptr, SegmentPtrType result_segment);
public:
    static inline void Operator(PointerPtrType numerator_result_ptr,
        SegmentPtrType numerator_result_segment, 
        ConstSegmentPtrType denominator_segment);
    static inline void Operator(PointerPtrType numerator_result_ptr,
        SegmentPtrType numerator_result_segment, 
        SegmentPtrType denominator_segment);
public:
    static inline void Operator(ConstSegmentPtrType numerator_segment,
        const std::uint8_t * denominator, const std::size_t & denominator_size,
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType numerator_segment,
        const std::uint8_t * denominator, const std::size_t & denominator_size,
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(PointerPtrType numerator_result_ptr,
        SegmentPtrType numerator_result_segment,
        const std::uint8_t * denominator, 
        const std::size_t & denominator_size);
public:
    template<std::size_t N>
    static inline void Operator(ConstSegmentPtrType numerator_segment,
        const std::uint8_t (&denominator)[N], PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    template<std::size_t N>
    static inline void Operator(SegmentPtrType numerator_segment,
        const std::uint8_t (&denominator)[N], PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    template<std::size_t N>
    static inline void Operator(PointerPtrType numerator_result_ptr,
        SegmentPtrType numerator_result_segment, 
        const std::uint8_t (&denominator)[N]);
public:
    static inline void Operator(ConstSegmentPtrType numerator_segment,
        const std::uint8_t & denominator, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType numerator_segment,
        const std::uint8_t & denominator, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(PointerPtrType numerator_result_ptr,
        SegmentPtrType numerator_result_segment, 
        const std::uint8_t & denominator);
private:
    inline Division() = delete;
public:
    inline ~Division() = delete;
};

inline void Division::Operator(ConstSegmentPtrType numerator_segment, 
    ConstSegmentPtrType denominator_segment, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    bytes::arithmetic::division::NewtonRaphson::Operator(numerator_segment,
        denominator_segment, result_ptr, result_segment, nullptr);
}

inline void Division::Operator(SegmentPtrType numerator_segment, 
    ConstSegmentPtrType denominator_segment, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Division::Operator(
        std::const_pointer_cast<ConstSegmentType>(numerator_segment),
        denominator_segment, result_ptr, result_segment);
}

inline void Division::Operator(ConstSegmentPtrType numerator_segment, 
    SegmentPtrType denominator_segment, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Division::Operator(numerator_segment,
        std::const_pointer_cast<ConstSegmentType>(denominator_segment),
        result_ptr, result_segment);
}

inline void Division::Operator(SegmentPtrType numerator_segment, 
    SegmentPtrType denominator_segment, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Division::Operator(
        std::const_pointer_cast<ConstSegmentType>(numerator_segment),
        std::const_pointer_cast<ConstSegmentType>(denominator_segment),
        result_ptr, result_segment);
}

inline void Division::Operator(PointerPtrType numerator_result_ptr,
    SegmentPtrType numerator_result_segment, 
    ConstSegmentPtrType denominator_segment)
{
    Division::Operator(numerator_result_segment, denominator_segment,
        numerator_result_ptr, numerator_result_segment);
}

inline void Division::Operator(PointerPtrType numerator_result_ptr,
    SegmentPtrType numerator_result_segment, 
    SegmentPtrType denominator_segment)
{
    Division::Operator(numerator_result_segment, 
        std::const_pointer_cast<ConstSegmentType>(denominator_segment),
        numerator_result_ptr, numerator_result_segment);
}

inline void Division::Operator(ConstSegmentPtrType numerator_segment,
    const std::uint8_t * denominator, const std::size_t & denominator_size,
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    bytes::arithmetic::division::NewtonRaphson::Operator(numerator_segment, 
        denominator, denominator_size, result_ptr, result_segment, nullptr);
}

inline void Division::Operator(SegmentPtrType numerator_segment,
    const std::uint8_t * denominator, const std::size_t & denominator_size,
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Division::Operator(
        std::const_pointer_cast<ConstSegmentType>(numerator_segment),
        denominator, denominator_size, result_ptr, result_segment);
}

inline void Division::Operator(PointerPtrType numerator_result_ptr,
    SegmentPtrType numerator_result_segment,
    const std::uint8_t * denominator, 
    const std::size_t & denominator_size)
{
    Division::Operator(numerator_result_segment, 
        denominator, denominator_size, 
        numerator_result_ptr, numerator_result_segment);
}

template<std::size_t N>
inline void Division::Operator(ConstSegmentPtrType numerator_segment,
    const std::uint8_t (&denominator)[N], PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Division::Operator(numerator_segment, denominator, N, result_ptr,
        result_segment);
}

template<std::size_t N>
inline void Division::Operator(SegmentPtrType numerator_segment,
    const std::uint8_t (&denominator)[N], PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Division::Operator(numerator_segment, denominator, N, result_ptr,
        result_segment);
}

template<std::size_t N>
inline void Division::Operator(PointerPtrType numerator_result_ptr,
    SegmentPtrType numerator_result_segment, 
    const std::uint8_t (&denominator)[N])
{
    Division::Operator(numerator_result_ptr, numerator_result_segment,
        denominator, N);
}

inline void Division::Operator(ConstSegmentPtrType numerator_segment,
    const std::uint8_t & denominator, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Division::Operator(numerator_segment, &denominator, 1,
        result_ptr, result_segment);
}

inline void Division::Operator(SegmentPtrType numerator_segment,
    const std::uint8_t & denominator, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Division::Operator(numerator_segment, &denominator, 1,
        result_ptr, result_segment);
}

inline void Division::Operator(PointerPtrType numerator_result_ptr,
    SegmentPtrType numerator_result_segment, 
    const std::uint8_t & denominator)
{
    Division::Operator(numerator_result_ptr, numerator_result_segment,
        &denominator, 1);
}

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_DIVISION_H_
