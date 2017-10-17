#include "XCounter.h"

void XCounter::operator++()
{
	(*numbers)++;
	for (int i = 1; i < LONG_NUM; i++)
	{
		if (numbers[i - 1]) { return; }
		numbers[i]++;
	}
}
