#ifndef BYTES_TRAIT_ELEMENT_CIRCULAR_H_
#define BYTES_TRAIT_ELEMENT_CIRCULAR_H_

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

class Circular : public bytes::trait::Element
{
public:
    inline Circular();
    inline ~Circular();
public:
    inline Circular(const Circular & cpy);
    inline Circular(Circular && mov);
public:
    inline Circular & operator=(const Circular & cpy);
    inline Circular & operator=(Circular && mov);
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

inline Circular::Circular()
{}

inline Circular::~Circular()
{}

inline Circular::Circular(const Circular & cpy) :
    bytes::trait::Element(cpy)
{}

inline Circular::Circular(Circular && mov) :
    bytes::trait::Element(std::move(mov))
{}

inline Circular & Circular::operator=(const Circular & cpy)
{
    bytes::trait::Element::operator=(cpy);
    return *this;
}

inline Circular & Circular::operator=(Circular && mov)
{
    bytes::trait::Element::operator=(std::move(mov));
    return *this;
}

inline std::shared_ptr<bytes::trait::Element> Circular::Copy() const
{
    return std::make_shared<Circular>(*this);
}

inline std::shared_ptr<bytes::trait::Element> Circular::Move()
{
    return std::make_shared<Circular>(std::move(*this));
}

inline bytes::trait::Element & 
    Circular::Assign(const bytes::trait::Element & cpy)
{
    return *this;
}

inline bytes::trait::Element & 
    Circular::Assign(bytes::trait::Element && mov)
{
    return *this;
}

inline std::size_t Circular::OnAt(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return (i % (ed - bg));
}

inline bool Circular::OnIsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const
{
    return false;
}

inline bool Circular::OnIsReverseEnd(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return false;
}

inline bool Circular::operator==(const bytes::trait::Element & b) const
{
    auto * cb = dynamic_cast<const Circular *>(&b);
    return cb;
}

inline bool Circular::operator!=(const bytes::trait::Element & b) const
{
    return !(*this == b);
}

} //!element

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_ELEMENT_CIRCULAR_H_
