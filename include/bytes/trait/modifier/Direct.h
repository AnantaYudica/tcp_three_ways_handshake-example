#ifndef BYTES_TRAIT_MODIFIER_DIRECT_H_
#define BYTES_TRAIT_MODIFIER_DIRECT_H_

#include <cstdint>
#include <utility>
#include <memory>

#include "../Modifier.h"

namespace bytes
{
namespace trait
{
namespace modifier
{

class Direct : public bytes::trait::Modifier
{
public:
    inline Direct();
public:
    inline ~Direct();
public:
    inline Direct(const Direct & cpy);
    inline Direct(Direct && mov);
public:
    inline Direct & operator=(const Direct & cpy);
    inline Direct & operator=(Direct && mov);
public:
    inline std::shared_ptr<bytes::trait::Modifier> Copy() const;
public:
    inline std::shared_ptr<bytes::trait::Modifier> Move();
public:
    inline bytes::trait::Modifier & Assign(const bytes::trait::Modifier & cpy);
    inline bytes::trait::Modifier & Assign(bytes::trait::Modifier && mov);
public:
    inline std::uint8_t OnSet(const std::uint8_t & v, 
        const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed) const;
public:
    inline std::uint8_t OnGet(const std::uint8_t & v, 
        const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed) const;
public:
    inline bool operator==(const bytes::trait::Modifier & b) const;
public:
    inline bool operator!=(const bytes::trait::Modifier & b) const;
};

inline Direct::Direct()
{}

inline Direct::~Direct()
{}

inline Direct::Direct(const Direct & cpy) :
    bytes::trait::Modifier(cpy)
{}

inline Direct::Direct(Direct && mov) :
    bytes::trait::Modifier(std::move(mov))
{}

inline Direct & Direct::operator=(const Direct & cpy)
{
    bytes::trait::Modifier::operator=(cpy);
    return *this;
}

inline Direct & Direct::operator=(Direct && mov)
{
    bytes::trait::Modifier::operator!=(std::move(mov));
    return *this;
}

inline std::shared_ptr<bytes::trait::Modifier> Direct::Copy() const
{
    return std::make_shared<Direct>(*this);
}

inline std::shared_ptr<bytes::trait::Modifier> Direct::Move()
{
    return std::make_shared<Direct>(std::move(*this));
}

inline bytes::trait::Modifier & 
    Direct::Assign(const bytes::trait::Modifier & cpy)
{
    return *this;
}

inline bytes::trait::Modifier & 
    Direct::Assign(bytes::trait::Modifier && mov)
{
    return *this;
}

inline std::uint8_t Direct::OnSet(const std::uint8_t & v, 
    const std::size_t & i, const std::size_t & bg,
    const std::size_t & ed) const
{
    return v;
}

inline std::uint8_t Direct::OnGet(const std::uint8_t & v, 
    const std::size_t & i, const std::size_t & bg,
    const std::size_t & ed) const
{
    return v;
}

inline bool Direct::operator==(const bytes::trait::Modifier & b) const
{
    auto * cb = dynamic_cast<const Direct *>(&b);
    return cb;
}

inline bool Direct::operator!=(const bytes::trait::Modifier & b) const
{
    return !(*this == b);
}

} //!modifier

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_MODIFIER_DIRECT_H_
