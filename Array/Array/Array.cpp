#include <assert.h>

#include "Array.h"

Array::Array(int size)
{
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
}

Array::~Array()
{
    delete[] m_array;
}

bool Array::insert(const int index, const int& value)
{
    if (index < 0 || index >= m_size)
        return false;

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

inline Array::Array(const Array& other)
{
    m_size = other.m_size;
    m_array = new int[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_array[i] = other.m_array[i];
    }
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