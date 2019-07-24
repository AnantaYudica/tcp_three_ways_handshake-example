#ifndef BYTES_TRAIT_CIRCULAR_H_
#define BYTES_TRAIT_CIRCULAR_H_

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

class Circular : public bytes::Trait
{
public:
    inline Circular();
    inline Circular(const bytes::Endian::CategoryEnum & e);
    inline ~Circular();
public:
    inline Circular(const Circular & cpy);
    inline Circular(Circular && mov);
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

inline Circular::Circular()
{}

inline Circular::Circular(const bytes::Endian::CategoryEnum & e) :
    bytes::Trait(e)
{}

inline Circular::~Circular()
{}

inline Circular::Circular(const Circular & cpy) :
    bytes::Trait(cpy)
{}

inline Circular::Circular(Circular && mov) :
    bytes::Trait(std::move(mov))
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

inline std::size_t Circular::Size(const std::size_t & s) const
{
    return s;
}

inline std::size_t Circular::Resize(const std::size_t & cs,
    const std::size_t & ns) const
{
    return cs;
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

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_CIRCULAR_H_
