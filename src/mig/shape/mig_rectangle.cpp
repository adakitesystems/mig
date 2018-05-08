#include "mig_rectangle.h"

namespace MIG
{
	namespace Shape
	{
		Rectangle::Rectangle(const XY &newTopLeft, const int newWidth, const int newHeight, const RGB &newRgb, const FillStyle newFillStyle)
			: topLeft(newTopLeft)
			, width(newWidth)
			, height(newHeight)
			, rgb(newRgb)
			, fillStyle(newFillStyle)
		{}

		void Rectangle::drawTo(MigImage &migImage)
		{
			const auto bottomRight = XY(topLeft.x + width, topLeft.y + height);

			for (int y = topLeft.y; y <= bottomRight.y; ++y) {
				for (int x = topLeft.x; x <= bottomRight.x; ++x) {
					const bool isBorderPixel = x == topLeft.x || x == bottomRight.x || y == topLeft.y || y == bottomRight.y;
					if ((fillStyle == FillStyle::SOLID || isBorderPixel) && migImage.isValid(x, y)) {
						migImage.drawPixel(x, y, rgb.r, rgb.g, rgb.b);
					}
				}
			}
		}
	}
}
