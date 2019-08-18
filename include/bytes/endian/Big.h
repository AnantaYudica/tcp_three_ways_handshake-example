#ifndef BYTES_ENDIAN_BIG_H_
#define BYTES_ENDIAN_BIG_H_

#include <cstdint>
#include <cstring>
#include <algorithm>

#include "../Endian.h"

namespace bytes
{
namespace endian
{

class Big : public bytes::Endian
{
public:
    static inline const Big & Instance();
public:
    inline Big();
    inline ~Big() = default;
public:
    inline Big(const Big & cpy) = delete;
    inline Big(Big && mov) = delete;
public:
    inline Big & operator=(const Big & cpy) = delete;
    inline Big & operator=(Big && mov) = delete;
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

inline const Big & Big::Instance()
{
    static Big instance;
    return instance;
}

inline Big::Big() :
    bytes::Endian(bytes::Endian::big)
{}

inline std::size_t Big::At(const std::size_t & i, const std::size_t & bg, 
        const std::size_t & ed) const
{
    return (ed - 1) - i;
}

inline std::size_t Big::Begin(const std::size_t & bg, 
    const std::size_t & ed) const
{
    return ed - 1;
}

inline std::size_t Big::End(const std::size_t & bg, 
    const std::size_t & ed) const
{
    return bg - 1;
}

inline void Big::Copy(std::uint8_t * a, const std::size_t & as,
    const std::uint8_t * b, const std::size_t & bs) const
{
    if (!a || !b || as == 0 || bs == 0) return;
    const std::size_t ad = bs > as ? 0 : as - bs,
        bd = bs > as ? bs - as : 0;
    std::memcpy(a + ad, b + bs, std::min(as, bs));
}

} //!endian

} //!bytes

#endif //!BYTES_ENDIAN_BIG_H_
