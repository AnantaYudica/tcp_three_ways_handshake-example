#ifndef BYTES_TRAIT_ELEMENT_H_
#define BYTES_TRAIT_ELEMENT_H_

#include <cstdint>
#include <memory>

namespace bytes
{
namespace trait
{

class Element
{
protected:
    inline Element() = default;
public:
    virtual inline ~Element() = default;
protected:
    inline Element(const Element & cpy) = default;
    inline Element(Element && mov) = default;
protected:
    inline Element & operator=(const Element & cpy) = default;
    inline Element & operator=(Element && mov) = default;
public:
    virtual std::shared_ptr<Element> Copy() const = 0;
public:
    virtual std::shared_ptr<Element> Move() = 0;
public:
    virtual Element & Assign(const Element & cpy) = 0;
    virtual Element & Assign(Element && mov) = 0;
public:
    virtual std::size_t OnAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual std::size_t OnReverseAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual std::size_t OnNext(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const = 0;
public:
    virtual std::size_t OnPrevious(const std::size_t & i, 
        const std::size_t & st, const std::size_t & bg, 
        const std::size_t & ed) const = 0;
public:
    virtual bool OnIsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual bool OnIsReverseEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual bool operator==(const Element & b) const = 0;
public:
    virtual bool operator!=(const Element & b) const = 0;
};

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_ELEMENT_H_
