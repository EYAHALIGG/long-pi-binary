#include "LongBase.h"

#include <iostream>

bool LongBase::operator==(const LongBase & val)
{
	for (int i = 0; i < LONG_NUM; i++)
		if (numbers[i] != val.numbers[i])
			return false;
	return true;
}

bool LongBase::operator!=(const LongBase & val)
{
	return !(*this == val);
}

bool LongBase::operator<(const LongBase & val)
{
	for (int i = LONG_NUM - 1; i >= 0; i--)
		if (numbers[i] < val.numbers[i])
			return true;
	return false;
}

bool LongBase::operator<=(const LongBase & val)
{
	return (*this < val) || (*this == val);
}

bool LongBase::operator>(const LongBase & val)
{
	return !(*this <= val);
}

bool LongBase::operator>=(const LongBase & val)
{
	return (*this > val) || (*this == val);
}

LongBase LongBase::operator<<(int shift)
{
	int a = shift / 32;
	int b = shift % 32;
	if (a >= LONG_NUM) { return LongBase(); }
	LongBase ret = *this;
	if (a) { for (int i = LONG_NUM - 1; i >= a; i--) { ret.numbers[i] = numbers[i - a]; ret.numbers[i - a] = 0; } }
	if (b) 
	{
		for (int i = LONG_NUM - 1; i > a; i--) 
		{
			ret.numbers[i] <<= b;
			ret.numbers[i] |= ret.numbers[i - 1] >> (32 - b);
		}
		ret.numbers[a] <<= b;
	}
	return ret;
}

LongBase LongBase::operator>>(int shift)
{
	int a = shift / 32;
	int b = shift % 32;
	if (a >= LONG_NUM) { return LongBase(); }
	LongBase ret = *this;
	if (a) { for (int i = 0; i < LONG_NUM - a; i++) { ret.numbers[i] = ret.numbers[i + a]; ret.numbers[i + a] = 0; } }
	if (b)
	{
		for (int i = 0; i < a; i--)
		{
			ret.numbers[i] >>= b;
			ret.numbers[i] |= ret.numbers[i + 1] << (32 - b);
		}
		ret.numbers[a] >>= b;
	}
	return ret;
}

LongBase LongBase::ShlOne()
{
	LongBase ret;
	for (int i = LONG_NUM - 1; i > 0; i--)
	{
		ret.numbers[i] = numbers[i] << 1;
		ret.numbers[i] |= numbers[i - 1] >> 31;
	}
	ret.numbers[0] = numbers[0] << 1;
	return ret;
}

LongBase LongBase::operator*(const LongBase & val)
{
	LongBase a = *this;
	LongBase b = val;
	LongBase sum;
	while ((a != 0) && (b != 0))
	{
		if ((*b.numbers) & 1) { sum = sum + a; }
		a = a << 1;
		b = b >> 1;
	}
	return sum;
}

LongBase LongBase::operator+(const LongBase & val)
{
	LongBase ret;
	__asm
	{
		clc
		pushf
	}
	for (int i = 0; i < LONG_NUM; i++)
	{
		unsigned a = numbers[i];
		unsigned b = val.numbers[i];
		unsigned r;
		__asm
		{
			popf
			mov eax, dword ptr [a]
			mov edx, dword ptr [b]
			adc eax, edx
			mov dword ptr [r], eax
			pushf
		}
		ret.numbers[i] = r;
	}
	__asm
	{
		popf
	}
	return ret;
}

LongBase LongBase::operator-(const LongBase & val)
{
	return *this + (~LongBase(val) + 1);
}

LongBase LongBase::operator~()
{
	LongBase ret;
	for (int i = 0; i < LONG_NUM; i++)
		ret.numbers[i] = ~numbers[i];
	return ret;
}

void LongBase::PrintBinary()
{
	for (int i = LONG_NUM - 1; i >= 0; i--)
	{
		for (int k = 31; k >= 0; k--)
			std::cout << ((numbers[i] >> k) & 1);
		std::cout << " ";
	}
	std::cout << "" << std::endl;

}

void LongBase::PrintBinary(int frac)
{
	const size_t s = sizeof(numbers) * 8 + 2;
	char c[s], tmp[s-2];
	size_t ct = 0;
	c[s - 1] = 0;
	for (int i = LONG_NUM - 1; i >= 0; i--)
		for (int k = 31; k >= 0; k--)
			tmp[ct++] = '0' + ((numbers[i] >> k) & 1);
	size_t index = s - 2 - frac;
	memcpy(c, tmp, index);
	c[index] = '.';
	memcpy(c + index + 1, tmp + index, frac);
	std::cout << c << std::endl;
}
