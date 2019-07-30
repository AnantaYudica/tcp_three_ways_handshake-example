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
    inline Modifier() = default;
public:
    virtual inline ~Modifier() = default;
protected:
    inline Modifier(const Modifier & cpy) = default;
    inline Modifier(Modifier && mov) = default;
protected:
    inline Modifier & operator=(const Modifier & cpy) = default;
    inline Modifier & operator=(Modifier && mov) = default;
public:
    virtual std::shared_ptr<Modifier> Copy() const = 0;
public:
    virtual std::shared_ptr<Modifier> Move() = 0;
public:
    virtual Modifier & Assign(const Modifier & cpy) = 0;
    virtual Modifier & Assign(Modifier && mov) = 0;
public:
    virtual std::uint8_t OnSet(const std::uint8_t & v) const = 0;
public:
    virtual std::uint8_t OnGet(const std::uint8_t & v) const = 0;
public:
    virtual bool operator==(const Modifier & b) const = 0;
public:
    virtual bool operator!=(const Modifier & b) const = 0;
};

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_MODIFIER_H_
