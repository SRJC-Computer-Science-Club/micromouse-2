#pragma once
#include "coord.h"

using namespace micromouse;

/*
* Test function for the coord class.
*/
coord test_coord()
{
	coord c0 = coord(0, 0);
	coord c1 = coord(3, 7);
	coord c2 = coord(1, 5);
	coord c3 = c0 + c1 + c2;

	return c3;
}
