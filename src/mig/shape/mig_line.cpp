#include "mig_line.h"

namespace MIG
{
	namespace Shape
	{
		Line::Line(const XY &newA, const XY &newB, const RGB &newRgb)
			: a(newA)
			, b(newB)
			, rgb(newRgb)
		{}

		// https://en.wikipedia.org/wiki/Bresenham's_line_algorithm#All_cases
		void Line::drawTo(MigImage &migImage)
		{
			const auto x0 = a.x;
			const auto y0 = a.y;
			const auto x1 = b.x;
			const auto y1 = b.y;

			if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
				if (x0 > x1) {
					drawLineLow(migImage, x1, y1, x0, y0);
				}
				else {
					drawLineLow(migImage, x0, y0, x1, y1);
				}
			}
			else {
				if (y0 > y1) {
					drawLineHigh(migImage, x1, y1, x0, y0);
				}
				else {
					drawLineHigh(migImage, x0, y0, x1, y1);
				}
			}
		}

		void Line::drawLineLow(MigImage &migImage, const int x0, const int y0, const int x1, const int y1)
		{
			auto dx = x1 - x0;
			auto dy = y1 - y0;

			int yi = 1;
			if (dy < 0) {
				yi = -yi;
				dy = -dy;
			}

			int d = 2 * dy - dx;
			int y = y0;

			for (int x = x0; x <= x1; ++x) {
				if (migImage.isValid(x, y)) {
					migImage.drawPixel(x, y, rgb.r, rgb.g, rgb.b);
					if (d > 0) {
						y += yi;
						d -= 2 * dx;
					}
					d += 2 * dy;
				}
			}
		}

		void Line::drawLineHigh(MigImage &migImage, const int x0, const int y0, const int x1, const int y1)
		{
			auto dx = x1 - x0;
			auto dy = y1 - y0;

			int xi = 1;
			if (dx < 0) {
				xi = -xi;
				dx = -dx;
			}

			int d = 2 * dx - dy;
			int x = x0;

			for (int y = y0; y <= y1; ++y) {
				if (migImage.isValid(x, y)) {
					migImage.drawPixel(x, y, rgb.r, rgb.g, rgb.b);
					if (d > 0) {
						x += xi;
						d -= 2 * dy;
					}
					d += 2 * dx;
				}
			}
		}
	}
}
