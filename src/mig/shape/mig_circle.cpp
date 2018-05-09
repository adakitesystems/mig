#include "mig_circle.h"

#include "mig_util.h"

namespace MIG
{
	namespace Shape
	{
		Circle::Circle(const XY &newCenter, const int newRadius, const RgbPixel &newRgb, const FillStyle newFillStyle)
			: center(newCenter)
			, radius(newRadius)
			, rgb(newRgb)
			, fillStyle(newFillStyle)
		{}

		void Circle::drawTo(MigImage &migImage)
		{
			const auto leftX = center.x - radius;
			const auto rightX = center.x + radius;

			const auto topY = center.y - radius;
			const auto bottomY = center.y + radius;

			for (int y = topY; y <= bottomY; ++y) {
				for (int x = leftX; x <= rightX; ++x) {
					const auto &xy = XY(x, y);
					if (Util::distance(xy, center) <= radius) {
						const bool isBorderPixel = Util::distance(xy, center) >= radius - 1;
						if ((fillStyle == FillStyle::SOLID || isBorderPixel) && migImage.isValid(x, y)) {
							migImage.drawPixel(x, y, rgb.r, rgb.g, rgb.b);
						}
					}
				}
			}
		}
	}
}
