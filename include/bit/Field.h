#ifndef BIT_FIELD_H_
#define BIT_FIELD_H_

#include <cstddef>
#include <cstdint>
#include <memory>

#include "../bytes/ptr/Segment.h"
#include "../Bit.h"
#include "../bytes/Endian.h"
#include "../bytes/sys/Endian.h"
#include "field/Value.h"

namespace bit
{

template<std::size_t N>
class Field
{
public:
    typedef typename bit::field::Value<N>::Type ValueType;
private:
    static ValueType Value(const Field<N> & Field);
    static void Value(Field<N> & Field, const ValueType & val);
private:
    static inline void Default(Field<N> & b);
    static inline bool Validation(Field<N> & b);
private:
    std::uint8_t m_offset;
    std::size_t m_index;
    std::shared_ptr<bytes::ptr::Segment> m_segment;
public:
    inline Field();
    inline Field(const ValueType & b);
    inline Field(const std::shared_ptr<bytes::ptr::Segment> & b);
    inline Field(const std::shared_ptr<bytes::ptr::Segment> & b,
        const std::size_t & i);
    inline Field(const std::shared_ptr<bytes::ptr::Segment> & b,
        const std::size_t & i, const std::uint8_t & off);
    inline ~Field();
public:
    inline Field(const Field<N> & cpy);
    inline Field(Field<N> && mov);
public:
    inline Field<N> & operator=(Field<N> && b);
    inline Field<N> & operator=(const Field<N> & b);
    inline Field<N> & operator=(const ValueType & b);
public:
    inline bool IsSameObject(const Field<N> & b) const;
    inline bool 
        IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const;
public:
    inline operator typename bit::field::Value<N>::Type() const;
public:
    inline Field<N> operator~() const;
public:
    inline Field<N> & operator|=(const Field<N> & b);
    inline Field<N> & operator|=(const ValueType & b);
public:
    inline Field<N> operator|(const Field<N> & b) const;
    inline Field<N> operator|(const ValueType & b) const;
public:
    inline Field<N> & operator&=(const Field<N> & b);
    inline Field<N> & operator&=(const ValueType & b);
public:
    inline Field<N> operator&(const Field<N> & b) const;
    inline Field<N> operator&(const ValueType & b) const;
public:
    inline Field<N> & operator^=(const Field<N> & b);
    inline Field<N> & operator^=(const ValueType & b);
public:
    inline Field<N> operator^(const Field<N> & b) const;
    inline Field<N> operator^(const ValueType & b) const;
public:
    inline Field<N> & operator>>=(const std::size_t & b);
public:
    inline Field<N> operator>>(const std::size_t & b) const;
public:
    inline Field<N> & operator<<=(const std::size_t & b);
public:
    inline Field<N> operator<<(const std::size_t & b) const;
public:
    inline Field<N> operator+() const = delete;
public:
    inline Field<N> operator-() const = delete;
public:
    inline Field<N> & operator++();
    inline Field<N> operator++(int);
public:
    inline Field<N> & operator--();
    inline Field<N> operator--(int);
public:
    inline Field<N> & operator+=(const Field<N> & b);
    inline Field<N> & operator+=(const ValueType & b);
public:
    inline Field<N> operator+(const Field<N> & b) const;
    inline Field<N> operator+(const ValueType & b) const;
public:
    inline Field<N> & operator-=(const Field<N> & b);
    inline Field<N> & operator-=(const ValueType & b);
public:
    inline Field<N> operator-(const Field<N> & b) const;
    inline Field<N> operator-(const ValueType & b) const;
public:
    inline Field<N> & operator*=(const Field<N> & b);
    inline Field<N> & operator*=(const ValueType & b);
public:
    inline Field<N> operator*(const Field<N> & b) const;
    inline Field<N> operator*(const ValueType & b) const;
public:
    inline Field<N> & operator/=(const Field<N> & b);
    inline Field<N> & operator/=(const ValueType & b);
public:
    inline Field<N> operator/(const Field<N> & b) const;
    inline Field<N> operator/(const ValueType & b) const;
public:
    inline Field<N> & operator%=(const Field<N> & b);
    inline Field<N> & operator%=(const ValueType & b);
public:
    inline Field<N> operator%(const Field<N> & b) const;
    inline Field<N> operator%(const ValueType& b) const;
public:
    inline Bit operator[](const std::size_t & i);
    inline const Bit operator[](const std::size_t & i) const;
public:
    inline bool operator==(const Field<N> & b) const;
    inline bool operator==(const ValueType & b) const;
public:
    inline bool operator!=(const Field<N> & b) const;
    inline bool operator!=(const ValueType & b) const;
public:
    inline bool operator<(const Field<N> & b) const;
    inline bool operator<(const ValueType & b) const;
public:
    inline bool operator<=(const Field<N> & b) const;
    inline bool operator<=(const ValueType & b) const;
public:
    inline bool operator>(const Field<N> & b) const;
    inline bool operator>(const ValueType & b) const;
public:
    inline bool operator>=(const Field<N> & b) const;
    inline bool operator>=(const ValueType & b) const;
public:
    inline void Swap(Field<N> & b);
};

template<std::size_t N>
inline typename Field<N>::ValueType Field<N>::Value(const Field<N> & Field)
{
    const auto & endian = bytes::sys::Endian();
    auto & segment = Field.m_segment;
    const auto & index = Field.m_index;
    const auto & offset = Field.m_offset;
    ValueType val = 0;
    std::uint8_t * pval = (std::uint8_t *)&val;
    std::size_t i_st = index;
    for (std::size_t j = 0; j < sizeof(ValueType); ++j, ++i_st)
    {
        const std::size_t i = segment->Next(0, i_st);
        pval[endian.ReverseAt(j, 0, sizeof(ValueType))] =
            segment->ReverseAt(i, offset, N);
    }
    return val;
}

template<std::size_t N>
inline void Field<N>::Value(Field<N> & Field, const ValueType & val)
{
    const auto & endian = bytes::sys::Endian();
    auto & segment = Field.m_segment;
    const auto & index = Field.m_index;
    const auto & offset = Field.m_offset;
    std::uint8_t * pval = (std::uint8_t *)&val;
    std::size_t i_st = index;
    for (std::size_t j = 0; j < sizeof(ValueType); ++i_st, ++j)
    {
        const std::size_t i = segment->Next(0, i_st);
        segment->ReverseAt(i, offset, N) = 
            pval[endian.ReverseAt(j, 0, sizeof(ValueType))];
    }
}

template<std::size_t N>
inline void Field<N>::Default(Field<N> & b)
{
    b.m_offset = 0;
    b.m_index = 0;
    b.m_segment = std::make_shared<bytes::ptr::Segment>(0, sizeof(ValueType),
        std::make_shared<bytes::ptr::Object>(sizeof(ValueType)));
}

template<std::size_t N>
inline bool Field<N>::Validation(Field<N> & b)
{
    if (!b.m_segment && !*(b.m_segment)) 
    {  
        Default(b);
        return false;
    }
    return true;
}

template<std::size_t N>
inline Field<N>::Field() :
    m_offset(0),
    m_index(0),
    m_segment(new bytes::ptr::Segment(0, sizeof(ValueType), 
        std::make_shared<bytes::ptr::Object>(sizeof(ValueType))))
{}

template<std::size_t N>
inline Field<N>::Field(const ValueType & b) :
    m_offset(0),
    m_index(0),
    m_segment(new bytes::ptr::Segment(0, sizeof(ValueType), 
        std::make_shared<bytes::ptr::Object>(sizeof(ValueType))))
{
    *this = b;
}

template<std::size_t N>
inline Field<N>::Field(const std::shared_ptr<bytes::ptr::Segment> & b) :
    m_offset(0),
    m_index(0),
    m_segment(b)
{
    Validation(*this);
}

template<std::size_t N>
inline Field<N>::Field(const std::shared_ptr<bytes::ptr::Segment> & b,
    const std::size_t & i) :
        m_offset(0),
        m_index(i),
        m_segment(b)
{
    Validation(*this);
}
    
template<std::size_t N>
inline Field<N>::Field(const std::shared_ptr<bytes::ptr::Segment> & b,
    const std::size_t & i, const std::uint8_t & off) :
        m_offset(off),
        m_index(i),
        m_segment(b)
{
    Validation(*this);
}
    
template<std::size_t N>
inline Field<N>::~Field()
{
    m_offset = 0;
    m_index = 0;
    m_segment = nullptr;
}

template<std::size_t N>
inline Field<N>::Field(const Field<N> & cpy) :
    m_offset(0),
    m_index(0),
    m_segment(new bytes::ptr::Segment(0, sizeof(ValueType), 
        std::make_shared<bytes::ptr::Object>(sizeof(ValueType))))
{
    *this = static_cast<ValueType>(cpy);
}

template<std::size_t N>
inline Field<N>::Field(Field<N> && mov) :
    m_offset(mov.m_offset),
    m_index(mov.m_index),
    m_segment(mov.m_segment)
{
    Default(mov);
}

template<std::size_t N>
inline Field<N> & Field<N>::operator=(Field<N> && b)
{
    return (*this = static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator=(const Field<N> & b)
{
    return (*this = static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator=(const ValueType & b)
{
    Value(*this, b);
    return *this;
}

template<std::size_t N>
inline bool Field<N>::IsSameObject(const Field<N> & b) const
{
    return m_segment->IsSameObject(*(b.m_segment));
}

template<std::size_t N>
inline bool Field<N>::
    IsSameObject(const std::shared_ptr<bytes::ptr::Object> & b) const
{
    return m_segment->IsSameObject(b);
}
    
template<std::size_t N>
inline Field<N>::operator typename bit::field::Value<N>::Type () const
{
    return Value(*this);
}

template<std::size_t N>
inline Field<N> Field<N>::operator~() const
{
    Field<N> res{~static_cast<ValueType>(*this)};
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator|=(const Field<N> & b)
{
    return (*this |= static_cast<ValueType>(b)); 
}

template<std::size_t N>
inline Field<N> & Field<N>::operator|=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) | b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator|(const Field<N> & b) const
{
    Field<N> res(*this);
    res |= b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator|(const ValueType & b) const
{
    Field<N> res(*this);
    res |= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator&=(const Field<N> & b)
{
    return (*this &= static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator&=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) & b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator&(const Field<N> & b) const
{
    Field<N> res{*this};
    res &= b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator&(const ValueType & b) const
{
    Field<N> res{*this};
    res &= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator^=(const Field<N> & b)
{
    return (*this ^= static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator^=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) ^ b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator^(const Field<N> & b) const
{
    Field<N> res{*this};
    res ^= b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator^(const ValueType & b) const
{
    Field<N> res{*this};
    res ^= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator>>=(const std::size_t & b)
{
    *this = (static_cast<ValueType>(*this) >> b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator>>(const std::size_t & b) const
{
    Field<N> res{*this};
    res >>= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator<<=(const std::size_t & b)
{
    *this = (static_cast<ValueType>(*this) << b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator<<(const std::size_t & b) const
{
    Field<N> res{*this};
    res <<= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator++()
{
    *this += 1;
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator++(int)
{
    Field<N> res{*this};
    ++(*this);
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator--()
{
    *this -= 1;
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator--(int)
{
    Field<N> res{*this};
    --(*this);
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator+=(const Field<N> & b)
{
    return (*this += static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator+=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) + b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator+(const Field<N> & b) const
{
    Field<N> res{*this};
    res += b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator+(const ValueType & b) const
{
    Field<N> res{*this};
    res += b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator-=(const Field<N> & b)
{
    return (*this -= static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator-=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) - b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator-(const Field<N> & b) const
{
    Field<N> res{*this};
    res -= b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator-(const ValueType & b) const
{
    Field<N> res{*this};
    res -= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator*=(const Field<N> & b)
{
    return (*this *= static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator*=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) * b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator*(const Field<N> & b) const
{
    Field<N> res{*this};
    res *= b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator*(const ValueType & b) const
{
    Field<N> res{*this};
    res *= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator/=(const Field<N> & b)
{
    return (*this /= static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator/=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) / b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator/(const Field<N> & b) const
{
    Field<N> res{*this};
    res /= b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator/(const ValueType & b) const
{
    Field<N> res{*this};
    res /= b;
    return res;
}

template<std::size_t N>
inline Field<N> & Field<N>::operator%=(const Field<N> & b)
{
    return (*this %= static_cast<ValueType>(b));
}

template<std::size_t N>
inline Field<N> & Field<N>::operator%=(const ValueType & b)
{
    *this = (static_cast<ValueType>(*this) % b);
    return *this;
}

template<std::size_t N>
inline Field<N> Field<N>::operator%(const Field<N> & b) const
{
    Field<N> res{*this};
    res %= b;
    return res;
}

template<std::size_t N>
inline Field<N> Field<N>::operator%(const ValueType& b) const
{
    Field<N> res{*this};
    res %= b;
    return res;
}

template<std::size_t N>
inline Bit Field<N>::operator[](const std::size_t & i)
{
    return {m_segment, i % 8, m_index + (i / 8), m_offset};
}

template<std::size_t N>
inline const Bit Field<N>::operator[](const std::size_t & i) const
{
    Bit res{m_segment->ReverseAt(m_index + (i / 8), m_offset), i % 8};
    return res;
}

template<std::size_t N>
inline bool Field<N>::operator==(const Field<N> & b) const
{
    return *this == static_cast<ValueType>(b);
}

template<std::size_t N>
inline bool Field<N>::operator==(const ValueType & b) const
{
    return static_cast<ValueType>(*this) == b;
}

template<std::size_t N>
inline bool Field<N>::operator!=(const Field<N> & b) const
{
    return !(*this == b);
}

template<std::size_t N>
inline bool Field<N>::operator!=(const ValueType & b) const
{
    return !(*this == b);
}

template<std::size_t N>
inline bool Field<N>::operator<(const Field<N> & b) const
{
    return *this < static_cast<ValueType>(b);
}

template<std::size_t N>
inline bool Field<N>::operator<(const ValueType & b) const
{
    return static_cast<ValueType>(*this) < b;
}

template<std::size_t N>
inline bool Field<N>::operator<=(const Field<N> & b) const
{
    return *this <= static_cast<ValueType>(b);
}

template<std::size_t N>
inline bool Field<N>::operator<=(const ValueType & b) const
{
    return static_cast<ValueType>(*this) <= b; 
}

template<std::size_t N>
inline bool Field<N>::operator>(const Field<N> & b) const
{
    return *this > static_cast<ValueType>(b);
}

template<std::size_t N>
inline bool Field<N>::operator>(const ValueType & b) const
{
    return static_cast<ValueType>(*this) > b;
}

template<std::size_t N>
inline bool Field<N>::operator>=(const Field<N> & b) const
{
    return *this >= static_cast<ValueType>(b);
}

template<std::size_t N>
inline bool Field<N>::operator>=(const ValueType & b) const
{
    return static_cast<ValueType>(*this) >= b;
}

template<std::size_t N>
inline void Field<N>::Swap(Field<N> & b)
{
    auto offset = m_offset;
    auto index = m_index;
    auto segment = m_segment;
    m_offset = b.m_offset;
    m_index = b.m_index;
    m_segment = b.m_segment;
    b.m_offset = offset;
    b.m_index = index;
    b.m_segment = segment;
}

} //!bit

template<std::size_t N>
inline bit::Field<N> operator|(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b | a;
}

template<std::size_t N>
inline bit::Field<N> operator&(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b & a;
}

template<std::size_t N>
inline bit::Field<N> operator^(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b ^ a;
}

template<std::size_t N>
inline bit::Field<N> operator+(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b + a;
}

template<std::size_t N>
inline bit::Field<N> operator-(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return bit::Field<N>(a) - b;
}

template<std::size_t N>
inline bit::Field<N> operator*(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b * a;
}

template<std::size_t N>
inline bit::Field<N> operator/(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return bit::Field<N>(a) / b;
}

template<std::size_t N>
inline bit::Field<N> operator%(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return bit::Field<N>(a) % b;
}

template<std::size_t N>
inline bool operator==(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b == a;
}

template<std::size_t N>
inline bool operator!=(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b != a;
}

template<std::size_t N>
inline bool operator<(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b > a;
}

template<std::size_t N>
inline bool operator<=(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b >= a;
}

template<std::size_t N>
inline bool operator>(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b < a;
}

template<std::size_t N>
inline bool operator>=(const typename bit::Field<N>::ValueType & a, 
    const bit::Field<N> & b)
{
    return b <= a;
}


#endif //!BIT_FIELD_H_
