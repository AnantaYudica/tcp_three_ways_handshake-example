#ifndef BYTES_TRAIT_FIXED_H_
#define BYTES_TRAIT_FIXED_H_

#include <functional>
#include <cstdint>
#include <limits>
#include <utility>
#include <memory>

#include "../Trait.h"

namespace bytes
{
namespace trait
{

class Fixed : public bytes::Trait
{
public:
    inline Fixed();
    inline Fixed(const bytes::Endian::CategoryEnum & e);
    inline ~Fixed();
public:
    inline Fixed(const Fixed & cpy);
    inline Fixed(Fixed && mov);
public:
    inline std::shared_ptr<bytes::Trait> Copy() const;
    inline std::shared_ptr<bytes::Trait> Move();
public:
    inline bytes::Trait & Assign(const bytes::Trait & cpy);
    inline bytes::Trait & Assign(bytes::Trait && mov);
public:
    inline std::size_t Size(const std::size_t & s) const;
public:
    inline std::size_t Resize(const std::size_t & cs,
        const std::size_t & ns) const;
public:
    inline std::size_t At(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
public:
    inline bool IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
};

inline Fixed::Fixed()
{}

inline Fixed::Fixed(const bytes::Endian::CategoryEnum & e) :
    bytes::Trait(e)
{}

inline Fixed::~Fixed()
{}

inline Fixed::Fixed(const Fixed & cpy) :
    bytes::Trait(cpy)
{}

inline Fixed::Fixed(Fixed && mov) :
    bytes::Trait(std::move(mov))
{}

inline std::shared_ptr<bytes::Trait> Fixed::Copy() const
{
    return std::make_shared<Fixed>(*this);
}

inline std::shared_ptr<bytes::Trait> Fixed::Move()
{
    return std::make_shared<Fixed>(std::move(*this));
}

inline bytes::Trait & Fixed::Assign(const bytes::Trait & cpy)
{
    return *this;
}

inline bytes::Trait & Fixed::Assign(bytes::Trait && mov)
{
    return *this;
}

inline std::size_t Fixed::Size(const std::size_t & s) const
{
    return s;
}

inline std::size_t Fixed::Resize(const std::size_t & cs,
    const std::size_t & ns) const
{
    return cs;
}

inline std::size_t Fixed::At(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return i;
}

inline bool Fixed::IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const
{
    return i >= ed;
}

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_FIXED_H_
