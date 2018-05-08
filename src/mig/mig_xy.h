#ifndef __MIG_XY_H__F3928519FE4150B5C60162DA086AF5AD____
#define __MIG_XY_H__F3928519FE4150B5C60162DA086AF5AD____
#pragma once

namespace MIG
{
	struct XY
	{
		int x;
		int y;

		XY() : x(0), y(0) {}
		XY(const int newX, const int newY) : x(newX), y(newY) {}
	};
}

#endif
