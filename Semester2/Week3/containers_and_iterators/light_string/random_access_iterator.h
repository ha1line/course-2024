#ifndef RANDOM_ACCESS_ITERATOR_H
#define RANDOM_ACCESS_ITERATOR_H

#include <iterator>
#include <vector>
#include <string>
#include <memory>

template <typename T>
class dummy_random_access_iterator
{
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t; // distance
    using pointer = T*;
    using reference = T&;

    dummy_random_access_iterator() : m_value(nullptr)
    {}

    dummy_random_access_iterator(pointer value) : m_value(value)
    {
    }

    dummy_random_access_iterator(const dummy_random_access_iterator& other) = default;

    reference operator*()
    {
        return *m_value;
    }

    pointer operator->()
    {
        return m_value;
    }

    dummy_random_access_iterator operator++(int)
    {
        auto temp = *this;
        ++m_value;
        return temp;
    }

    dummy_random_access_iterator& operator++()
    {
        ++m_value;
        return *this;
    }

    dummy_random_access_iterator operator--(int)
    {
        auto temp = *this;
        --m_value;
        return temp;
    }

    dummy_random_access_iterator& operator--()
    {
        --m_value;
        return *this;
    }


    dummy_random_access_iterator operator+(difference_type idx)
    {
        return dummy_random_access_iterator(m_value + idx);
    }


    dummy_random_access_iterator& operator+=(difference_type idx)
    {
        m_value += idx;
        return *this;
    }

    dummy_random_access_iterator& operator-=(difference_type idx)
    {
        m_value -= idx;
        return *this;
    }

    dummy_random_access_iterator operator-(difference_type idx)
    {
        return dummy_random_access_iterator(m_value - idx);
    }

    reference operator[](difference_type idx)
    {
        return m_value[idx];
    }

    bool operator==(const dummy_random_access_iterator& other)
    {
        return m_value == other.m_value;
    }

    bool operator!=(const dummy_random_access_iterator& other)
    {
        return !(m_value == other.m_value);
    }

    bool operator<(const dummy_random_access_iterator& other)
    {
        return m_value < other.m_value;
    }

    bool operator>(const dummy_random_access_iterator& other)
    {
        return m_value > other.m_value;
    }

    bool operator>=(const dummy_random_access_iterator& other)
    {
        return m_value >= other.m_value;
    }

    bool operator<=(const dummy_random_access_iterator& other)
    {
        return m_value <= other.m_value;
    }
private:
    pointer m_value;
};

#endif // !RANDOM_ACCESS_ITERATOR_H
