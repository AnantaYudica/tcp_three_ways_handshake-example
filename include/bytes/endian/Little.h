#ifndef BYTES_ENDIAN_LITTLE_H_
#define BYTES_ENDIAN_LITTLE_H_

#include <cstdint>

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
    inline std::size_t At(const std::size_t & i, const std::size_t & s) const;
};

inline Little & Little::Instance()
{
    static Little instance;
    return instance;
}

inline Little::Little() :
    bytes::Endian(bytes::Endian::little)
{}

inline std::size_t Little::At(const std::size_t & i, const std::size_t & s) const
{
    return i % s;
}

} //!endian

} //!bytes

#endif //!BYTES_ENDIAN_LITTLE_H_
