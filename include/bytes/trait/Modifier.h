#ifndef BYTES_TRAIT_MODIFIER_H_
#define BYTES_TRAIT_MODIFIER_H_

#include <cstdint>
#include <cstddef>
#include <memory>

namespace bytes
{
namespace trait
{

class Modifier
{
protected:
    Modifier() = default;
public:
    virtual ~Modifier() = default;
protected:
    Modifier(const Modifier & cpy) = default;
    Modifier(Modifier && mov) = default;
protected:
    inline Modifier & operator=(const Modifier & cpy) = default;
    inline Modifier & operator=(Modifier && mov) = default;
public:
    virtual inline std::shared_ptr<Modifier> Copy() const = 0;
public:
    virtual inline std::shared_ptr<Modifier> Move() = 0;
public:
    virtual inline Modifier & Assign(const Modifier & cpy) = 0;
    virtual inline Modifier & Assign(Modifier && mov) = 0;
public:
    virtual std::uint8_t OnSet(const std::uint8_t & v, 
        const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed) const = 0;
public:
    virtual std::uint8_t OnGet(const std::uint8_t & v, 
        const std::size_t & i, const std::size_t & bg,
        const std::size_t & ed) const = 0;
public:
    virtual inline bool operator==(const Modifier & b) const = 0;
public:
    virtual inline bool operator!=(const Modifier & b) const = 0;
};

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_MODIFIER_H_
