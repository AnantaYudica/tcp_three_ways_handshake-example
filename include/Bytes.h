#ifndef BYTES_H_
#define BYTES_H_

#include <cstdint>
#include <cstddef>
#include <memory>
#include <initializer_list>

#include "Byte.h"
#include "bytes/Base.h"
#include "bytes/arithmetic/Addition.h"
#include "bytes/Pointer.h"
#include "bytes/ptr/Segment.h"
#include "bytes/Endian.h"
#include "bytes/endian/Big.h"
#include "bytes/endian/Little.h"
#include "bytes/sys/Endian.h"
#include "bytes/sys/endian/Category.h"
#include "bytes/Trait.h"
#include "bytes/trait/capacity/Fixed.h"
#include "bytes/trait/capacity/Extended.h"
#include "bytes/trait/element/Direct.h"
#include "bytes/trait/modifier/Direct.h"
#include "bytes/Assign.h"
#include "bytes/Comparison.h"
#include "bytes/arithmetic/bitwise/Not.h"
#include "bytes/arithmetic/bitwise/Or.h"
#include "bytes/arithmetic/bitwise/And.h"
#include "bytes/arithmetic/bitwise/Xor.h"
#include "bytes/arithmetic/bitwise/Shift.h"
#include "bytes/arithmetic/Addition.h"
#include "bytes/arithmetic/Subtraction.h"
#include "bytes/arithmetic/Multiplication.h"
#include "bytes/arithmetic/Division.h"
#include "bytes/arithmetic/Modulo.h"

class Bytes : protected bytes::Base
{
public:
    inline Bytes();
    inline Bytes(const bytes::Endian::CategoryEnum & e);
    inline Bytes(const bytes::Trait & t);
    inline Bytes(const std::shared_ptr<bytes::Trait> & t);
public:
    inline Bytes(const std::size_t & s);
    inline Bytes(const std::size_t & s, const bytes::Endian::CategoryEnum & e);
    inline Bytes(const std::size_t & s, const bytes::Trait & t);
    inline Bytes(const std::size_t & s, const std::shared_ptr<bytes::Trait> & t);
public:
    template<std::size_t N>
    inline Bytes(const std::uint8_t (&b)[N]);
    template<std::size_t N>
    inline Bytes(const std::uint8_t (&b)[N], 
        const bytes::Endian::CategoryEnum & e);
    template<std::size_t N>
    inline Bytes(const std::uint8_t (&b)[N], const bytes::Trait & t);
    template<std::size_t N>
    inline Bytes(const std::uint8_t (&b)[N], 
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline Bytes(const std::uint8_t * ptr, const std::size_t & s);
    inline Bytes(const std::uint8_t * ptr, const std::size_t & s,
        const bytes::Endian::CategoryEnum & e);
    inline Bytes(const std::uint8_t * ptr, const std::size_t & s, 
        const bytes::Trait & t);
    inline Bytes(const std::uint8_t * ptr, const std::size_t & s, 
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline Bytes(std::initializer_list<std::uint8_t> li);
    inline Bytes(std::initializer_list<std::uint8_t> li,
        const bytes::Endian::CategoryEnum & e);
    inline Bytes(std::initializer_list<std::uint8_t> li, 
        const bytes::Trait & t);
    inline Bytes(std::initializer_list<std::uint8_t> li, 
        const std::shared_ptr<bytes::Trait> & t);
private: 
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s);
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const bytes::Endian::CategoryEnum & e);
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const bytes::Trait & t);
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const std::shared_ptr<bytes::Trait> & t);
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & s, const bytes::Endian::CategoryEnum & e,
        const std::shared_ptr<bytes::Trait> & t);
private:
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed);
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed, 
        const bytes::Endian::CategoryEnum & e);
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed, 
        const bytes::Trait & t);
    inline Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
        const std::size_t & bg, const std::size_t & ed, 
        const std::shared_ptr<bytes::Trait> & t);
public:
    inline ~Bytes();
public:
    inline Bytes(const Bytes & cpy);
    inline Bytes(Bytes && mov);
public:
    inline Bytes & operator=(const Bytes & b);
    inline Bytes & operator=(Bytes && b);
    template<std::size_t N>
    inline Bytes & operator=(const std::uint8_t (&b)[N]);
    inline Bytes & operator=(const std::uint8_t & b);
    inline Bytes & operator=(std::initializer_list<std::uint8_t> li);
public:
    const bytes::Trait & GetTrait() const;
public:
    Byte At(const std::size_t & i);
    const Byte At(const std::size_t & i) const;
public:
    inline std::size_t Size() const;
public:
    inline bool IsEnd(const std::size_t & i) const;
public:
    inline bool IsReverseEnd(const std::size_t & i) const;
public:
    inline void Assign(const std::uint8_t * ptr, const std::size_t & ptr_s);
    template<std::size_t N>
    inline void Assign(const std::uint8_t (&b)[N]);
    inline void Assign(const std::uint8_t & b);
    inline void Assign(std::initializer_list<std::uint8_t> li);
    inline void Assign(const Bytes & b);
    inline void Assign(const std::size_t & i, const std::uint8_t * ptr, 
        const std::size_t & ptr_s);
    template<std::size_t N>
    inline void Assign(const std::size_t & i, const std::uint8_t (&b)[N]);
    inline void Assign(const std::size_t & i, const std::uint8_t & b);
    inline void Assign(const std::size_t & i, 
        std::initializer_list<std::uint8_t> li);
    inline void Assign(const std::size_t & i, const Bytes & b);
    inline void Assign(const std::size_t & i, const Bytes & b, 
        const std::size_t & ib);
    inline void Assign(const std::size_t & i, const Bytes & b, 
        const std::size_t & ib, const std::size_t & sb);
    inline void Assign(const std::size_t & i, const std::size_t & s, 
        const std::uint8_t & b);
public:
    inline Bytes Slice(const std::size_t & i);
    inline const Bytes Slice(const std::size_t & i) const;
    inline Bytes Slice(const std::size_t & i, const bytes::Trait & t);
    inline const Bytes Slice(const std::size_t & i, 
        const bytes::Trait & t) const;
    inline Bytes Slice(const std::size_t & i, const std::size_t & s);
    inline const Bytes Slice(const std::size_t & i, 
        const std::size_t & s) const;
    inline Bytes Slice(const std::size_t & i, const std::size_t & s,
        const bytes::Trait & t);
    inline const Bytes Slice(const std::size_t & i, const std::size_t & s,
        const bytes::Trait & t) const;
public:
    inline std::uint8_t * Get();
    inline const std::uint8_t * Get() const;
public:
    inline Bytes operator~() const;
public:
    inline Bytes & operator|=(const Bytes & b);
public:
    inline Bytes operator|(const Bytes & b) const;
public:
    inline Bytes & operator&=(const Bytes & b);
public:
    inline Bytes operator&(const Bytes & b) const;
public:
    inline Bytes & operator^=(const Bytes & b);
public:
    inline Bytes operator^(const Bytes & b) const;
public:
    inline Bytes & operator>>=(const std::size_t & b);
public:
    inline Bytes operator>>(const std::size_t & b) const;
public:
    inline Bytes & operator<<=(const std::size_t & b);
public:
    inline Bytes operator<<(const std::size_t & b) const;
public:
    inline Bytes & operator++();
    inline Bytes operator++(int);
public:
    inline Bytes & operator--();
    inline Bytes operator--(int);
public:
    inline Bytes & operator+=(const Bytes & b);
public:
    inline Bytes operator+(const Bytes & b) const;
public:
    inline Bytes & operator-=(const Bytes & b);
public:
    inline Bytes operator-(const Bytes & b) const;
public:
    inline Bytes & operator*=(const Bytes & b);
public:
    inline Bytes operator*(const Bytes & b) const;
public:
    inline Bytes & operator/=(const Bytes & b);
public:
    inline Bytes operator/(const Bytes & b) const;
public:
    inline Bytes & operator%=(const Bytes & b);
public:
    inline Bytes operator%(const Bytes & b) const;
public:
    Byte operator[](const std::size_t & i);
    const Byte operator[](const std::size_t & i) const;
public:
    inline bool operator==(const Bytes & b) const;
public:
    inline bool operator!=(const Bytes & b) const;
public:
    inline bool operator<(const Bytes & b) const;
public:
    inline bool operator<=(const Bytes & b) const;
public:
    inline bool operator>(const Bytes & b) const;
public:
    inline bool operator>=(const Bytes & b) const;
public:
    inline void Swap(Bytes & b);
};

inline Bytes::Bytes() :
    bytes::Base()
{}

inline Bytes::Bytes(const bytes::Endian::CategoryEnum & e) :
    bytes::Base(e)
{}

inline Bytes::Bytes(const bytes::Trait & t) :
    bytes::Base(t)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Trait> & t) :
    bytes::Base(t)
{}

inline Bytes::Bytes(const std::size_t & s) :
    bytes::Base(s)
{}

inline Bytes::Bytes(const std::size_t & s, 
    const bytes::Endian::CategoryEnum & e) :
        bytes::Base(s, e)
{}

inline Bytes::Bytes(const std::size_t & s, const bytes::Trait & t) :
    bytes::Base(s, t)
{}

inline Bytes::Bytes(const std::size_t & s, 
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::Base(s, t)
{}

template<std::size_t N>
inline Bytes::Bytes(const std::uint8_t (&b)[N]) :
    bytes::Base(b)
{}

template<std::size_t N>
inline Bytes::Bytes(const std::uint8_t (&b)[N], 
    const bytes::Endian::CategoryEnum & e) :
        bytes::Base(b, e)
{}

template<std::size_t N>
inline Bytes::Bytes(const std::uint8_t (&b)[N], const bytes::Trait & t) :
    bytes::Base(b, t)
{}

template<std::size_t N>
inline Bytes::Bytes(const std::uint8_t (&b)[N], 
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::Base(b, t)
{}

inline Bytes::Bytes(const std::uint8_t * ptr, const std::size_t & s) :
    bytes::Base(ptr, s)
{}

inline Bytes::Bytes(const std::uint8_t * ptr, const std::size_t & s,
    const bytes::Endian::CategoryEnum & e) :
        bytes::Base(ptr, s, e)
{}

inline Bytes::Bytes(const std::uint8_t * ptr, const std::size_t & s, 
    const bytes::Trait & t) :
        bytes::Base(ptr, s, t)
{}

inline Bytes::Bytes(const std::uint8_t * ptr, const std::size_t & s,
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::Base(ptr, s, t)
{}

inline Bytes::Bytes(std::initializer_list<std::uint8_t> li) :
    bytes::Base(li.begin(), li.size())
{}

inline Bytes::Bytes(std::initializer_list<std::uint8_t> li,
    const bytes::Endian::CategoryEnum & e) :
        bytes::Base(li.begin(), li.size(), e)
{}

inline Bytes::Bytes(std::initializer_list<std::uint8_t> li, 
    const bytes::Trait & t)  :
        bytes::Base(li.begin(), li.size(), t)
{}

inline Bytes::Bytes(std::initializer_list<std::uint8_t> li, 
    const std::shared_ptr<bytes::Trait> & t)  :
        bytes::Base(li.begin(), li.size(), t)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s) :
        bytes::Base(ptr, s)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s, const bytes::Endian::CategoryEnum & e) :
        bytes::Base(ptr, s, e)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s, const bytes::Trait & t) :
        bytes::Base(ptr, s, t)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & s, const std::shared_ptr<bytes::Trait> & t) :
        bytes::Base(ptr, s, t)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed) :
        bytes::Base(ptr, bg, ed)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed, 
    const bytes::Endian::CategoryEnum & e) :
        bytes::Base(ptr, bg, ed, e)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed, 
    const bytes::Trait & t) :
        bytes::Base(ptr, bg, ed, t)
{}

inline Bytes::Bytes(const std::shared_ptr<bytes::Pointer> & ptr, 
    const std::size_t & bg, const std::size_t & ed, 
    const std::shared_ptr<bytes::Trait> & t) :
        bytes::Base(ptr, bg, ed, t)
{}


inline Bytes::~Bytes()
{}

inline Bytes::Bytes(const Bytes & cpy) :
    bytes::Base(cpy)
{}

inline Bytes::Bytes(Bytes && mov) :
    bytes::Base(std::move(mov))
{}

inline Bytes & Bytes::operator=(const Bytes & b)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), b.GetSegment());
    return *this;
}

inline Bytes & Bytes::operator=(Bytes && b)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), b.GetSegment());
    return *this;
}

template<std::size_t N>
inline Bytes & Bytes::operator=(const std::uint8_t (&b)[N])
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), b);
    return *this;
}

inline Bytes & Bytes::operator=(const std::uint8_t & b)
{
    bytes::Assign::Operator(GetSegment(), b);
    return *this;
}

inline Bytes & Bytes::operator=(std::initializer_list<std::uint8_t> li)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), li.begin(), li.size());
    return *this;
}

const bytes::Trait & Bytes::GetTrait() const
{
    return GetSegment()->Trait();
}

Byte Bytes::At(const std::size_t & i)
{
    const std::size_t index = GetSegment()->At(i).Index();
    return Byte(GetPointer()->Share(index, index + 1, 
        SetCapacityTrait<bytes::trait::capacity::Fixed>(GetTrait())));
}

const Byte Bytes::At(const std::size_t & i) const
{
    auto _this = const_cast<Bytes *>(this);
    return _this->At(i);
}

inline std::size_t Bytes::Size() const
{
    return GetSegment()->Size();
}

inline bool Bytes::IsEnd(const std::size_t & i) const
{
    return GetSegment()->IsEnd(i);
}

inline bool Bytes::IsReverseEnd(const std::size_t & i) const
{
    return GetSegment()->IsReverseEnd(i);
}

inline void Bytes::Assign(const std::uint8_t * ptr, 
    const std::size_t & ptr_s)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), ptr, ptr_s);
}

template<std::size_t N>
inline void Bytes::Assign(const std::uint8_t (&b)[N])
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), b);
}

inline void Bytes::Assign(const std::uint8_t & b)
{
    bytes::Assign::Operator(GetSegment(), b);
}

inline void Bytes::Assign(std::initializer_list<std::uint8_t> li)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), 
        li.begin(), li.size());
}

inline void Bytes::Assign(const Bytes & b)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), b.GetSegment());
}

inline void Bytes::Assign(const std::size_t & i, const std::uint8_t * ptr, 
    const std::size_t & ptr_s)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), i, ptr, ptr_s);
}

template<std::size_t N>
inline void Bytes::Assign(const std::size_t & i, const std::uint8_t (&b)[N])
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), i, b);
}

inline void Bytes::Assign(const std::size_t & i, const std::uint8_t & b)
{
    bytes::Assign::Operator(GetSegment(), i, b);
}

inline void Bytes::Assign(const std::size_t & i, 
    std::initializer_list<std::uint8_t> li)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), i, 
        li.begin(), li.size());
}

inline void Bytes::Assign(const std::size_t & i, const Bytes & b)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), i, b.GetSegment());
}

inline void Bytes::Assign(const std::size_t & i, const Bytes & b, 
    const std::size_t & ib)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), i, 
        b.GetSegment(), ib);
}

inline void Bytes::Assign(const std::size_t & i, const Bytes & b, 
    const std::size_t & ib, const std::size_t & sb)
{
    bytes::Assign::Operator(GetPointer(), GetSegment(), i, 
        b.GetSegment(), ib, sb);
}

inline void Bytes::Assign(const std::size_t & i, const std::size_t & s, 
    const std::uint8_t & b)
{
    bytes::Assign::Operator(GetSegment(), i, s, b);
}

inline Bytes Bytes::Slice(const std::size_t & i)
{
    return Bytes(GetPointer(), GetSegment()->At(i).Index(), GetTrait());
}

inline const Bytes Bytes::Slice(const std::size_t & i) const
{
    auto _this = const_cast<Bytes *>(this);
    return Bytes(_this->GetPointer(), GetSegment()->At(i).Index(), GetTrait());
}

inline Bytes Bytes::Slice(const std::size_t & i, const bytes::Trait & t)
{
    return Bytes(GetPointer(), GetSegment()->At(i).Index(), t);
}

inline const Bytes Bytes::Slice(const std::size_t & i, 
    const bytes::Trait & t) const
{
    auto _this = const_cast<Bytes *>(this);
    return Bytes(_this->GetPointer(), GetSegment()->At(i).Index(), t);
}

inline Bytes Bytes::Slice(const std::size_t & i, const std::size_t & s)
{
    const std::size_t index = GetSegment()->At(i).Index();
    return Bytes(GetPointer(), index, index + s, GetTrait());
}

inline const Bytes Bytes::Slice(const std::size_t & i, 
    const std::size_t & s) const
{
    const std::size_t index = GetSegment()->At(i).Index();
    auto _this = const_cast<Bytes *>(this);
    return Bytes(_this->GetPointer(), index, index + s, GetTrait());
}

inline Bytes Bytes::Slice(const std::size_t & i, const std::size_t & s,
    const bytes::Trait & t)
{
    const std::size_t index = GetSegment()->At(i).Index();
    return Bytes(GetPointer(), index, index + s, t);
}

inline const Bytes Bytes::Slice(const std::size_t & i, const std::size_t & s,
    const bytes::Trait & t) const
{
    const std::size_t index = GetSegment()->At(i).Index();
    auto _this = const_cast<Bytes *>(this);
    return Bytes(_this->GetPointer(), index, index + s, t);
}

inline std::uint8_t * Bytes::Get()
{
    return GetSegment()->Get();
}

inline const std::uint8_t * Bytes::Get() const
{
    return GetSegment()->Get();
}

inline Bytes Bytes::operator~() const
{
    Bytes res(*this);
    bytes::arithmetic::bitwise::Not::Operator(res.GetSegment());
    return res;
}

inline Bytes & Bytes::operator|=(const Bytes & b)
{
    bytes::arithmetic::bitwise::Or::Operator(GetPointer(),
        GetSegment(), b.GetSegment());
    return *this;
}

inline Bytes Bytes::operator|(const Bytes & b) const
{
    Bytes res(*this);
    res |= b;
    return res;
}

inline Bytes & Bytes::operator&=(const Bytes & b)
{
    bytes::arithmetic::bitwise::And::Operator(GetPointer(),
        GetSegment(), b.GetSegment());
    return *this;
}

inline Bytes Bytes::operator&(const Bytes & b) const
{
    Bytes res(*this);
    res |= b;
    return res;
}

inline Bytes & Bytes::operator^=(const Bytes & b)
{
    bytes::arithmetic::bitwise::Xor::Operator(GetPointer(),
        GetSegment(), b.GetSegment());
    return *this;
}

inline Bytes Bytes::operator^(const Bytes & b) const
{
    Bytes res(*this);
    res ^= b;
    return res;
}

inline Bytes & Bytes::operator>>=(const std::size_t & b)
{
    bytes::arithmetic::bitwise::Shift::Operator(GetSegment(), 
        -std::intmax_t(b));
    return *this;
}

inline Bytes Bytes::operator>>(const std::size_t & b) const
{
    Bytes res(*this);
    res >>= b;
    return res;
}

inline Bytes & Bytes::operator<<=(const std::size_t & b)
{
    bytes::arithmetic::bitwise::Shift::Operator(GetSegment(), 
        std::intmax_t(b));
    return *this;
}

inline Bytes Bytes::operator<<(const std::size_t & b) const
{
    Bytes res(*this);
    res <<= b;
    return res;
}

inline Bytes & Bytes::operator++()
{
    *this += 1;
    return *this;
}

inline Bytes Bytes::operator++(int)
{
    Bytes res(*this);
    ++(*this);
    return res;
}

inline Bytes & Bytes::operator--()
{
    *this -= 1;
    return *this;
}

inline Bytes Bytes::operator--(int)
{
    Bytes res(*this);
    --(*this);
    return res;
}

inline Bytes & Bytes::operator+=(const Bytes & b)
{
    bytes::arithmetic::Addition::Operator(GetPointer(), GetSegment(), 
        b.GetSegment());
    return *this;
}

inline Bytes Bytes::operator+(const Bytes & b) const
{
    Bytes res(*this);
    res += b;
    return res;
}

inline Bytes & Bytes::operator-=(const Bytes & b)
{
    bytes::arithmetic::Subtraction::Operator(GetSegment(), b.GetSegment());
    return *this;
}

inline Bytes Bytes::operator-(const Bytes & b) const
{
    Bytes res(*this);
    res -= b;
    return res;
}

inline Bytes & Bytes::operator*=(const Bytes & b)
{
    bytes::arithmetic::Multiplication::Operator(GetPointer(),
        GetSegment(), b.GetSegment());
    return *this;
}

inline Bytes Bytes::operator*(const Bytes & b) const
{
    Bytes res(*this);
    res *= b;
    return res;
}

inline Bytes & Bytes::operator/=(const Bytes & b)
{
    bytes::arithmetic::Division::Operator(GetPointer(),
        GetSegment(), b.GetSegment());
    return *this;
}

inline Bytes Bytes::operator/(const Bytes & b) const
{
    Bytes res(*this);
    res /= b;
    return res;
}

inline Bytes & Bytes::operator%=(const Bytes & b)
{
    bytes::arithmetic::Modulo::Operator(GetPointer(),
        GetSegment(), b.GetSegment());
}

inline Bytes Bytes::operator%(const Bytes & b) const
{
    Bytes res(*this);
    res %= b;
    return res;
}

Byte Bytes::operator[](const std::size_t & i)
{
    return At(i);
}

const Byte Bytes::operator[](const std::size_t & i) const
{
    return At(i);
}

inline bool Bytes::operator==(const Bytes & b) const
{
    return bytes::Comparison::Operation(GetSegment(), b.GetSegment()) == 0;
}

inline bool Bytes::operator!=(const Bytes & b) const
{
    return !(*this == b);
}

inline bool Bytes::operator<(const Bytes & b) const
{
    return bytes::Comparison::Operation(GetSegment(), b.GetSegment()) < 0;
}

inline bool Bytes::operator<=(const Bytes & b) const
{
    return bytes::Comparison::Operation(GetSegment(), b.GetSegment()) <= 0;
}

inline bool Bytes::operator>(const Bytes & b) const
{
    return bytes::Comparison::Operation(GetSegment(), b.GetSegment()) > 0;
}

inline bool Bytes::operator>=(const Bytes & b) const
{
    return bytes::Comparison::Operation(GetSegment(), b.GetSegment()) >= 0;
}

inline void Bytes::Swap(Bytes & b)
{
    Base::Swap(b);
}

#endif //!BYTES_H_
