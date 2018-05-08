#ifndef __MIG_LINE_H__E69AEABFE71C88752B028528BB42DF2C____
#define __MIG_LINE_H__E69AEABFE71C88752B028528BB42DF2C____
#pragma once

#include "mig_shape.h"
#include "../mig_xy.h"
#include "../mig_rgb.h"

namespace MIG
{
	namespace Shape
	{
		class Line : public ShapeInterface
		{
		public:
			Line(const XY &a = XY(0, 0), const XY &b = XY(0, 0), const RGB &rgb = RGB(0, 0, 0));

			virtual void drawTo(MigImage &migImage) override;

			XY getA() const;
			XY getB() const;
			RGB getRGB() const;

		private:
			void drawLineLow(MigImage &migImage, const int x0, const int y0, const int x1, const int y1);
			void drawLineHigh(MigImage &migImage, const int x0, const int y0, const int x1, const int y1);

			const XY _a;
			const XY _b;
			const RGB _rgb;

		};
	}
}

#endif
