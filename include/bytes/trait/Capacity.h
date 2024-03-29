#ifndef BYTES_TRAIT_CAPACITY_H_
#define BYTES_TRAIT_CAPACITY_H_

#include <cstddef>
#include <memory>

namespace bytes
{
namespace trait
{

class Capacity
{
protected:
    inline Capacity() = default;
public:
    virtual inline ~Capacity() = default;
protected:
    inline Capacity(const Capacity & cpy) = default;
    inline Capacity(Capacity && mov) = default;
protected:
    inline Capacity & operator=(const Capacity & cpy) = default;
    inline Capacity & operator=(Capacity & mov) = default;
public:
    virtual std::shared_ptr<Capacity> Copy() const = 0;
public:
    virtual std::shared_ptr<Capacity> Move() = 0;
public:
    virtual Capacity & Assign(const Capacity & cpy) = 0;
    virtual Capacity & Assign(Capacity && mov) = 0;
public:
    virtual std::size_t OnSize(const std::size_t & s) const = 0;
public:
    virtual std::size_t OnResize(const std::size_t & cs,
        const std::size_t & ns) const = 0;
public:
    virtual bool operator==(const Capacity & b) const = 0;
public:
    virtual bool operator!=(const Capacity & b) const = 0;
};

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_CAPACITY_H_
