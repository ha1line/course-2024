#ifndef BIDIR_ITERATOR_H
#define BIDIR_ITERATOR_H

#include <iterator>
#include <vector>
#include <string>

template <typename T>
class dummy_bidirectional_iterator
{
public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    dummy_bidirectional_iterator() : m_value(nullptr)
    {}

    dummy_bidirectional_iterator(pointer value) : m_value(value)
    {}

    reference operator*()
    {
        return *m_value;
    }

    pointer operator->()
    {
        return m_value;
    }

    dummy_bidirectional_iterator operator++(int)
    {
        auto temp = *this;
        ++m_value;
        return temp;
    }

    dummy_bidirectional_iterator& operator++()
    {
        ++m_value;
        return *this;
    }

    dummy_bidirectional_iterator operator--(int)
    {
        auto temp = *this;
        --m_value;
        return temp;
    }

    dummy_bidirectional_iterator& operator--()
    {
        --m_value;
        return *this;
    }

    bool operator==(const dummy_bidirectional_iterator& other)
    {
        return m_value == other.m_value;
    }

    bool operator!=(const dummy_bidirectional_iterator& other)
    {
        return !(m_value == other.m_value);
    }
private:
    pointer m_value;
};


#endif // !BIDIR_ITERATOR_H
