#include "mig_rectangle.h"

namespace MIG
{
	namespace Shape
	{
		Rectangle::Rectangle(const XY &topLeft, const int width, const int height, const RGB &rgb, const FillStyle fillStyle)
			: _topLeft(topLeft)
			, _width(width)
			, _height(height)
			, _rgb(rgb)
			, _fillStyle(fillStyle)
		{}

		void Rectangle::drawTo(MigImage &migImage)
		{
			for (int y = getTopLeft().y; y <= getBottomRight().y; ++y) {
				for (int x = getTopLeft().x; x <= getBottomRight().x; ++x) {
					const bool isBorderPixel = x == getTopLeft().x || x == getBottomRight().x || y == getTopLeft().y || y == getBottomRight().y;
					if ((_fillStyle == FillStyle::SOLID || isBorderPixel) && migImage.isValid(x, y)) {
						migImage.drawPixel(x, y, _rgb.r, _rgb.g, _rgb.b);
					}
				}
			}
		}

		XY Rectangle::getTopLeft() const
		{
			return _topLeft;
		}

		XY Rectangle::getBottomRight() const
		{
			const auto topLeft = getTopLeft();
			const int bottomRightX = topLeft.x + _width;
			const int bottomRightY = topLeft.y + _height;

			return XY(bottomRightX, bottomRightY);
		}

		int Rectangle::getWidth() const
		{
			return _width;
		}

		int Rectangle::getHeight() const
		{
			return _height;
		}

		RGB Rectangle::getRGB() const
		{
			return _rgb;
		}

		Rectangle::FillStyle Rectangle::getFillStyle() const
		{
			return _fillStyle;
		}
	}
}
