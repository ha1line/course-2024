#include <algorithm>
#include <iostream>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
#include "random_access_iterator.h"

class dummy_string
{
public:
    using iterator = dummy_random_access_iterator<char>;
    using const_iterator = const dummy_random_access_iterator<char>;

    dummy_string() : m_size(0), m_data(nullptr)
    {
    }

    dummy_string(const char* tmp)
    {
       m_size = std::strlen(tmp);
       m_data = new char[m_size + 1];
       std::memcpy(m_data, tmp, m_size);
       m_data[m_size] = '\0';
    }

    dummy_string(const dummy_string& other)
    {
        m_size = other.m_size;
        m_data = new char[m_size + 1];
        std::memcpy(m_data, other.m_data, m_size + 1);
    }

    ~dummy_string()
    {
        Clear();
    }

    char& operator[](size_t index) noexcept
    {
        return m_data[index];
    }

    const char& operator[](size_t index) const noexcept
    {
        return m_data[index];
    }

    char& at(size_t index)
    {
        if (index >= m_size)
        {
            throw std::out_of_range("index out of range");
        }
        return m_data[index];
    }

    const char& at(size_t index) const
    {
        if (index >= m_size)
        {
            throw std::out_of_range("index out of range");
        }
        return m_data[index];
    }

    dummy_string& operator=(const dummy_string& other)
    {
        if (this != &other)
        {
            dummy_string copy(other);
            std::swap(m_data, copy.m_data);
            std::swap(m_size, copy.m_size);
        }
        return *this;
    }

    bool operator==(const dummy_string& other) const noexcept
    {
        if (m_size != other.m_size)
        {
            return false;
        }
        return std::memcmp(m_data, other.m_data, other.m_size) == 0;
    }

    bool operator!=(const dummy_string& other) const noexcept
    {
        return !(*this == other);
    }

    bool operator<(const dummy_string& other) const noexcept
    {
        return std::lexicographical_compare(m_data, m_data + m_size, other.m_data,
            other.m_data + other.m_size);
    }

    bool operator>(const dummy_string& other) const noexcept
    {
        return other < *this;
    }

    size_t Size() const noexcept
    {
        return m_size;
    }

    void Clear() noexcept
    {
        m_size = 0;
        delete[] m_data;
        m_data = nullptr;
    }

    const char* C_str() const noexcept
    {
        return m_data;
    }

    iterator begin()
    {
        return iterator(m_data);
    }

    iterator end()
    {
        return iterator(m_data + m_size);
    }
private:
    size_t m_size;
    char* m_data;
};

int main()
{
    {
        const char* str = "Hello, World!";
        dummy_string dstr(str);
        std::cout << dstr.C_str() + dstr.Size() - 1 << std::endl;
    }
    {
        std::cout << "new" << std::endl;
        std::vector<std::string> vec = {"first", "second", "third"};
        dummy_random_access_iterator<std::string> begin(vec.data());
        dummy_random_access_iterator<std::string> end(vec.data() + vec.size());
        for (auto it = begin; it != end; ++it)
        {
            std::cout << *it << std::endl;
        }
    }
}
