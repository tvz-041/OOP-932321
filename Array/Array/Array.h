#pragma once

#include <assert.h>
#include <iostream>
#include <utility>

#undef DEBUG_OUTPUT

template <typename ItemType>
class Array
{
public:
    Array(int size = 10);
    Array(const Array& other);
    Array(Array&& other);
    ~Array();
    
    int size() const;

    bool insert(const int index, const ItemType& value);
    void swap(Array& other) noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    ItemType& operator[](int index);
    const ItemType& operator[](int index) const;
    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);

private:
    ItemType* m_array = nullptr;
    int m_size = 0;
};

template <typename ItemType>
Array<ItemType>::Array(int size)
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::Array() \n";
#endif // DEBUG_OUTPUT
    if (size < 0)
    {
        size = -size;
    }
    m_size = size;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = ItemType();
    }
#ifdef DEBUG_OUTPUT
    std::cout << "m_array: " << m_array << " \n";
#endif // DEBUG_OUTPUT
}

template <typename ItemType>
Array<ItemType>::Array(const Array& other)
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::Array(const Array& other) \n";
    std::cout << "other: " << &other << " \n";
#endif // DEBUG_OUTPUT
    m_size = other.m_size;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
#ifdef DEBUG_OUTPUT
    std::cout << "m_array: " << m_array << " \n";
#endif // DEBUG_OUTPUT
}

template <typename ItemType>
Array<ItemType>::Array(Array&& other)
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::Array(Array&& other) \n";
    std::cout << "other: " << &other << " \n";
#endif // DEBUG_OUTPUT
    m_size = other.m_size;
    m_array = other.m_array;
    other.m_array = nullptr;
}

template <typename ItemType>
Array<ItemType>::~Array()
{
#ifdef DEBUG_OUTPUT
    std::cout << this << ": " << "Array::~Array() \n";
    std::cout << "m_array: " << m_array << " \n";
#endif // DEBUG_OUTPUT
    delete[] m_array;
}

template <typename ItemType>
int Array<ItemType>::size() const
{
    return m_size;
}

template <typename ItemType>
bool Array<ItemType>::insert(const int index, const ItemType& value)
{
    if (index < 0 || index >= m_size)
    {
        return false;
    }

    ItemType* newArray = new ItemType[m_size + 1];
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
//template <typename ItemType>
//Array& Array<ItemType>::operator=(const Array& other)
//{
//    if (this == &other)
//    {
//        return *this;
//    }
//
//    m_size = other.m_size;
//    delete[] m_array;
//    ItemType* newArr = new ItemType[m_size];
//    for (int i = 0; i < m_size; ++i)
//    {
//        newArr[i] = other.m_array[i];
//    }
//    m_array = newArr;
//    return *this;
//}

// "copy-and-swap" assign
template <typename ItemType>
void Array<ItemType>::swap(Array& other) noexcept
{
    std::swap(m_size, other.m_size);
    std::swap(m_array, other.m_array);
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array& other)
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

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(Array&& other) noexcept
{
    std::cout << this << ": " << "Array::operator=(Array&& other) begin \n";
    std::cout << "other: " << &other << " \n";
    swap(other); 
    std::cout << this << ": " << "Array::operator=(Array&& other) end \n";
    return *this;
}

template <typename ItemType>
ItemType& Array<ItemType>::operator[](int index)
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
const ItemType& Array<ItemType>::operator[](int index) const
{
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array& other) const
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

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const Array& other)
{
    operator+(other).swap(*this);
    return *this;
}
