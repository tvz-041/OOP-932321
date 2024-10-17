#include <iostream>

#include "BoolVector.h"

int main()
{
	BoolVector bv(14);
	bv.setBitValue(1, true);
	bv.setBitValue(6, true);
	for (int i = 0; i < 14; ++i)
	{
		std::cout << bv.bitValue(i);
		//01000010000000
	}
	return 0;
}