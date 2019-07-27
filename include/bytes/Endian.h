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
    virtual inline std::size_t At(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const = 0;
public:
    virtual inline std::size_t Begin(const std::size_t & bg, 
        const std::size_t & ed) const = 0;
public:
    virtual inline std::size_t End(const std::size_t & bg, 
        const std::size_t & ed) const = 0;
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
