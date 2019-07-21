#ifndef BYTES_PTR_COUNTER_H_
#define BYTES_PTR_COUNTER_H_

#include <cstdint>
#include <utility>

namespace bytes
{
namespace ptr
{

template<typename T>
class Counter
{
private:
    std::size_t m_count;
    T m_data;
public:
    inline Counter(const T & t);
    inline ~Counter();
public:
    inline Counter(const Counter<T> & cpy);
    inline Counter(Counter<T> && mov);
public:
    inline Counter<T> & operator=(const Counter<T> & cpy);
    inline Counter<T> & operator=(Counter<T> && mov);
public:
    inline operator bool() const;
public:
    inline T & Get();
    inline const T & Get() const;
public:
    inline Counter<T> & operator++();
    inline Counter<T> operator++(int);
public:
    inline Counter<T> & operator--();
    inline Counter<T> operator--(int);
};

template<typename T>
inline Counter<T>::Counter(const T & t) :
    m_count(1),
    m_data(t)
{}

template<typename T>
inline Counter<T>::~Counter()
{
    m_count = 0;
}

template<typename T>
inline Counter<T>::Counter(const Counter<T> & cpy) :
    m_count(cpy.m_count),
    m_data(cpy.m_data)
{}

template<typename T>
inline Counter<T>::Counter(Counter<T> && mov) :
    m_count(mov.m_count),
    m_data(std::move(mov.m_data))
{
    mov.m_count = 0;
}

template<typename T>
inline Counter<T> & Counter<T>::operator=(const Counter<T> & cpy)
{
    m_count = cpy.m_count;
    m_data = cpy.m_data;
}

template<typename T>
inline Counter<T> & Counter<T>::operator=(Counter<T> && mov)
{
    m_count = mov.m_count;
    m_data = std::move(mov.m_data);
    mov.m_count = 0;
}

template<typename T>
inline Counter<T>::operator bool() const
{
    return m_count > 0;
}

template<typename T>
inline T & Counter<T>::Get()
{
    return m_data;
}

template<typename T>
inline const T & Counter<T>::Get() const
{
    return m_data;
}

template<typename T>
inline Counter<T> & Counter<T>::operator++()
{
    ++m_count;
    return *this;
}

template<typename T>
inline Counter<T> Counter<T>::operator++(int)
{
    Counter<T> res(*this);
    ++(*this);
    return res;
}

template<typename T>
inline Counter<T> & Counter<T>::operator--()
{
    --m_count;
    return *this;
}

template<typename T>
inline Counter<T> Counter<T>::operator--(int)
{
    Counter<T> res(*this);
    --(*this);
    return res;
}

} //!ptr

} //!bytes

#endif //!BYTES_PTR_COUNTER_H_
