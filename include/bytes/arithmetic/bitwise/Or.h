#ifndef BYTES_ARITHMETIC_BITWISE_OR_H_
#define BYTES_ARITHMETIC_BITWISE_OR_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "../../Pointer.h"
#include "../../ptr/Segment.h"
#include "../../endian/Big.h"

namespace bytes
{
namespace arithmetic
{
namespace bitwise
{

class Or
{
public:
    typedef std::shared_ptr<bytes::Pointer> PointerPtrType;
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
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, ConstSegmentPtrType b_segment);
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, SegmentPtrType b_segment);
public:
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t * b, const std::size_t & b_size, 
        SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t * b, const std::size_t & b_size, 
        SegmentPtrType result_segment);
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment,
        const std::uint8_t * b, const std::size_t & b_size);
public:
    template<std::size_t N>
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t (&b)[N], SegmentPtrType result_segment);
    template<std::size_t N>
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t (&b)[N], SegmentPtrType result_segment);
    template<std::size_t N>
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, const std::uint8_t (&b)[N]);
public:
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t & b, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t & b, SegmentPtrType result_segment);
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, const std::uint8_t & b);
private:
    inline Or() = delete;
public:
    inline ~Or() = delete;
};

inline void Or::Operator(ConstSegmentPtrType a_segment,
    ConstSegmentPtrType b_segment, SegmentPtrType result_segment)
{
    std::size_t i_st = 0, j_st = 0, k_st = 0;
    for(; k_st < result_segment->Size(); ++i_st, ++j_st, ++k_st)
    {
        const std::size_t i = a_segment->Next(0, i_st),
            j = b_segment->Next(0, j_st),
            k = result_segment->Next(0, k_st);
        const bool a_is_end = a_segment->IsReverseEnd(i),
            b_is_end = b_segment->IsReverseEnd(j);
        if (a_is_end && b_is_end) 
            result_segment->ReverseAt(k) = std::uint8_t(0);
        else if (a_is_end) 
            result_segment->ReverseAt(k) = b_segment->ReverseAt(j);
        else if (b_is_end) 
            result_segment->ReverseAt(k) = a_segment->ReverseAt(i);
        else result_segment->ReverseAt(k) = a_segment->ReverseAt(i) | 
            b_segment->ReverseAt(j);
    }
}

inline void Or::Operator(SegmentPtrType a_segment,
    ConstSegmentPtrType b_segment, SegmentPtrType result_segment)
{
    Or::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        b_segment, result_segment);
}

inline void Or::Operator(ConstSegmentPtrType a_segment,
    SegmentPtrType b_segment, SegmentPtrType result_segment)
{
    Or::Operator(a_segment, 
        std::const_pointer_cast<ConstSegmentType>(b_segment), result_segment);
}

inline void Or::Operator(SegmentPtrType a_segment,
    SegmentPtrType b_segment, SegmentPtrType result_segment)
{
    Or::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        std::const_pointer_cast<ConstSegmentType>(b_segment), result_segment);
}
    
inline void Or::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, ConstSegmentPtrType b_segment)
{
    const std::size_t b_size = b_segment->Size();
    if (b_size > a_result_segment->Size())
        a_result_ptr->Reallocate(b_size, a_result_segment);
    Or::Operator(a_result_segment, b_segment, a_result_segment);
}

inline void Or::Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, SegmentPtrType b_segment)
{
    Or::Operator(a_result_ptr, a_result_segment, 
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline void Or::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    SegmentPtrType result_segment)
{
    std::size_t i_st = 0, j = 0, k_st = 0;
    for(; k_st < result_segment->Size(); ++i_st, ++j, ++k_st)
    {
        const std::size_t i = a_segment->Next(0, i_st),
            k = result_segment->Next(0, k_st);
        const bool a_is_end = a_segment->IsReverseEnd(i),
            b_is_end = j >= b_size;
        if (a_is_end && b_is_end) 
            result_segment->ReverseAt(k) = std::uint8_t(0);
        else if (a_is_end) result_segment->ReverseAt(k) = 
            b[bytes::endian::Big::Instance().ReverseAt(j, 0, b_size)];
        else if (b_is_end) 
            result_segment->ReverseAt(k) = a_segment->ReverseAt(i);
        else result_segment->ReverseAt(k) = a_segment->ReverseAt(i) | 
            b[bytes::endian::Big::Instance().ReverseAt(j, 0, b_size)];
    }
}

inline void Or::Operator(SegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    SegmentPtrType result_segment)
{
    Or::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment), 
        b, b_size, result_segment);
}

inline void Or::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment,
    const std::uint8_t * b, const std::size_t & b_size)
{
    if (b_size > a_result_segment->Size())
        a_result_ptr->Reallocate(b_size, a_result_segment);
    Or::Operator(a_result_segment, b, b_size, a_result_segment);
}

template<std::size_t N>
inline void Or::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t (&b)[N], SegmentPtrType result_segment)
{
    Or::Operator(a_segment, b, N, result_segment);
}

template<std::size_t N>
inline void Or::Operator(SegmentPtrType a_segment,
    const std::uint8_t (&b)[N], SegmentPtrType result_segment)
{
    Or::Operator(a_segment, b, N, result_segment);
}

template<std::size_t N>
inline void Or::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, const std::uint8_t (&b)[N])
{
    Or::Operator(a_result_ptr, a_result_segment, b, N);
}

inline void Or::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t & b, SegmentPtrType result_segment)
{
    Or::Operator(a_segment, &b, 1, result_segment);
}

inline void Or::Operator(SegmentPtrType a_segment,
    const std::uint8_t & b, SegmentPtrType result_segment)
{
    Or::Operator(a_segment, &b, 1, result_segment);
}

inline void Or::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, const std::uint8_t & b)
{
    Or::Operator(a_result_ptr, a_result_segment, &b, 1);
}

} //bitwise

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_BITWISE_OR_H_
