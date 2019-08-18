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
    std::uint8_t c = std::uint8_t(0);
    std::int8_t binary_index = std::int8_t(value % std::intmax_t(8));
    std::intmax_t index = std::intmax_t(value / std::intmax_t(8));
    if (index > std::intmax_t(0) || binary_index > std::uint8_t(0))
    {
        for (std::size_t i = size - 1, j = size - (index + 1); i < size;)
        {
            if (binary_index == std::uint8_t(0))
                a_segment->At(i--) = (j >= size ? std::uint8_t(0) : 
                    a_segment->At(j--));
            else
                a_segment->At(i--) = (((j >= size) ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->At(j--) << 
                    std::uint8_t(binary_index))) | 
                    ((j >= size) ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->At(j) >> 
                    std::uint8_t(8 - binary_index))));
        }
    }
    else if (index < std::intmax_t(0) || binary_index < std::uint8_t(0))
    {
        for (std::size_t i = 0, j = -index; i < size;)
        {
            if (binary_index == std::uint8_t(0))
                a_segment->At(i++) = (j >= size ? std::uint8_t(0) : 
                    a_segment->At(j++));
            else
                a_segment->At(i++) = (((j >= size) ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->At(j++) >> 
                    std::uint8_t(-binary_index))) | 
                    ((j >= size) ? std::uint8_t(0) : 
                    std::uint8_t(a_segment->At(j) << 
                    std::uint8_t(8 + binary_index))));
        }
    }
}

} //!bitwise

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_BITWISE_SHIFT_H_
