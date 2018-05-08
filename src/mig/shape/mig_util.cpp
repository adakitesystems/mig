#include "mig_util.h"

#include <math.h>

namespace MIG
{
	namespace Util
	{
		double distance(const XY &a, const XY &b)
		{
			const auto dx = a.x - b.x;
			const auto dy = a.y - b.y;
			return norm(dx, dy);
		}

		double norm(const int x, const int y)
		{
			return sqrt(squaredNorm(x, y));
		}

		int squaredNorm(const int x, const int y)
		{
			return (x * x + y * y);
		}
	}
}
