#ifndef BYTES_TRAIT_FIXED_H_
#define BYTES_TRAIT_FIXED_H_

#include <cstdint>
#include <utility>
#include <memory>

#include "../Capacity.h"

namespace bytes
{
namespace trait
{
namespace capacity
{

class Fixed : public bytes::trait::Capacity
{
public:
    inline Fixed() = default;
    inline ~Fixed() = default;
public:
    inline Fixed(const Fixed & cpy);
    inline Fixed(Fixed && mov);
public:
    inline Fixed & operator=(const Fixed & cpy) = default;
    inline Fixed & operator=(Fixed && mov) = default;
public:
    inline std::shared_ptr<bytes::Trait> Copy() const;
public:
    inline std::shared_ptr<bytes::Trait> Move();
public:
    inline bytes::Trait & Assign(const bytes::Trait & cpy);
    inline bytes::Trait & Assign(bytes::Trait && mov);
public:
    inline std::size_t OnSize(const std::size_t & s) const;
public:
    inline std::size_t OnResize(const std::size_t & cs,
        const std::size_t & ns) const;
public:
    inline bool operator==(const bytes::trait::Capacity & b) const;
public:
    inline bool operator!=(const bytes::trait::Capacity & b) const;
};

inline Fixed::Fixed()
{}

inline Fixed::~Fixed()
{}

inline Fixed::Fixed(const Fixed & cpy) :
    bytes::trait::Capacity(cpy)
{}

inline Fixed::Fixed(Fixed && mov) :
    bytes::trait::Capacity(std::move(mov))
{}

inline std::shared_ptr<bytes::trait::Capacity> Fixed::Copy() const
{
    return std::make_shared<Fixed>(*this);
}

inline std::shared_ptr<bytes::trait::Capacity> Fixed::Move()
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

inline std::size_t Fixed::OnSize(const std::size_t & s) const
{
    return s;
}

inline std::size_t Fixed::OnResize(const std::size_t & cs,
    const std::size_t & ns) const
{
    return cs;
}

inline bool Fixed::operator==(const bytes::trait::Capacity & b) const
{
    auto * cb = dynamic_cast<const Fixed *>(&b);
    return cb;
}

inline bool Fixed::operator!=(const bytes::trait::Capacity & b) const
{
    return !(*this == b);
}

} //!capacity

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_FIXED_H_
