#include "mig_circle.h"

#include "mig_util.h"

namespace MIG
{
	namespace Shape
	{
		Circle::Circle(const XY &center, const int radius, const RGB &rgb, const FillStyle fillMode)
			: _center(center)
			, _radius(radius)
			, _rgb(rgb)
			, _fillStyle(fillMode)
		{}

		void Circle::drawTo(MigImage &migImage)
		{
			const auto leftX = getCenter().x - getRadius();
			const auto rightX = getCenter().x + getRadius();

			const auto topY = getCenter().y - getRadius();
			const auto bottomY = getCenter().y + getRadius();

			for (int y = topY; y <= bottomY; ++y) {
				for (int x = leftX; x <= rightX; ++x) {
					const auto &xy = XY(x, y);
					if (Util::distance(xy, getCenter()) <= getRadius()) {
						const bool isBorderPixel = Util::distance(xy, getCenter()) >= getRadius() - 1;
						if ((getFillStyle() == FillStyle::SOLID || isBorderPixel) && migImage.isValid(x, y)) {
							migImage.drawPixel(x, y, getRGB().r, getRGB().g, getRGB().b);
						}
					}
				}
			}
		}

		XY Circle::getCenter() const
		{
			return _center;
		}

		int Circle::getRadius() const
		{
			return _radius;
		}

		RGB Circle::getRGB() const
		{
			return _rgb;
		}

		Circle::FillStyle Circle::getFillStyle() const
		{
			return _fillStyle;
		}
	}
}
