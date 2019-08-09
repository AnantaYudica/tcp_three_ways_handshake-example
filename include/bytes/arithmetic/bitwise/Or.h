#ifndef BYTES_ARITHMETIC_BITWISE_OR_H_
#define BYTES_ARITHMETIC_BITWISE_OR_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "../../Pointer.h"
#include "../../ptr/Segment.h"

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
private:
    inline Or() = delete;
public:
    inline ~Or() = delete;
};

inline void Or::Operator(ConstSegmentPtrType a_segment,
    ConstSegmentPtrType b_segment, SegmentPtrType result_segment)
{
    for(std::size_t i = 0; i < result_segment->Size(); ++i)
    {
        const bool a_is_end = a_segment->IsEnd(i),
            b_is_end = b_segment->IsEnd(i);
        if (a_is_end && b_is_end) result_segment->At(i) = std::uint8_t(0);
        else if (a_is_end) result_segment->At(i) = b_segment->At(i);
        else if (b_is_end) result_segment->At(i) = a_segment->At(i);
        else result_segment->At(i) = a_segment->At(i) | b_segment->At(i);
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

} //bitwise

} //!arithmetic

} //!bytes

#endif //!BYTES_ARITHMETIC_BITWISE_OR_H_
