#pragma once

#include "LongBase.h"

class XCounter : public LongBase
{
public:
	XCounter() : LongBase() {}
	void operator ++ ();
};