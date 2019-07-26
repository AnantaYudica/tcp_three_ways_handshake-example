#ifndef BYTES_TRAIT_FIXED_CIRCULAR_H_
#define BYTES_TRAIT_FIXED_CIRCULAR_H_

#include <cstdint>
#include <utility>
#include <memory>

#include "../Fixed.h"
#include "../../Trait.h"

namespace bytes
{
namespace trait
{
namespace fixed
{

class Circular : public bytes::trait::Fixed
{
public:
    inline Circular();
    inline Circular(const bytes::Endian::CategoryEnum & e);
    inline ~Circular();
public:
    inline Circular(const Circular & cpy);
    inline Circular(Circular && mov);
public:
    virtual inline std::shared_ptr<bytes::Trait> Copy() const;
    virtual inline std::shared_ptr<bytes::Trait> Move();
public:
    virtual inline bytes::Trait & Assign(const bytes::Trait & cpy);
    virtual inline bytes::Trait & Assign(bytes::Trait && mov);
public:
    virtual inline std::size_t Size(const std::size_t & s) const;
public:
    virtual inline std::size_t Resize(const std::size_t & cs,
        const std::size_t & ns) const;
public:
    virtual inline std::size_t At(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    virtual inline bool IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
};

inline Circular::Circular()
{}

inline Circular::Circular(const bytes::Endian::CategoryEnum & e) :
    bytes::trait::Fixed(e)
{}

inline Circular::~Circular()
{}

inline Circular::Circular(const Circular & cpy) :
    bytes::trait::Fixed(cpy)
{}

inline Circular::Circular(Circular && mov) :
    bytes::trait::Fixed(std::move(mov))
{}

inline std::shared_ptr<bytes::Trait> Circular::Copy() const
{
    return std::make_shared<Circular>(*this);
}

inline std::shared_ptr<bytes::Trait> Circular::Move()
{
    return std::make_shared<Circular>(std::move(*this));
}

inline bytes::Trait & Circular::Assign(const bytes::Trait & cpy)
{
    return *this;
}

inline bytes::Trait & Circular::Assign(bytes::Trait && mov)
{
    return *this;
}

inline std::size_t Circular::At(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return (i % (ed - bg));
}

inline bool Circular::IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const
{
    return false;
}

} //!fixed

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_FIXED_CIRCULAR_H_
