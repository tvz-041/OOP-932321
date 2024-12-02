#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "List.h"

template <typename T>
void printSearchResult(const List<T>& list, const T& value)
{
    auto it = std::find(list.begin(), list.end(), value);
    std::cout << "list ";
    if (it == list.end())
    {
        std::cout << "doesn't contain ";
    }
    else
    {
        std::cout << "contains ";
    }
    std::cout << "'" << value << "' value.\n";
}

int main()
{
    List<std::string> list;
    list.append("aboba");
    list.append("bobao");
    list.append("pshh-pshh");
    list.print();
    ++list.begin();
    
    printSearchResult(list, {"boba"});
    printSearchResult(list, {"bobao"});
    printSearchResult(list, {"b"});
    
    List<int> list2;
    list2.append(10);
    list2.append(-4);
    list2.append(0);
    list2.append(1);
    printSearchResult(list2, 10);
    printSearchResult(list2, 5);
    printSearchResult(list2, -1);
    
    
    return 0;
}
