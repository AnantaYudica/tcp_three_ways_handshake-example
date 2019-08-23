#ifndef BYTES_ARITHMETIC_MULTIPLICATION_H_
#define BYTES_ARITHMETIC_MULTIPLICATION_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "../sys/Endian.h"
#include "../ptr/Segment.h"
#include "../Pointer.h"
#include "../Assign.h"
#include "Addition.h"
#include "bitwise/Shift.h"
#include "../endian/Big.h"

namespace bytes
{
namespace arithmetic
{

class Multiplication
{
public:
    typedef std::shared_ptr<bytes::Pointer> PointerPtrType;
    typedef bytes::ptr::Segment SegmentType;
    typedef const SegmentType ConstSegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
    typedef std::shared_ptr<ConstSegmentType> ConstSegmentPtrType;
public:
    static inline void Operator(ConstSegmentPtrType a_segment, 
        ConstSegmentPtrType b_segment,
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment, 
        ConstSegmentPtrType b_segment,
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(ConstSegmentPtrType a_segment, 
        SegmentPtrType b_segment,
        PointerPtrType result_ptr, SegmentPtrType result_segment);
    static inline void Operator(SegmentPtrType a_segment, 
        SegmentPtrType b_segment,
        PointerPtrType result_ptr, SegmentPtrType result_segment);
public:
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
    inline Multiplication() = delete;
public:
    inline ~Multiplication() = delete;
};

inline void Multiplication::Operator(ConstSegmentPtrType a_segment, 
    ConstSegmentPtrType b_segment,
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    const auto & endian = bytes::sys::Endian();
    const auto a_size = a_segment->Size();
    const auto b_size = b_segment->Size();
    const auto result_size = result_segment->Size();
    bytes::Pointer mul_ptr{result_size};
    auto mul_trait = 
        std::make_shared<bytes::Trait>(result_segment->GetTrait());
    auto mul_segment = mul_ptr.Share(0, result_size, mul_trait);
    std::size_t i = 0, j = 0, k = 0;
    for (std::size_t l = 0; l < b_size; ++l)
    {
        bytes::Assign::Operator(mul_segment, std::uint8_t(0));
        std::uint16_t carry = 0;
        std::uint8_t b_segment_reverse_at = b_segment->ReverseAt(j);
        std::uint8_t * carry_ptr = reinterpret_cast<std::uint8_t *>(&carry);
        i = 0; k = 0;
        for (std::size_t m = 0; m < a_size; ++m)
        {
            if (b_segment_reverse_at == std::uint8_t(0) && carry == 0) break;
            std::uint16_t val = a_segment->ReverseAt(i);
            val *= b_segment_reverse_at;
            std::uint8_t * pval = reinterpret_cast<std::uint8_t *>(&val);
            carry += pval[endian.At(1, 0, 2)];
            mul_segment->ReverseAt(k) = carry_ptr[endian.At(1, 0, 2)];
            carry >>= sizeof(std::uint8_t) * 8;
            carry += pval[endian.At(0, 0, 2)];
            i = a_segment->Next(i);
            k = mul_segment->Next(k);
        }
        const std::size_t resize = (carry_ptr[endian.At(0, 0, 2)] != 0 ? 2 :
            (carry_ptr[endian.At(1, 0, 2)] != 0 ? 1 : 0));
        const bool has_carry = resize > 0, 
            is_resize_mul = mul_segment->Size() < (a_size + resize);
        if (has_carry && is_resize_mul &&
            mul_ptr.Reallocate(mul_segment->Size() + resize, mul_segment))
        {
            mul_segment->At(mul_segment->Next(0)) += 
                carry_ptr[endian.At(1, 0, 2)];
            mul_segment->At(0) += carry_ptr[endian.At(0, 0, 2)];
        }
        else if (has_carry && !is_resize_mul)
        {
            mul_segment->ReverseAt(k) += carry_ptr[endian.At(1, 0, 2)];
            mul_segment->ReverseAt(mul_segment->Next(k)) += 
                carry_ptr[endian.At(0, 0, 2)];
        }
        bytes::arithmetic::bitwise::Shift::Operator(mul_segment, 8 * l);
        bytes::arithmetic::Addition::Operator(result_ptr, result_segment, 
            mul_segment);
        j = b_segment->Next(j);
    }
}

inline void Multiplication::Operator(SegmentPtrType a_segment, 
    ConstSegmentPtrType b_segment,
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Multiplication::Operator(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        b_segment, result_ptr, result_segment);
}

inline void Multiplication::Operator(ConstSegmentPtrType a_segment, 
    SegmentPtrType b_segment,
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Multiplication::Operator(a_segment,
        std::const_pointer_cast<ConstSegmentType>(b_segment),
        result_ptr, result_segment);
}

inline void Multiplication::Operator(SegmentPtrType a_segment, 
    SegmentPtrType b_segment,
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Multiplication::Operator(
        std::const_pointer_cast<ConstSegmentType>(a_segment),
        std::const_pointer_cast<ConstSegmentType>(b_segment), 
        result_ptr, result_segment);
}

inline void Multiplication::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, ConstSegmentPtrType b_segment)
{
    const std::size_t expand_size = a_result_segment->Size() + 
        b_segment->Size();
    auto result_ptr = std::make_shared<bytes::Pointer>(expand_size);
    auto result_trait = 
        std::make_shared<bytes::Trait>(a_result_segment->GetTrait());
    auto result_segment = result_ptr->Share(0, expand_size, result_trait);
    bytes::Assign::Operator(result_segment, std::uint8_t(0));
    Multiplication::Operator(a_result_segment, b_segment, result_ptr, 
        result_segment);
    std::size_t reduce_size = 0;
    for (std::size_t i = result_segment->Size() - 1; 
        i < result_segment->Size(); --i, ++reduce_size)
    {
        if (result_segment->At(i) != std::uint8_t(0)) break;
    }
    bytes::Assign::Operator(result_ptr, a_result_segment, 0, 
        result_segment, 0, result_segment->Size() - reduce_size);
}

inline void Multiplication::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, SegmentPtrType b_segment)
{
    Multiplication::Operator(a_result_ptr, a_result_segment,
        std::const_pointer_cast<ConstSegmentType>(b_segment));
}


inline void Multiplication::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    const auto & endian = bytes::sys::Endian();
    const auto a_size = a_segment->Size();
    const auto result_size = result_segment->Size();
    bytes::Pointer mul_ptr{result_size};
    auto mul_trait = 
        std::make_shared<bytes::Trait>(result_segment->GetTrait());
    auto mul_segment = mul_ptr.Share(0, result_size, mul_trait);
    std::size_t i = 0, j = 0, k = 0;
    for (std::size_t l = 0; l < b_size; ++l, ++j)
    {
        bytes::Assign::Operator(mul_segment, std::uint8_t(0));
        std::uint16_t carry = 0;
        std::uint8_t b_reverse_at = 
            b[bytes::endian::Big::Instance().ReverseAt(j, 0, b_size)];
        std::uint8_t * carry_ptr = reinterpret_cast<std::uint8_t *>(&carry);
        i = 0; k = 0;
        for (std::size_t m = 0; m < a_size; ++m)
        {
            if (b_reverse_at == 0 && carry == 0) break;
            std::uint16_t val = a_segment->ReverseAt(i);
            val *= b_reverse_at;
            std::uint8_t * pval = reinterpret_cast<std::uint8_t *>(&val);
            carry += pval[endian.At(1, 0, 2)];
            mul_segment->ReverseAt(k) = carry_ptr[endian.At(1, 0, 2)];
            carry >>= sizeof(std::uint8_t) * 8;
            carry += pval[endian.At(0, 0, 2)];
            i = a_segment->Next(i);
            k = mul_segment->Next(k);
        }
        const std::size_t resize = (carry_ptr[endian.At(0, 0, 2)] != 0 ? 2 :
            (carry_ptr[endian.At(1, 0, 2)] != 0 ? 1 : 0));
        const bool has_carry = resize > 0, 
            is_resize_mul = mul_segment->Size() < (a_size + resize);
        if (has_carry && is_resize_mul &&
            mul_ptr.Reallocate(mul_segment->Size() + resize, mul_segment))
        {
            mul_segment->At(mul_segment->Next(0)) += 
                carry_ptr[endian.At(1, 0, 2)];
            mul_segment->At(0) += carry_ptr[endian.At(0, 0, 2)];
        }
        else if (has_carry && !is_resize_mul)
        {
            mul_segment->ReverseAt(k) += carry_ptr[endian.At(1, 0, 2)];
            mul_segment->ReverseAt(mul_segment->Next(k)) += 
                carry_ptr[endian.At(0, 0, 2)];
        }
        bytes::arithmetic::bitwise::Shift::Operator(mul_segment, 8 * l);
        bytes::arithmetic::Addition::Operator(result_ptr, result_segment, 
            mul_segment);
    }
}

inline void Multiplication::Operator(SegmentPtrType a_segment,
    const std::uint8_t * b, const std::size_t & b_size, 
    PointerPtrType result_ptr, SegmentPtrType result_segment)
{
    Multiplication::Operator(
        std::const_pointer_cast<ConstSegmentType>(a_segment), b, b_size,
        result_ptr, result_segment);
}

inline void Multiplication::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment,
    const std::uint8_t * b, const std::size_t & b_size)
{
    const std::size_t expand_size = a_result_segment->Size() + b_size;
    auto result_ptr = std::make_shared<bytes::Pointer>(expand_size);
    auto result_trait = 
        std::make_shared<bytes::Trait>(a_result_segment->GetTrait());
    auto result_segment = result_ptr->Share(0, expand_size, result_trait);
    bytes::Assign::Operator(result_segment, std::uint8_t(0));
    Multiplication::Operator(a_result_segment, b, b_size, result_ptr, 
        result_segment);
    std::size_t reduce_size = 0;
    for (std::size_t i = result_segment->Size() - 1; 
        i < result_segment->Size(); --i, ++reduce_size)
    {
        if (result_segment->At(i) != std::uint8_t(0)) break;
    }
    bytes::Assign::Operator(result_ptr, a_result_segment, 0, 
        result_segment, 0, result_segment->Size() - reduce_size);
}

template<std::size_t N>
inline void Multiplication::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t (&b)[N], PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Multiplication::Operator(a_segment, b, N, result_ptr, result_segment);
}

template<std::size_t N>
inline void Multiplication::Operator(SegmentPtrType a_segment,
    const std::uint8_t (&b)[N], PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Multiplication::Operator(a_segment, b, N, result_ptr, result_segment);
}

template<std::size_t N>
inline void Multiplication::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, const std::uint8_t (&b)[N])
{
    Multiplication::Operator(a_result_ptr, a_result_segment, b, N);
}

inline void Multiplication::Operator(ConstSegmentPtrType a_segment,
    const std::uint8_t & b, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Multiplication::Operator(a_segment, &b, 1, result_ptr, result_segment);
}

inline void Multiplication::Operator(SegmentPtrType a_segment,
    const std::uint8_t & b, PointerPtrType result_ptr, 
    SegmentPtrType result_segment)
{
    Multiplication::Operator(a_segment, &b, 1, result_ptr, result_segment);
}

inline void Multiplication::Operator(PointerPtrType a_result_ptr,
    SegmentPtrType a_result_segment, const std::uint8_t & b)
{
    
    Multiplication::Operator(a_result_ptr, a_result_segment, &b, 1);
}

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_MULTIPLICATION_H_
