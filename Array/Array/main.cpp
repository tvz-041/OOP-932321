#include <iostream>

#include "Array.h"

int main()
{
    std::cout << "main-begin\n";
    Array arr;

    try
    {

        int a = arr[3];
        arr[4] = a;
        arr[0] = arr[5];
    }
    catch (...)
    {
        std::cout << "main-catch: ?" << "\n";
    }

    std::cout << "main-end\n";
    return 0;
}