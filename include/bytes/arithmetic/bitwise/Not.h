#ifndef BYTES_ARITHMETIC_BITWISE_NOT_H_
#define BYTES_ARITHMETIC_BITWISE_NOT_H_

#include <cstddef>
#include <memory>

#include "../../ptr/Segment.h"

namespace bytes
{
namespace arithmetic
{
namespace bitwise
{

class Not
{
public:
    typedef bytes::ptr::Segment SegmentType;
    typedef std::shared_ptr<SegmentType> SegmentPtrType;
public:
    static inline void Operator(SegmentPtrType segment);
private:
    inline Not() = delete;
public:
    inline ~Not() = delete;
};

inline void Not::Operator(SegmentPtrType segment)
{
    for (std::size_t i = 0; i < segment->Size();)
    {
        segment->At(i) = ~segment->At(i);
        i = segment->Next(i);
    }
}

} //!bitwise

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_BITWISE_NOT_H_
