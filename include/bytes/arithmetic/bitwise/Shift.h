#ifndef BYTES_ARITHMETIC_BITWISE_SHIFT_H_
#define BYTES_ARITHMETIC_BITWISE_SHIFT_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "../../ptr/Segment.h"

namespace bytes
{
namespace arithmetic
{
namespace bitwise
{

class Shift
{
public:
    typedef bytes::ptr::Segment SegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
public:
    static inline void Operator(SegmentPtrType a_segment, 
        const std::intmax_t & value);
private:
    inline Shift() = delete;
public:
    inline ~Shift() = delete;
};

inline void Shift::Operator(SegmentPtrType a_segment, 
    const std::intmax_t & value)
{
    const std::size_t size = a_segment->Size();
    std::int8_t binary_index = std::int8_t(value % std::intmax_t(8));
    std::intmax_t index = std::intmax_t(value / std::intmax_t(8));
    if (index > std::intmax_t(0) || binary_index > std::uint8_t(0))
    {
        std::size_t i_st = 0, j_st = index,
            j = a_segment->Next(0, j_st);
        bool j_is_end = a_segment->IsEnd(j);
        for (; i_st < size; ++i_st, ++j_st)
        {
            const std::size_t i = a_segment->Next(0, i_st);
            if (binary_index == std::uint8_t(0))
                a_segment->At(i) = (j_is_end ? 
                    std::uint8_t(0) : a_segment->At(j));
            else
            {
                const std::size_t next_j = a_segment->Next(0, j_st + 1);
                const bool next_j_is_end = j_is_end || 
                    a_segment->IsEnd(next_j);
                a_segment->At(i) = ((j_is_end ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->At(j) << 
                    std::uint8_t(binary_index))) | 
                    ((next_j_is_end) ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->At(next_j) >> 
                    std::uint8_t(8 - binary_index))));
            }
            if (!j_is_end)
            {
                j = a_segment->Next(0, j_st + 1);
                j_is_end = a_segment->IsEnd(j);
            }
        }
    }
    else if (index < std::intmax_t(0) || binary_index < std::uint8_t(0))
    {
        std::size_t i_st = 0, j_st = std::size_t(-index),
            j = a_segment->Next(0, j_st);
        bool j_is_end = a_segment->IsReverseEnd(j);
        for (;i_st < size; ++i_st, ++j_st)
        {
            const std::size_t i = a_segment->Next(0, i_st);
            if (binary_index == std::uint8_t(0))
                a_segment->ReverseAt(i) = (j_is_end ? std::uint8_t(0) : 
                    a_segment->ReverseAt(j));
            else
            {
                const std::size_t next_j = a_segment->Next(0, j_st + 1);
                const bool next_j_is_end = j_is_end || 
                    a_segment->IsReverseEnd(next_j);
                a_segment->ReverseAt(i) = ((j_is_end ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->ReverseAt(j) >> 
                    std::uint8_t(-binary_index))) | 
                    (next_j_is_end ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->ReverseAt(next_j) << 
                    std::uint8_t(8 + binary_index))));
            }
            if (!j_is_end)
            {
                j = a_segment->Next(0, j_st + 1);
                j_is_end = a_segment->IsReverseEnd(j);
            }
        }
    }
}

} //!bitwise

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_BITWISE_SHIFT_H_
