#ifndef BYTES_ARITHMETIC_ADDITION_H_
#define BYTES_ARITHMETIC_ADDITION_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "../sys/Endian.h"
#include "../Pointer.h"
#include "../ptr/Segment.h"
#include "../endian/Big.h"

namespace bytes
{
namespace arithmetic
{

class Addition
{
public:
    typedef std::shared_ptr<bytes::Pointer> PointerPtrType;
    typedef bytes::ptr::Segment SegmentType;
    typedef const SegmentType ConstSegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
    typedef std::shared_ptr<ConstSegmentType> ConstSegmentPtrType;
public:
    static inline void Operator(ConstSegmentPtrType a_segment, 
        ConstSegmentPtrType b_segment, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment, 
        ConstSegmentPtrType b_segment, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(ConstSegmentPtrType a_segment, 
        SegmentPtrType b_segment, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment, 
        SegmentPtrType b_segment, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, ConstSegmentPtrType b_segment);
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, SegmentPtrType b_segment);
public:
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t * b, const std::size_t & b_size, 
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t * b, const std::size_t & b_size, 
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment,
        const std::uint8_t * b, const std::size_t & b_size);
public:
    template<std::size_t N>
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t (&b)[N], PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    template<std::size_t N>
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t (&b)[N], PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    template<std::size_t N>
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, const std::uint8_t (&b)[N]);
public:
    static inline void Operator(ConstSegmentPtrType a_segment,
        const std::uint8_t & b, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment,
        const std::uint8_t & b, PointerPtrType result_ptr, 
        SegmentPtrType result_segment);
    static inline void Operator(PointerPtrType a_result_ptr,
        SegmentPtrType a_result_segment, const std::uint8_t & b);
private:
    inline Addition() = delete;
public:
    inline ~Addition() = delete;
};

inline void Addition::Operator(ConstSegmentPtrType a_segment, 
    ConstSegmentPtrType b_segment, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    const auto & endian = bytes::sys::Endian();
    std::uint8_t carry = std::uint8_t(0);
    std::size_t i_st = 0, j_st = 0, k_st = 0;
    for (; k_st < result_segment->Size(); ++i_st, ++j_st, ++k_st)
    {
        const std::size_t i = a_segment->Next(0, i_st),
            j = b_segment->Next(0, j_st),
            k = result_segment->Next(0, k_st);
        std::uint16_t val = carry;
        if (!a_segment->IsReverseEnd(i))
            val += a_segment->ReverseAt(i);
        if (!b_segment->IsReverseEnd(j))
            val += b_segment->ReverseAt(j);
        std::uint8_t * pval = reinterpret_cast<std::uint8_t *>(&val);
        carry = pval[endian.At(0, 0, 2)];
        result_segment->ReverseAt(k) = pval[endian.At(1, 0, 2)];
    }
    if (carry != std::uint8_t(0))
    {
        if (result_ptr->Reallocate(result_segment->Size() + 1, result_segment))
            result_segment->At(0) = carry;
    }
}

inline void Addition::Operator(SegmentPtrType a_segment, 
    ConstSegmentPtrType b_segment, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Addition::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        b_segment, result_ptr, result_segment);
}

inline void Addition::Operator(ConstSegmentPtrType a_segment, 
    SegmentPtrType b_segment, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Addition::Operator(a_segment, 
        std::const_pointer_cast<ConstSegmentType>(b_segment), result_ptr, 
        result_segment);
}

inline void Addition::Operator(SegmentPtrType a_segment, 
    SegmentPtrType b_segment, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Addition::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        std::const_pointer_cast<ConstSegmentType>(b_segment), 
        result_ptr, result_segment);
}

inline void Addition::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, ConstSegmentPtrType b_segment)
{
    Addition::Operator(a_result_segment, b_segment, a_result_ptr,
        a_result_segment);
}

inline void Addition::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, SegmentPtrType b_segment)
{
    Addition::Operator(a_result_ptr, a_result_segment,
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}

inline void Addition::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    const auto & endian = bytes::sys::Endian();
    std::uint8_t carry = std::uint8_t(0);
    std::size_t i_st = 0, j = 0, k_st = 0;
    for (; k_st < result_segment->Size(); ++i_st, ++j, ++k_st)
    {
        const std::size_t i = a_segment->Next(0, i_st),
            k = result_segment->Next(0, k_st);
        std::uint16_t val = carry;
        if (!a_segment->IsReverseEnd(i))
            val += a_segment->ReverseAt(i);
        if (i < b_size)
            val += b[bytes::endian::Big::Instance().ReverseAt(j, 0, b_size)];
        std::uint8_t * pval = reinterpret_cast<std::uint8_t *>(&val);
        carry = pval[endian.At(0, 0, 2)];
        result_segment->ReverseAt(k) = pval[endian.At(1, 0, 2)];
    }
    if (carry != std::uint8_t(0))
    {
        if (result_ptr->Reallocate(result_segment->Size() + 1, result_segment))
            result_segment->At(0) = carry;
    }
}

inline void Addition::Operator(SegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Addition::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        b, b_size, result_ptr, result_segment);
}

inline void Addition::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment,
    const std::uint8_t * b, const std::size_t & b_size)
{
    Addition::Operator(a_result_segment, b, b_size, 
        a_result_ptr, a_result_segment);
}

template<std::size_t N>
inline void Addition::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t (&b)[N], PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Addition::Operator(a_segment, b, N, result_ptr, result_segment);
}

template<std::size_t N>
inline void Addition::Operator(SegmentPtrType a_segment,
    const std::uint8_t (&b)[N], PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Addition::Operator(std::const_pointer_cast<ConstSegmentType>(a_segment),
        b, N, result_ptr, result_segment);
}

template<std::size_t N>
inline void Addition::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, const std::uint8_t (&b)[N])
{
    Addition::Operator(a_result_segment, b, N, 
        a_result_ptr, a_result_segment);
}

inline void Addition::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t & b, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Addition::Operator(a_segment, &b, 1, result_ptr, result_segment);
}

inline void Addition::Operator(SegmentPtrType a_segment,
    const std::uint8_t & b, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Addition::Operator(a_segment, &b, 1, result_ptr, result_segment);
}

inline void Addition::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, const std::uint8_t & b)
{
    Addition::Operator(a_result_segment, &b, 1, 
        a_result_ptr, a_result_segment);
}

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_ADDITION_H_
