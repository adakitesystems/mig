#ifndef __MIG_CIRCLE_H__740C08E378DE009D08212F64544A5900____
#define __MIG_CIRCLE_H__740C08E378DE009D08212F64544A5900____
#pragma once

#include "mig_shape.h"
#include "../mig_xy.h"
#include "../mig_rgb.h"

namespace MIG
{
	namespace Shape
	{
		class Circle : public ShapeInterface
		{
		public:
			enum class FillStyle { NONE, SOLID };

			Circle(const XY &center = XY(0, 0), const int radius = 0, const RGB &rgb = RGB(0, 0, 0), const FillStyle fillStyle = FillStyle::NONE);

			virtual void drawTo(MigImage &migImage) override;

			XY getCenter() const;
			int getRadius() const;
			RGB getRGB() const;
			FillStyle getFillStyle() const;

		private:
			const XY _center;
			const int _radius;
			const RGB _rgb;
			const FillStyle _fillStyle;
		};
	}
}

#endif
