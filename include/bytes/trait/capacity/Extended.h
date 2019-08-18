#ifndef BYTES_TRAIT_CAPACITY_EXTENDED_H_
#define BYTES_TRAIT_CAPACITY_EXTENDED_H_

#include <functional>
#include <cstdint>
#include <limits>
#include <utility>
#include <memory>

#include "../Capacity.h"

namespace bytes
{
namespace trait
{
namespace capacity
{

class Extended : public bytes::trait::Capacity
{
private:
    static inline std::size_t Default(const std::size_t & s);
private:
    std::function<std::size_t(const std::size_t &)> m_formula;
public:
    inline Extended();
    inline Extended(const std::size_t & c);
    inline Extended(std::function<std::size_t(const std::size_t &)> f);
public:
    inline ~Extended();
public:
    inline Extended(const Extended & cpy);
    inline Extended(Extended && mov);
public:
    inline Extended & operator=(const Extended & cpy);
    inline Extended & operator=(Extended && mov);
public:
    inline std::shared_ptr<bytes::trait::Capacity> Copy() const;
public:
    inline std::shared_ptr<bytes::trait::Capacity> Move();
public:
    inline bytes::trait::Capacity & Assign(const bytes::trait::Capacity & cpy);
    inline bytes::trait::Capacity & Assign(bytes::trait::Capacity && mov);
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

inline std::size_t Extended::Default(const std::size_t & s)
{
    if (s == 0) return 1;
    return s;
}

inline Extended::Extended() :
    m_formula(&Default)
{}

inline Extended::Extended(const std::size_t & c) :
    m_formula([&](const std::size_t & s){
        if (s == 0) return c;
        return s;})
{}

inline Extended::Extended(std::function<std::size_t(const std::size_t &)> f) :
        m_formula(f)
{}

inline Extended::~Extended()
{}

inline Extended::Extended(const Extended & cpy) :
    bytes::trait::Capacity(cpy),
    m_formula(cpy.m_formula)
{}

inline Extended::Extended(Extended && mov):
    bytes::trait::Capacity(std::move(mov)),
    m_formula(std::move(mov.m_formula))
{
    mov.m_formula = &Default;
}

inline Extended & Extended::operator=(const Extended & cpy)
{
    bytes::trait::Capacity::operator=(cpy);
    m_formula = cpy.m_formula;
    return *this;
}

inline Extended & Extended::operator=(Extended && mov)
{
    bytes::trait::Capacity::operator=(std::move(mov));
    m_formula = mov.m_formula;
    mov.m_formula = &Default;
    return *this;
}

inline std::shared_ptr<bytes::trait::Capacity> Extended::Copy() const
{
    return std::make_shared<Extended>(*this);
}

inline std::shared_ptr<bytes::trait::Capacity> Extended::Move()
{
    return std::make_shared<Extended>(std::move(*this));
}

inline bytes::trait::Capacity & 
    Extended::Assign(const bytes::trait::Capacity & cpy)
{
    auto c = dynamic_cast<const Extended *>(&cpy);
    if (c) m_formula = c->m_formula;
    return *this;
}

inline bytes::trait::Capacity & 
    Extended::Assign(bytes::trait::Capacity && mov)
{
    auto c = dynamic_cast<Extended *>(&mov);
    if (c) {
        m_formula = c->m_formula;
        c->m_formula = &Default;
    }
    return *this;
}

inline std::size_t Extended::OnSize(const std::size_t & s) const
{
    return m_formula(s);
}

inline std::size_t Extended::OnResize(const std::size_t & cs,
    const std::size_t & ns) const
{
    return m_formula(ns);
}

inline bool Extended::operator==(const bytes::trait::Capacity & b) const
{
    auto * cb = dynamic_cast<const Extended *>(&b);
    return cb && &m_formula == &(cb->m_formula);
}

inline bool Extended::operator!=(const bytes::trait::Capacity & b) const
{
    return !(*this == b);
}

} //!capacity

} //!trait

} //!bytes

#endif //!BYTES_TRAIT_CAPACITY_EXTENDED_H_
