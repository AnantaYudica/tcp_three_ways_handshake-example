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
    Element() = default;
public:
    virtual ~Element() = default;
protected:
    Element(const Element & cpy) = default;
    Element(Element && mov) = default;
protected:
    inline Element & operator=(const Element & cpy) = default;
    inline Element & operator=(Element && mov) = default;
public:
    virtual inline std::shared_ptr<Element> Copy() const = 0;
public:
    virtual inline std::shared_ptr<Element> Move() = 0;
public:
    virtual inline Element & Assign(const Element & cpy) = 0;
    virtual inline Element & Assign(Element && mov) = 0;
public:
    virtual std::uint8_t OnAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual bool OnIsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual bool OnIsReverseEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual inline bool operator==(const Element & b) const = 0;
public:
    virtual inline bool operator!=(const Element & b) const = 0;
};

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_ELEMENT_H_
