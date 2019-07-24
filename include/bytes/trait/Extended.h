#ifndef BYTES_TRAIT_EXTENDED_H_
#define BYTES_TRAIT_EXTENDED_H_

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

class Extended : public bytes::Trait
{
private:
    static inline std::size_t Default(const std::size_t & s);
private:
    std::function<std::size_t(const std::size_t &)> m_formula;
public:
    inline Extended();
    inline Extended(const bytes::Endian::CategoryEnum & e);
    inline Extended(const std::size_t & c);
    inline Extended(const bytes::Endian::CategoryEnum & e,
        const std::size_t & c);
    inline Extended(std::function<std::size_t(const std::size_t &)> f);
    inline Extended(const bytes::Endian::CategoryEnum & e,
        std::function<std::size_t(const std::size_t &)> f);
    inline ~Extended();
public:
    inline Extended(const Extended & cpy);
    inline Extended(Extended && mov);
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

inline std::size_t Extended::Default(const std::size_t & s)
{
    if (s == 0) return 1;
    return s;
}

inline Extended::Extended() :
    m_formula(&Default)
{}

inline Extended::Extended(const bytes::Endian::CategoryEnum & e) :
    m_formula(&Default)
{}

inline Extended::Extended(const std::size_t & c) :
    m_formula([&](const std::size_t & s){
        if (s == 0) return c;
        return s;})
{}

inline Extended::Extended(const bytes::Endian::CategoryEnum & e,
    const std::size_t & c) :
        bytes::Trait(e),
        m_formula([&](const std::size_t & s){
            if (s == 0) return c;
            return s;})
{}

inline Extended::Extended(std::function<std::size_t(const std::size_t &)> f) :
        m_formula(f)
{}

inline Extended::Extended(const bytes::Endian::CategoryEnum & e,
    std::function<std::size_t(const std::size_t &)> f) :
        bytes::Trait(e),
        m_formula(f)
{}

inline Extended::~Extended()
{}

inline Extended::Extended(const Extended & cpy) :
    bytes::Trait(cpy),
    m_formula(cpy.m_formula)
{}

inline Extended::Extended(Extended && mov):
    bytes::Trait(std::move(mov)),
    m_formula(std::move(mov.m_formula))
{
    mov.m_formula = &Default;
}

inline std::shared_ptr<bytes::Trait> Extended::Copy() const
{
    return std::make_shared<Extended>(*this);
}

inline std::shared_ptr<bytes::Trait> Extended::Move()
{
    return std::make_shared<Extended>(std::move(*this));
}

inline bytes::Trait & Extended::Assign(const bytes::Trait & cpy)
{
    auto c = dynamic_cast<const Extended *>(&cpy);
    if (c) m_formula = c->m_formula;
    return *this;
}

inline bytes::Trait & Extended::Assign(bytes::Trait && mov)
{
    auto c = dynamic_cast<Extended *>(&mov);
    if (c) {
        m_formula = c->m_formula;
        c->m_formula = &Default;
    }
    return *this;
}

inline std::size_t Extended::Size(const std::size_t & s) const
{
    return m_formula(s);
}

inline std::size_t Extended::Resize(const std::size_t & cs,
    const std::size_t & ns) const
{
    return m_formula(ns);
}

inline std::size_t Extended::At(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const
{
    return i;
}

inline bool Extended::IsEnd(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const
{
    return i >= ed;
}

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_EXTENDED_H_
