#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "List.h"

int main()
{
    List<std::string> list;
    list.append("aboba");
    list.append("bobao");
    list.append("pshh-pshh");
    list.print();
    ++list.begin();

    return 0;
}