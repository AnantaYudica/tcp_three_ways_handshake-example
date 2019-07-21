#ifndef BYTES_PTR_SEGMENT_H_
#define BYTES_PTR_SEGMENT_H_

#include <cstdint>
#include <utility>

namespace bytes
{
namespace ptr
{

class Segment
{
private:
    std::size_t m_begin;
    std::size_t m_end;
public:
    inline Segment();
    inline Segment(const std::size_t & bg, const std::size_t & ed);
    inline ~Segment();
public:
    inline Segment(const Segment & cpy);
    inline Segment(Segment && mov);
public:
    inline Segment & operator=(const Segment & cpy);
    inline Segment & operator=(Segment && mov);
public:
    inline std::size_t Begin() const;
    inline void Begin(const std::size_t & bg);
public:
    inline std::size_t End() const;
    inline void End(const std::size_t & ed);
public:
    inline std::size_t Size() const;
public:
    inline void Resize(const std::size_t & i, const std::size_t & s,
        const std::size_t & ns);
public:
    inline operator bool() const;
public:
    inline bool operator==(const Segment & b) const;
    inline bool operator==(const std::pair<std::size_t, 
        std::size_t> & b) const;
public:
    inline bool operator!=(const Segment & b) const;
    inline bool operator!=(const std::pair<std::size_t, 
        std::size_t> & b) const;
};

inline Segment::Segment() :
    m_begin(0),
    m_end(0)
{}

inline Segment::Segment(const std::size_t & bg, const std::size_t & ed) :
    m_begin(bg),
    m_end(ed)
{}

inline Segment::~Segment()
{
    m_begin = 0;
    m_end = 0;
}

inline Segment::Segment(const Segment & cpy) :
    m_begin(cpy.m_begin),
    m_end(cpy.m_end)
{}

inline Segment::Segment(Segment && mov) :
    m_begin(mov.m_begin),
    m_end(mov.m_end)

{
    mov.m_begin = 0;
    mov.m_end = 0;
}

inline Segment & Segment::operator=(const Segment & cpy)
{
    m_begin = cpy.m_begin;
    m_end = cpy.m_end;
    return *this;
}

inline Segment & Segment::operator=(Segment && mov)
{
    m_begin = mov.m_begin;
    m_end = mov.m_end;
    mov.m_begin = 0;
    mov.m_end = 0;
    return *this;
}

inline std::size_t Segment::Begin() const
{
    return m_begin;
}

inline void Segment::Begin(const std::size_t & bg)
{
    m_begin = bg;
}

inline std::size_t Segment::End() const
{
    return m_end;
}

inline void Segment::End(const std::size_t & ed)
{
    m_end = ed;
}

inline std::size_t Segment::Size() const
{
    return m_end - m_begin;
}

inline void Segment::Resize(const std::size_t & i, const std::size_t & s,
    const std::size_t & ns)
{
    if (s == ns) return;
    const bool isinc = s < ns;
    const std::size_t d = (isinc ? ns - s : s - ns);
    const bool isbg  = Begin() > (i + d), ised = End() > (i + d);
    if (isbg && isinc)
        Begin(Begin() + d);
    else if(isbg && !isinc) 
        Begin(Begin() - d);
    if (ised && isinc)
        End(End() + d);
    else if (ised && !isinc)
        End(End() - d);
}

inline Segment::operator bool() const
{
    return Begin() != End();
}

inline bool Segment::operator==(const Segment & b) const
{
    return m_begin == b.m_begin && m_end == b.m_end;
}

inline bool Segment::operator==(const std::pair<std::size_t, 
    std::size_t> & b) const
{
    return m_begin == b.first && m_end == b.second;
}

inline bool Segment::operator!=(const Segment & b) const
{
    return !(*this == b);
}

inline bool Segment::operator!=(const std::pair<std::size_t, 
    std::size_t> & b) const
{
    return !(*this == b);
}

} //!ptr

} //!bytes

#endif //!BYTES_PTR_SEGMENT_H_
