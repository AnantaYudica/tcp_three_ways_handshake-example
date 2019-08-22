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
    inline std::size_t ReverseAt(const std::size_t & i, 
        const std::size_t & bg, const std::size_t & ed) const;
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
    return (ed - 1) - i;
}

inline std::size_t Little::ReverseAt(const std::size_t & i, 
    const std::size_t & bg, const std::size_t & ed) const
{
    return bg + i;
}

inline std::size_t Little::Begin(const std::size_t & bg, 
    const std::size_t & ed) const
{
    return ed - 1;
}

inline std::size_t Little::End(const std::size_t & bg, 
    const std::size_t & ed) const
{
    return bg - 1;
}

inline void Little::Copy(std::uint8_t * a, const std::size_t & as,
    const std::uint8_t * b, const std::size_t & bs) const
{
    if (!a || !b || as == 0 || bs == 0) return;
    const std::size_t ad = bs > as ? 0 : as - bs,
        bd = bs > as ? bs - as : 0;
    std::memcpy(a + ad, b + bs, std::min(as, bs));
}

} //!endian

} //!bytes

#endif //!BYTES_ENDIAN_LITTLE_H_
