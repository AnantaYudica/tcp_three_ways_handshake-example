#ifndef BYTES_ARITHMETIC_DIVISION_NEWTONRAPHSON_H_
#define BYTES_ARITHMETIC_DIVISION_NEWTONRAPHSON_H_

#include <memory>
#include <cstddef>
#include <cstdint>

#include "../../Pointer.h"
#include "../../Trait.h"
#include "../../ptr/Segment.h"
#include "../../Assign.h"
#include "../../Comparison.h"
#include "../Addition.h"
#include "../Subtraction.h"
#include "../Multiplication.h"
#include "../bitwise/Shift.h"

namespace bytes
{
namespace arithmetic
{
namespace division
{

class NewtonRaphson
{
public:
    typedef std::shared_ptr<bytes::Pointer> PointerPtrType;
    typedef bytes::ptr::Segment SegmentType;
    typedef const SegmentType ConstSegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
    typedef std::shared_ptr<ConstSegmentType> ConstSegmentPtrType;
private:
    static inline void Equalize(SegmentPtrType a_segment,
        std::intmax_t & a_exponent, SegmentPtrType b_segment,
        std::intmax_t & b_exponent);
private:
    static inline void Round(PointerPtrType ptr, SegmentPtrType segment,
        std::intmax_t & exponent, const std::intmax_t & precision);
public:
    static inline void Operator(ConstSegmentPtrType numerator_segment, 
        ConstSegmentPtrType denominator_segment,
        PointerPtrType result_ptr, SegmentPtrType result_quotient_segment,
        SegmentPtrType result_remainder_segment);
    static inline void Operator(ConstSegmentPtrType numerator_segment, 
        const std::uint8_t * denominator_segment, 
        const std::size_t & denominator_size,
        PointerPtrType result_ptr, SegmentPtrType result_quotient_segment,
        SegmentPtrType result_remainder_segment);
private:
    NewtonRaphson() = delete;
public:
    ~NewtonRaphson() = delete;
};

inline void NewtonRaphson::Equalize(SegmentPtrType a_segment,
    std::intmax_t & a_exponent, SegmentPtrType b_segment,
    std::intmax_t & b_exponent)
{
    if (a_exponent > b_exponent)
    {
        bytes::arithmetic::bitwise::Shift::Operator(a_segment,
            a_exponent - b_exponent);
        a_exponent = b_exponent;
    }
    else if (a_exponent < b_exponent)
    {
        bytes::arithmetic::bitwise::Shift::Operator(b_segment,
            b_exponent - a_exponent);
        b_exponent = a_exponent;
    }
}

inline void NewtonRaphson::Round(PointerPtrType ptr, SegmentPtrType segment,
    std::intmax_t & exponent, const std::intmax_t & precision)
{
    auto round_trait = std::make_shared<bytes::Trait>(segment->Trait());
    auto round_ptr = std::make_shared<bytes::Pointer>(segment->Size() * 2);
    auto sum_segment = round_ptr->Share(0, segment->Size(), round_trait);
    auto mul_segment = round_ptr->Share(segment->Size(), segment->Size() * 2, 
        round_trait);

    const std::size_t max_exponent = precision * 3;
    if (exponent >= 0 || std::size_t(-exponent) <= max_exponent) return;
    bytes::Assign::Operator(round_ptr, sum_segment, segment);
    for (std::size_t i = 0; i < precision; ++i)
    {
        bytes::Assign::Operator(mul_segment, std::uint8_t(0));
        bytes::arithmetic::Multiplication::Operator(sum_segment, 
            std::uint8_t(10), round_ptr, mul_segment);
        bytes::Assign::Operator(round_ptr, sum_segment, mul_segment);
    }
    const std::size_t abs_exponent = std::size_t(-exponent), 
        prev_exponent = abs_exponent - 1;
    const std::size_t diff = abs_exponent - max_exponent;
    const std::size_t index = prev_exponent / 8;
    const std::size_t binary_shift = prev_exponent % 8;
    const std::uint8_t binary_index = 1 << binary_shift;
    const bool round = (sum_segment->At(index) & binary_index) == binary_index;
    bytes::arithmetic::bitwise::Shift::Operator(segment, -diff);
    exponent += diff;
    if (round) bytes::arithmetic::Addition::Operator(ptr, segment, 1);
}

inline void NewtonRaphson::Operator(ConstSegmentPtrType numerator_segment, 
    ConstSegmentPtrType denominator_segment,
    PointerPtrType result_ptr, SegmentPtrType result_quotient_segment,
    SegmentPtrType result_remainder_segment)
{
    const std::size_t base3_minsize = (numerator_segment->Size() * 8) / 3, 
        base3_bin_minsize = base3_minsize * 3,
        precision = (base3_minsize * 2) + 1,
        min_exponent = base3_bin_minsize + ((base3_bin_minsize % 2) == 0 ? 1 : 0),
        expand_size = numerator_segment->Size() * 4;
    auto div_ptr = std::make_shared<bytes::Pointer>(expand_size * 5);
    auto div_trait = std::make_shared<bytes::Trait>(numerator_segment->Trait());
    auto x0_segment = div_ptr->Share(0, expand_size, div_trait);
    auto x_segment = div_ptr->Share(expand_size, expand_size * 2, div_trait);
    auto xn_segment = div_ptr->Share(expand_size * 2, expand_size * 3, div_trait);
    auto bx_segment = div_ptr->Share(expand_size * 3, expand_size * 4, div_trait);
    auto c2_segment = div_ptr->Share(expand_size * 4, expand_size * 5, div_trait);
    std::intmax_t x0_exponent = -1, x_exponent = 0, xn_exponent = -(int(min_exponent)), 
        c2_exponent = 1, bx_exponent = 0;
    bytes::Assign::Operator(xn_segment,  std::uint8_t(0));
    xn_segment->At(0) = std::uint8_t(0x01);
    bytes::Assign::Operator(c2_segment,  std::uint8_t(0));
    c2_segment->At(0) = std::uint8_t(0x01);
    do
    {
        std::memcpy(x0_segment->Get(), xn_segment->Get(), expand_size);
        x0_exponent = xn_exponent;
        std::memcpy(x_segment->Get(), c2_segment->Get(), expand_size);
        x_exponent = c2_exponent;
        bytes::Assign::Operator(bx_segment, std::uint8_t(0));
        bytes::arithmetic::Multiplication::Operator(x0_segment, 
            denominator_segment, div_ptr, bx_segment);
        bx_exponent = x0_exponent;
        Equalize(x_segment, x_exponent, bx_segment, bx_exponent);
        bytes::arithmetic::Subtraction::Operator(x_segment, bx_segment);
        bytes::Assign::Operator(xn_segment, std::uint8_t(0));
        bytes::arithmetic::Multiplication::Operator(x0_segment, x_segment, 
            div_ptr, xn_segment);
        xn_exponent = x0_exponent + x_exponent;
        Round(div_ptr, xn_segment, xn_exponent, (precision * 2) + 1);
        Equalize(xn_segment, xn_exponent, x0_segment, x0_exponent);
    } while(bytes::Comparison::Operation(x0_segment, xn_segment) != 0);
    bytes::arithmetic::Multiplication::Operator(numerator_segment, x0_segment, 
        result_ptr, result_quotient_segment);
    bytes::arithmetic::bitwise::Shift::Operator(result_quotient_segment, 
        xn_exponent);
    if (result_remainder_segment)
    {
        bytes::arithmetic::Multiplication::Operator(result_quotient_segment,
            denominator_segment, result_ptr, result_remainder_segment);
        bytes::arithmetic::Subtraction::Operator(result_remainder_segment, 
            numerator_segment);
    }
}

inline void NewtonRaphson::Operator(ConstSegmentPtrType numerator_segment, 
    const std::uint8_t * denominator_segment, 
    const std::size_t & denominator_size,
    PointerPtrType result_ptr, SegmentPtrType result_quotient_segment,
    SegmentPtrType result_remainder_segment)
{
    const std::size_t base3_minsize = (numerator_segment->Size() * 8) / 3, 
        base3_bin_minsize = base3_minsize * 3,
        precision = (base3_minsize * 2) + 1,
        min_exponent = base3_bin_minsize + ((base3_bin_minsize % 2) == 0 ? 1 : 0),
        expand_size = numerator_segment->Size() * 4;
    auto div_ptr = std::make_shared<bytes::Pointer>(expand_size * 5);
    auto div_trait = std::make_shared<bytes::Trait>(numerator_segment->Trait());
    auto x0_segment = div_ptr->Share(0, expand_size, div_trait);
    auto x_segment = div_ptr->Share(expand_size, expand_size * 2, div_trait);
    auto xn_segment = div_ptr->Share(expand_size * 2, expand_size * 3, div_trait);
    auto bx_segment = div_ptr->Share(expand_size * 3, expand_size * 4, div_trait);
    auto c2_segment = div_ptr->Share(expand_size * 4, expand_size * 5, div_trait);
    std::intmax_t x0_exponent = -1, x_exponent = 0, xn_exponent = -(int(min_exponent)), 
        c2_exponent = 1, bx_exponent = 0;
    bytes::Assign::Operator(xn_segment,  std::uint8_t(0));
    xn_segment->At(0) = std::uint8_t(0x01);
    bytes::Assign::Operator(c2_segment,  std::uint8_t(0));
    c2_segment->At(0) = std::uint8_t(0x01);
    do
    {
        std::memcpy(x0_segment->Get(), xn_segment->Get(), expand_size);
        x0_exponent = xn_exponent;
        std::memcpy(x_segment->Get(), c2_segment->Get(), expand_size);
        x_exponent = c2_exponent;
        bytes::Assign::Operator(bx_segment, std::uint8_t(0));
        bytes::arithmetic::Multiplication::Operator(x0_segment, 
            denominator_segment, denominator_size, div_ptr, bx_segment);
        bx_exponent = x0_exponent;
        Equalize(x_segment, x_exponent, bx_segment, bx_exponent);
        bytes::arithmetic::Subtraction::Operator(x_segment, bx_segment);
        bytes::Assign::Operator(xn_segment, std::uint8_t(0));
        bytes::arithmetic::Multiplication::Operator(x0_segment, x_segment, 
            div_ptr, xn_segment);
        xn_exponent = x0_exponent + x_exponent;
        Round(div_ptr, xn_segment, xn_exponent, (precision * 2) + 1);
        Equalize(xn_segment, xn_exponent, x0_segment, x0_exponent);
    } while(bytes::Comparison::Operation(x0_segment, xn_segment) != 0);
    bytes::arithmetic::Multiplication::Operator(numerator_segment, x0_segment, 
        result_ptr, result_quotient_segment);
    bytes::arithmetic::bitwise::Shift::Operator(result_quotient_segment, 
        xn_exponent);
    if (result_remainder_segment)
    {
        bytes::arithmetic::Multiplication::Operator(result_quotient_segment,
            denominator_segment, denominator_size, result_ptr, 
            result_remainder_segment);
        bytes::arithmetic::Subtraction::Operator(result_remainder_segment, 
            numerator_segment);
    }
}

} //!division

} //arithmetic

} //!bytes


#endif //!BYTES_ARITHMETIC_DIVISION_NEWTONRAPHSON_H_
