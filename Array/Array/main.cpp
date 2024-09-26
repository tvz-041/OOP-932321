#include <iostream>

#include "Array.h"

int main()
{
    std::cout << "main begin \n";
    Array a, b;
    Array c = a += b;
    Array f = std::move(b);
    std::cout << "main end \n";
    return 0;
}