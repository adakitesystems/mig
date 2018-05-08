#ifndef __MIG_SHAPE_H__B85670D5DA1F57CA8745CDB5F25FD7CF____
#define __MIG_SHAPE_H__B85670D5DA1F57CA8745CDB5F25FD7CF____
#pragma once

#include "../mig.h"

namespace MIG
{
	namespace Shape
	{
		class ShapeInterface
		{
		public:
			virtual void drawTo(MigImage &migImage) = 0;

		protected:
			ShapeInterface() {}
		};
	}
}

#endif
