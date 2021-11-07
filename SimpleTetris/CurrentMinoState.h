#pragma once

#include "ConstTetris.h"

struct CurrentMinoState
{
	ConstTetris::MinoType type;
	ConstTetris::MinoDir dir;
	int x;
	int y;

	ConstTetris::TSpin tspin;
};