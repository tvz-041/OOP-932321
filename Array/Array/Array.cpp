#include <assert.h>
#include <iostream>
#include <utility>

#include "Array.h"

#define DEBUG_OUTPUT

Array::Array(int size)
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::Array() \n";
#endif // DEBUG_OUTPUT
    if (size < 0)
    {
        size = -size;
    }
    m_size = size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = 0;
    }
#ifdef DEBUG_OUTPUT
    std::cout << "m_array: " << m_array << " \n";
#endif // DEBUG_OUTPUT
}

Array::Array(const Array& other)
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::Array(const Array& other) \n";
    std::cout << "other: " << &other << " \n";
#endif // DEBUG_OUTPUT
    m_size = other.m_size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
#ifdef DEBUG_OUTPUT
    std::cout << "m_array: " << m_array << " \n";
#endif // DEBUG_OUTPUT
}

Array::Array(Array&& other)
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::Array(Array&& other) \n";
    std::cout << "other: " << &other << " \n";
#endif // DEBUG_OUTPUT
    m_size = other.m_size;
    m_array = other.m_array;
    other.m_array = nullptr;
}

Array::~Array()
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::~Array() \n";
    std::cout << "m_array: " << m_array << " \n";
#endif // DEBUG_OUTPUT
    delete[] m_array;
}

bool Array::insert(const int index, const int& value)
{
    if (index < 0 || index >= m_size)
    {
        return false;
    }

    int* newArray = new int[m_size + 1];
    for (int i = 0; i < index; i++)
    {
        newArray[i] = m_array[i];
    }

    newArray[index] = value;

    for (int i = index + 1; i < m_size + 1; i++)
    {
        newArray[i] = m_array[i - 1];
    }

    delete[] m_array;
    m_array = newArray;
    m_size++;

    return true;
}

// "classic" assign
//Array& Array::operator=(const Array& other)
//{
//    if (this == &other)
//    {
//        return *this;
//    }
//
//    m_size = other.m_size;
//    delete[] m_array;
//    int* newArr = new int[m_size];
//    for (int i = 0; i < m_size; ++i)
//    {
//        newArr[i] = other.m_array[i];
//    }
//    m_array = newArr;
//    return *this;
//}

// "copy-and-swap" assign
void Array::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

Array& Array::operator=(const Array& other)
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::operator=(const Array& other) begin \n";
    std::cout << "other: " << &other << " \n";
#endif // DEBUG_OUTPUT
    if (m_size == other.m_size)
    {
        for (int i = 0; i < m_size; ++i)
        {
            m_array[i] = other.m_array[i];
        }
    }
    else
    {
        Array copy(other);
        swap(copy);
    }

#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::operator=(const Array& other) end \n";
#endif // DEBUG_OUTPUT
    return *this;
}

Array& Array::operator=(Array&& other) noexcept
{
    std::cout << this << ": " << "Array::operator=(Array&& other) begin \n";
    std::cout << "other: " << &other << " \n";
    swap(other); 
    std::cout << this << ": " << "Array::operator=(Array&& other) end \n";
    return *this;
}

int& Array::operator[](int index)
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

const int& Array::operator[](int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

Array Array::operator+(const Array& other) const
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::operator+(const Array& other) begin \n";
    std::cout << "other: " << &other << " \n";
#endif // DEBUG_OUTPUT
    Array result(m_size + other.m_size);
    for (int i = 0; i < m_size; ++i)
    {
        result[i] = m_array[i];
    }
    for (int i = 0; i < other.m_size; ++i)
    {
        result[m_size + i] = other[i];
    }
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::operator+(const Array& other) end \n";
#endif // DEBUG_OUTPUT
    return result;
}

Array& Array::operator+=(const Array& other)
{
    operator+(other).swap(*this);
    return *this;
}