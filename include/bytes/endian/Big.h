#ifndef BYTES_ENDIAN_BIG_H_
#define BYTES_ENDIAN_BIG_H_

#include <cstdint>

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
    inline std::size_t At(const std::size_t & i, const std::size_t & s) const;
};

inline const Big & Big::Instance()
{
    static Big instance;
    return instance;
}

inline Big::Big() :
    bytes::Endian(bytes::Endian::big)
{}

inline std::size_t Big::At(const std::size_t & i, const std::size_t & s) const
{
    return (s - ((i % s) + 1)) % s;
}

} //!endian

} //!bytes

#endif //!BYTES_ENDIAN_BIG_H_
