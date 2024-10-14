#include <iostream>

#include "Array.h"

int main()
{
    std::cout << "main begin \n";
    Array<int> a, b;
    Array<int> c = a += b;
    Array<int> f = std::move(b);
    for (int i = 0; i < a.size(); ++i)
    {
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
    std::cout << "main end \n";
    return 0;
}