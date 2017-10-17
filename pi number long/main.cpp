#include <iostream>
using namespace std;

#include "XCounter.h"

void getpi(int digits)
{
	LongBase limit = LongBase(1) << digits;
	LongBase limitsqr = (limit*limit);
	LongBase counter, ysqr;
	for (XCounter y; y != limit; ++y)
	{
		LongBase xsqr;
		LongBase xsqrlimit = limitsqr - ysqr;
		for (XCounter x; x != limit; ++x)
		{
			if (xsqr >= xsqrlimit)
			{
				counter = counter + x;
				break;
			}
			xsqr = xsqr + x.ShlOne() + 1;
		}
		ysqr = ysqr + y.ShlOne() + 1;
	}
	cout << ((double)(*(counter << 2).numbers) / (*limitsqr.numbers)) << endl;
	counter.PrintBinary(digits * 2 - 2);
}

int main()
{
	for (int iter = 0; iter <= 9; iter++)
		getpi(5 + iter);
	system("pause");
	return 0;
}