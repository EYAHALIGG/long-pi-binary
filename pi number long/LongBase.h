#pragma once

#define LONG_NUM 4

class LongBase
{
public:
	unsigned numbers[LONG_NUM] = { 0 };
	LongBase() {}
	LongBase(unsigned val) { numbers[0] = val; }
	bool operator==(const LongBase& val);
	bool operator!=(const LongBase& val);
	bool operator<(const LongBase& val);
	bool operator<=(const LongBase& val);
	bool operator>(const LongBase& val);
	bool operator>=(const LongBase& val);
	LongBase operator << (int shift);
	LongBase operator >> (int shift);
	LongBase ShlOne();
	LongBase ShrOne();
	LongBase operator*(const LongBase& val);
	LongBase operator+(const LongBase& val);
	LongBase operator-(const LongBase& val);
	LongBase operator~();
	void PrintBinary();
	void PrintBinary(int frac);
};