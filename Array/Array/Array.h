#pragma once

class Array
{
public:
    Array(int size = 10);
    Array(const Array& other);
    Array(Array&& other);
    ~Array();

    bool insert(const int index, const int& value);
    void swap(Array& other) noexcept;

    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    int& operator[](int index);
    const int& operator[](int index) const;
    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);

private:
    int* m_array = nullptr;
    int m_size = 0;
};
