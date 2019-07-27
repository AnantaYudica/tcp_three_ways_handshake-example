#ifndef BYTES_ENDIAN_LITTLE_H_
#define BYTES_ENDIAN_LITTLE_H_

#include <cstdint>
#include <cstring>
#include <algorithm>

#include "../Endian.h"

namespace bytes
{
namespace endian
{

class Little : public bytes::Endian
{
public:
    static inline Little & Instance();
public:
    inline Little();
    inline ~Little() = default;
public:
    inline Little(const Little & cpy) = delete;
    inline Little(Little && mov) = delete;
public:
    inline Little & operator=(const Little & cpy) = delete;
    inline Little & operator=(Little && mov) = delete;
public:
    inline std::size_t At(const std::size_t & i, const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline std::size_t Begin(const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline std::size_t End(const std::size_t & bg, 
        const std::size_t & ed) const;
public:
    inline void Copy(std::uint8_t * a, const std::size_t & as,
        const std::uint8_t * b, const std::size_t & bs) const;
};

inline Little & Little::Instance()
{
    static Little instance;
    return instance;
}

inline Little::Little() :
    bytes::Endian(bytes::Endian::little)
{}

inline std::size_t Little::At(const std::size_t & i, const std::size_t & bg, 
        const std::size_t & ed) const
{
    return bg + i;
}

inline std::size_t Little::Begin(const std::size_t & bg, 
    const std::size_t & ed) const
{
    return bg;
}

inline std::size_t Little::End(const std::size_t & bg, 
    const std::size_t & ed) const
{
    return ed;
}

inline void Little::Copy(std::uint8_t * a, const std::size_t & as,
    const std::uint8_t * b, const std::size_t & bs) const
{
    if (!a || !b || as == 0 || bs == 0) return;
    std::memcpy(a, b, std::min(as, bs));
}

} //!endian

} //!bytes

#endif //!BYTES_ENDIAN_LITTLE_H_
