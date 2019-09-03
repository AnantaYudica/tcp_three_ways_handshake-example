#ifndef BYTES_ENDIAN_H_
#define BYTES_ENDIAN_H_

#include <cstdint>
#include <cstddef>

namespace bytes
{

class Endian
{
public:
    enum CategoryEnum : uint8_t
    {
        little = 1,
        big = 2
    };
private:
    CategoryEnum m_category;
protected:
    inline Endian(const CategoryEnum & c);
public:
    virtual ~Endian() = default;
public:
    inline Endian(const Endian & cpy) = delete;
    inline Endian(Endian && mov) = delete;
public:
    inline Endian & operator=(const Endian & cpy) = delete;
    inline Endian & operator=(Endian && mov) = delete;
public:
    virtual std::size_t At(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual std::size_t ReverseAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual std::size_t Begin(const std::size_t & bg, 
        const std::size_t & ed) const = 0;
public:
    virtual std::size_t End(const std::size_t & bg, 
        const std::size_t & ed) const = 0;
public:
    virtual std::uint8_t ValueAt(const std::uint8_t & v_at_0, 
        const std::uint8_t & v_at_1, const std::uint8_t & off) const = 0;
public:
    virtual void ValueAt(std::uint8_t & v_at_0, 
        std::uint8_t & v_at_1, const std::uint8_t & v_in, 
        const std::uint8_t & off) const = 0;
public:
    virtual std::uint8_t ValueReverseAt(const std::uint8_t & v_reverse_at_0, 
        const std::uint8_t & v_reverse_at_1, 
        const std::uint8_t & off) const = 0;
public:
    virtual void ValueReverseAt(std::uint8_t & v_reverse_at_0, 
        std::uint8_t & v_reverse_at_1, const std::uint8_t & v_in, 
        const std::uint8_t & off) const = 0;
public:
    virtual void Copy(std::uint8_t * a, const std::size_t & as,
        const std::uint8_t * b, const std::size_t & bs) const = 0;
public:
    inline Endian::CategoryEnum Category() const;
public:
    inline bool operator==(const Endian & b) const;
    inline bool operator!=(const Endian & b) const;
};

inline Endian::Endian(const CategoryEnum & c) :
    m_category(c)
{}

inline Endian::CategoryEnum Endian::Category() const
{
    return m_category;
}

inline bool Endian::operator==(const Endian & b) const
{
    return m_category == b.m_category;
}

inline bool Endian::operator!=(const Endian & b) const
{
    return !(*this == b);
}

} //!bytes

#endif //!BYTES_ENDIAN_H_
