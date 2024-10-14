#include <algorithm>
#include <iostream>

#include "Array.h"

int main()
{
    std::cout << "main begin \n";
    Array<int> a, b;
    Array<int> c = a += b;
    Array<int> f = std::move(b);
    a[4] = 8;
    a.begin()[5] = 3;
    auto it = a.end() - 1;
    *it = 4;
    for (int val : a)
    {
        std::cout << val << ' ';
        //0 0 0 0 8 3 0 0 0 0 0 0 0 0 0 0 0 0 0 4 
    }
    std::sort(a.begin(), a.begin() + a.size() / 2);
    for (int val : a)
    {
        std::cout << val << ' ';
        //0 0 0 0 0 0 0 0 3 8 0 0 0 0 0 0 0 0 0 4
    }
    it = std::find(a.begin(), a.end(), 3);
    if (it != a.end())
    {
        std::cout << '\n' << it - a.begin(); //8
    }
    
    std::cout << '\n';
    std::cout << "main end \n";
    return 0;
}