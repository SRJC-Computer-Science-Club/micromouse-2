#pragma once
#include <assert.h>

namespace micromouse
{
	/*
	These four directions are relative to the maze.
	The bot will start in the southwest corner, facing north.
	NORTH: Positive Y
	EAST: Positive X
	*/
	enum direction { NORTH, EAST, SOUTH, WEST };

	/*
	A pair of x-y coordinates that represents a cell within the maze.
	*/
	struct coord
	{
		int x;
		int y;

		coord(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
	};

	/*
	Coord Arithmetic
	(Operator Overloads)
	*/
	coord operator+(const coord& left, const coord& right)
	{
		return coord(left.x + right.x, left.y + right.y);
	}

	coord operator-(const coord& left, const coord& right)
	{
		return coord(left.x - right.x, left.y - right.y);
	}

	coord operator*(int left, const coord& right)
	{
		return coord(left * right.x, left * right.y);
	}

	coord operator*(const coord& left, int right)
	{
		return right * left;
	}


	/*
	Returns a unit vector in the given direction.
	*/
	coord get_offset(direction dir)
	{
		switch (dir)
		{
		case NORTH:
			return coord(0, 1);
		case EAST:
			return coord(1, 0);
		case SOUTH:
			return coord(0, -1);
		case WEST:
			return coord(-1, 0);
		default:
			assert(false);
		}
	}
}