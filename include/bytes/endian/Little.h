#ifndef BYTES_ENDIAN_LITTLE_H_
#define BYTES_ENDIAN_LITTLE_H_

#include <cstdint>
#include <cstring>
#include <algorithm>

#include "../Endian.h"
#include "../../byte/Mask.h"

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
    inline std::uint8_t ValueAt(const std::uint8_t & v_at_0, 
        const std::uint8_t & v_at_1, const std::uint8_t & off,
        const std::uint8_t & sz = 8) const;
public:
    inline void ValueAt(std::uint8_t & v_at_0, 
        std::uint8_t & v_at_1, const std::uint8_t & v_in, 
        const std::uint8_t & off, const std::uint8_t & sz = 8) const;
public:
    inline std::uint8_t ValueReverseAt(const std::uint8_t & v_reverse_at_0, 
        const std::uint8_t & v_reverse_at_1, 
        const std::uint8_t & off, const std::uint8_t & sz = 8) const;
public:
    inline void ValueReverseAt(std::uint8_t & v_reverse_at_0, 
        std::uint8_t & v_reverse_at_1, const std::uint8_t & v_in, 
        const std::uint8_t & off, const std::uint8_t & sz = 8) const;
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

inline std::uint8_t Little::ValueAt(const std::uint8_t & v_reverse_at_0, 
    const std::uint8_t & v_reverse_at_1, const std::uint8_t & off,
    const std::uint8_t & sz) const
{
    const std::int8_t size = std::int8_t(sz > 8 ? 0 : sz), 
        inv_size = std::int8_t(8 - size);
    if (off == 0) return v_reverse_at_0 & byte::Mask(0xFF, -inv_size);
    else if (off == 8) return v_reverse_at_1 & byte::Mask(0xFF, -inv_size);
    else if (off >= 16) return std::uint8_t(0);
    else if (off > 8) return (v_reverse_at_1 >> (off % 8)) &
        byte::Mask(0xFF, -inv_size);
    else return ((v_reverse_at_0 >> off) |
        (v_reverse_at_1 << 8 - off)) & byte::Mask(0xFF, -inv_size);
}

inline void Little::ValueAt(std::uint8_t & v_reverse_at_0, 
    std::uint8_t & v_reverse_at_1, const std::uint8_t & v_in, 
    const std::uint8_t & off, const std::uint8_t & sz) const
{
    const std::int8_t size = std::int8_t(sz > 8 ? 0 : sz), 
        inv_size = std::int8_t(8 - size);
    if (off == 0) v_reverse_at_0 = (v_reverse_at_0 & byte::Mask(0xFF, size)) | 
        (v_in & byte::Mask(0xFF, -inv_size));
    else if (off == 8) v_reverse_at_1 = 
        (v_reverse_at_1 & byte::Mask(0xFF, size)) | 
        (v_in & byte::Mask(0xFF, -inv_size));
    else if (off >= 16) return;
    else if (off > 8) 
    {
        const std::int8_t inv_off = 8 - (off % 8);
        if (inv_off > size)
            v_reverse_at_1 = (v_reverse_at_1 & byte::Mask(0xFF, -inv_off)) | 
                (v_reverse_at_1 & byte::Mask(0xFF, (off + size))) |
                (v_in << (off % 8) & byte::Mask(0xFF, -inv_size));
        else
            v_reverse_at_1 = (v_reverse_at_1 & byte::Mask(0xFF, -inv_off)) |
                (v_in << (off % 8) & byte::Mask(0xFF, -inv_size));
    }
    else
    {
        const std::uint8_t inv_off = std::uint8_t(8) - off;
        if (inv_off > size)
            v_reverse_at_0 = (v_reverse_at_0 & 
                byte::Mask(0xFF, -int(inv_off))) |
                (v_reverse_at_0 & byte::Mask(0xFF, (off + size))) |
                ((v_in << off) & byte::Mask(0xFF, -inv_size));
        else
        {
            const std::uint8_t rem_size = size - inv_off,
                inv_rem_size = std::uint8_t(8) - rem_size;
            v_reverse_at_0 = (v_reverse_at_0 & 
                byte::Mask(0xFF, -int(inv_off))) | (v_in << off);
            v_reverse_at_1 = (v_reverse_at_1 & byte::Mask(0xFF, rem_size)) |
                ((v_in >> inv_off) & byte::Mask(0xFF, -inv_rem_size));
        }
    }
}

inline std::uint8_t Little::ValueReverseAt(const std::uint8_t & v_at_0, 
    const std::uint8_t & v_at_1, const std::uint8_t & off, 
    const std::uint8_t & sz) const
{
    const std::int8_t size = std::int8_t(sz > 8 ? 0 : sz), 
        inv_size = std::int8_t(8 - size);
    if (off == 0) return v_at_0 & byte::Mask(0xFF, -inv_size);
    else if (off == 8) return v_at_1 & byte::Mask(0xFF, -inv_size);
    else if (off >= 16) return std::uint8_t(0);
    else if (off > 8) return (v_at_1 << (off % 8)) >> size;
    else return ((v_at_0 << off) | (v_at_1 >> (8 - off))) >> size;
}

inline void Little::ValueReverseAt(std::uint8_t & v_at_0, 
    std::uint8_t & v_at_1, const std::uint8_t & v_in, 
    const std::uint8_t & off, const std::uint8_t & sz) const
{
    const std::int8_t size = std::int8_t(sz > 8 ? 0 : sz), 
        inv_size = std::int8_t(8 - size);
    if (off == 0) v_at_0 = (v_at_0 & byte::Mask(0xFF, size)) |
        (v_in & byte::Mask(0xFF, -inv_size));
    else if (off == 8) v_at_1 = (v_at_1 & byte::Mask(0xFF, size)) |
        (v_in & byte::Mask(0xFF, -inv_size));
    else if (off >= 16) return;
    else if (off > 8) 
    {
        const std::int8_t inv_off = 8 - (off % 8);
        if (inv_off > size)
            v_at_1 = (v_at_1 & byte::Mask(0xFF, inv_off)) | 
                (v_at_1 & byte::Mask(0xFF, -int(off + size))) |
                (((v_in >> off) << inv_size) & byte::Mask(0xFF, inv_off));
        else
            v_at_1 = (v_at_1 & byte::Mask(0xFF, inv_off)) | 
                (v_in >> off);
    }
    else 
    {
        const std::uint8_t inv_off = std::uint8_t(8) - off;
        if (inv_off > size)
            v_at_0 = (v_at_0 & byte::Mask(0xFF, inv_off)) |
                (v_at_0 & byte::Mask(0xFF, -int(off + size))) |
                ((v_in << off) & byte::Mask(0xFF, inv_off));
        else
        {
            const std::uint8_t rem_size = size - inv_off,
                inv_rem_size = std::uint8_t(8) - rem_size;
            v_at_0 = (v_at_0 & byte::Mask(0xFF, inv_off)) |
                (v_in >> off);
            v_at_1 = (v_at_1 & byte::Mask(0xFF, -int(rem_size))) |
                ((v_in << inv_off) & byte::Mask(0xFF, inv_rem_size));
        }
    }
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
