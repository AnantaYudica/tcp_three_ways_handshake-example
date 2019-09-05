#ifndef BYTES_REVERSEELEMENT_H_
#define BYTES_REVERSEELEMENT_H_

#include <cstdint>
#include <cstddef>
#include <memory>

#include "Element.h"
#include "Trait.h"
#include "ptr/Object.h"

namespace bytes
{

class ReverseElement : public bytes::Element
{
public:
    inline ReverseElement();
    inline ReverseElement(const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed, const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
    inline ReverseElement(const std::size_t & i, const std::size_t & bg, 
        const std::size_t & ed, const std::uint8_t & off, 
        const std::shared_ptr<bytes::ptr::Object> & o,
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline ~ReverseElement();
public:
    inline ReverseElement(const ReverseElement & cpy);
    inline ReverseElement(ReverseElement && mov);
public:
    inline ReverseElement & operator=(const ReverseElement & cpy);
    inline ReverseElement & operator=(ReverseElement && mov);
    inline ReverseElement & operator=(const std::uint8_t & v);
public:
    inline std::size_t GetAbsoluteIndex() const;
public:
    inline operator std::uint8_t() const;
};

inline ReverseElement::ReverseElement() :
    bytes::Element()
{}

inline ReverseElement::ReverseElement(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed, 
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::Element(i, bg, ed, o, t)
{}
inline ReverseElement::ReverseElement(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed, const std::uint8_t & off, 
    const std::shared_ptr<bytes::ptr::Object> & o,
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::Element(i, bg, ed, off, o, t)
{}

inline ReverseElement::~ReverseElement()
{}

inline ReverseElement::ReverseElement(const ReverseElement & cpy) :
    bytes::Element(cpy)
{}

inline ReverseElement::ReverseElement(ReverseElement && mov) :
    bytes::Element(std::move(mov))
{}

inline ReverseElement & ReverseElement::operator=(const ReverseElement & cpy)
{
    return (*this = static_cast<std::uint8_t>(cpy));
}

inline ReverseElement & ReverseElement::operator=(ReverseElement && mov)
{
    
    return (*this = static_cast<std::uint8_t>(mov));
}

inline ReverseElement & ReverseElement::operator=(const std::uint8_t & v)
{
    const std::size_t index = GetIndex(), 
        begin = GetBeginIndex(), end = GetEndIndex();
    const auto offset = GetOffset();
    auto trait = GetTrait();
    auto object = GetObject();
    if (offset == 0)
        object->At(trait->ReverseAt(index, begin, end)) = trait->Set(v);
    else
        trait->ValueAt(object->At(trait->ReverseAt(index, begin, end)), 
            object->At(trait->ReverseAt(trait->Next(index, 1, begin, end), 
            begin, end)), trait->Set(v), offset);
    return *this;
}

inline std::size_t ReverseElement::GetAbsoluteIndex() const
{
    return GetTrait()->ReverseAt(GetIndex(), GetBeginIndex(),
        GetEndIndex());
}

inline ReverseElement::operator std::uint8_t() const
{
    const std::size_t index = GetIndex(), 
        begin = GetBeginIndex(), end = GetEndIndex();
    const auto offset = GetOffset();
    const auto & trait = GetTrait();
    const auto & object = GetObject();
    if (offset == 0)
        return trait->Get(object->At(trait->ReverseAt(index, begin, end)));
    return trait->ValueAt(object->At(trait->At(index, begin, end)), 
        object->At(trait->At(trait->Next(index, 1, begin, end), 
        begin, end)), offset, 8);
}

} //!bytes

inline std::uint8_t operator|(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b | a;
}

inline std::uint8_t operator&(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b & a;    
}

inline std::uint8_t operator^(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b ^ a;
}

inline std::uint8_t operator+(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b + a;
}

inline std::uint8_t operator-(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return a - static_cast<std::uint8_t>(b);
}

inline std::uint8_t operator*(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b * a;
}

inline std::uint8_t operator/(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return a / static_cast<std::uint8_t>(b);
}

inline std::uint8_t operator%(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return a % static_cast<std::uint8_t>(b);
}

inline bool operator==(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b == a;
}

inline bool operator!=(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b != a;
}

inline bool operator<(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b > a;
}

inline bool operator<=(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b >= a;
}

inline bool operator>(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b < a;
}

inline bool operator>=(const std::uint8_t & a, 
    const bytes::ReverseElement & b)
{
    return b <= a;
}

#endif //!BYTES_REVERSEELEMENT_H_
