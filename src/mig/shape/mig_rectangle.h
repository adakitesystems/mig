#ifndef __MIG_RECTANGLE_H__04AF2B602FA081E1E926DE3B27594B00____
#define __MIG_RECTANGLE_H__04AF2B602FA081E1E926DE3B27594B00____
#pragma once

#include "mig_shape.h"
#include "../mig_xy.h"
#include "../mig_rgb.h"

namespace MIG
{
	namespace Shape
	{
		class Rectangle : public ShapeInterface
		{
		public:
			enum class FillStyle { NONE, SOLID };

			Rectangle(const XY &topLeft = XY(0, 0), const int width = 0, const int height = 0, const RGB &rgb = RGB(0, 0, 0), const FillStyle fillStyle = FillStyle::NONE);

			virtual void drawTo(MigImage &migImage) override;

			XY getTopLeft() const;
			XY getBottomRight() const;
			int getWidth() const;
			int getHeight() const;
			RGB getRGB() const;
			FillStyle getFillStyle() const;

		private:
			const XY _topLeft;
			const int _width;
			const int _height;
			const RGB _rgb;
			const FillStyle _fillStyle;
		};
	}
}

#endif
