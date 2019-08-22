#ifndef BYTES_TRAIT_ELEMENT_DIRECT_H_
#define BYTES_TRAIT_ELEMENT_DIRECT_H_

#include <cstdint>
#include <utility>
#include <memory>

#include "../Element.h"

namespace bytes
{
namespace trait
{
namespace element
{

class Direct : public bytes::trait::Element
{
public:
    inline Direct();
    inline ~Direct();
public:
    inline Direct(const Direct & cpy);
    inline Direct(Direct && mov);
public:
    inline Direct & operator=(const Direct & cpy);
    inline Direct & operator=(Direct && mov);
public:
    inline std::shared_ptr<bytes::trait::Element> Copy() const;
    inline std::shared_ptr<bytes::trait::Element> Move();
public:
    inline bytes::trait::Element & Assign(const bytes::trait::Element & cpy);
    inline bytes::trait::Element & Assign(bytes::trait::Element && mov);
public:
    inline std::size_t OnAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline std::size_t OnReverseAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline std::size_t OnNextAt(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline std::size_t OnPreviousAt(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline std::size_t OnNextReverseAt(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline std::size_t OnPrevioursReverseAt(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline bool OnIsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline bool OnIsReverseEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline bool operator==(const bytes::trait::Element & b) const;
public:
    inline bool operator!=(const bytes::trait::Element & b) const;
};

inline Direct::Direct()
{}

inline Direct::~Direct()
{}

inline Direct::Direct(const Direct & cpy) :
    bytes::trait::Element(cpy)
{}

inline Direct::Direct(Direct && mov) :
    bytes::trait::Element(std::move(mov))
{}

inline Direct & Direct::operator=(const Direct & cpy)
{
    bytes::trait::Element::operator=(cpy);
    return *this;
}

inline Direct & Direct::operator=(Direct && mov)
{
    bytes::trait::Element::operator=(std::move(mov));
    return *this;
}

inline std::shared_ptr<bytes::trait::Element> Direct::Copy() const
{
    return std::make_shared<Direct>(*this);
}

inline std::shared_ptr<bytes::trait::Element> Direct::Move()
{
    return std::make_shared<Direct>(std::move(*this));
}

inline bytes::trait::Element & 
    Direct::Assign(const bytes::trait::Element & cpy)
{
    return *this;
}

inline bytes::trait::Element & Direct::Assign(bytes::trait::Element && mov)
{
    return *this;
}

inline std::size_t Direct::OnAt(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return i;
}

inline std::size_t Direct::OnReverseAt(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return i;
}

inline std::size_t Direct::OnNextAt(const std::size_t & i, 
    const std::size_t & st, const std::size_t & bg, 
    const std::size_t & ed) const
{
    return (st < ((ed - bg) - i)) ? OnAt(i + st, bg, ed) : 
        OnAt(ed, bg, ed);
}

inline std::size_t Direct::OnPreviousAt(const std::size_t & i, 
    const std::size_t & st, const std::size_t & bg, 
    const std::size_t & ed) const
{
    return (st <= i) ? OnAt(i - st, bg, ed) : 
        OnAt(bg - 1, bg, ed);
}

inline std::size_t Direct::OnNextReverseAt(const std::size_t & i, 
    const std::size_t & st, const std::size_t & bg, 
    const std::size_t & ed) const
{
    return (st < ((ed - bg) - i)) ? OnAt(i + st, bg, ed) : 
        OnAt(ed, bg, ed);
}

inline std::size_t Direct::OnPrevioursReverseAt(const std::size_t & i, 
    const std::size_t & st, const std::size_t & bg, 
    const std::size_t & ed) const
{
    return (st <= i) ? OnAt(i - st, bg, ed) : 
        OnAt(bg - 1, bg, ed);
}

inline bool Direct::OnIsEnd(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return i >= ed;
}

inline bool Direct::OnIsReverseEnd(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return i >= ed;
}

inline bool Direct::operator==(const Element & b) const
{
    auto * cb = dynamic_cast<const Direct *>(&b);
    return cb;
}

inline bool Direct::operator!=(const bytes::trait::Element & b) const
{
    return !(*this == b);
}

} //!element

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_ELEMENT_DIRECT_H_
