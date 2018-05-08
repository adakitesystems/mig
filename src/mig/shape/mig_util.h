#ifndef __MIG_UTIL_H__474E68DD10C22C5A9EEDA65931AEFA61____
#define __MIG_UTIL_H__474E68DD10C22C5A9EEDA65931AEFA61____
#pragma once

#include "../mig_xy.h"

namespace MIG
{
	namespace Util
	{
		double distance(const XY &a, const XY &b);
		double norm(const int x, const int y);
		int squaredNorm(const int x, const int y) noexcept;
	}
}

#endif
