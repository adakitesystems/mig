#ifndef __MIG_H__5BE397E7C7867C3914F689451B69451A____
#define __MIG_H__5BE397E7C7867C3914F689451B69451A____
#pragma once

#include <string>

#include "TypeSafeEnum.h"

namespace MIG
{
	struct RGB
	{
		static const unsigned char comp = 3;

		unsigned char r;
		unsigned char g;
		unsigned char b;

		RGB() : r(0), g(0), b(0) {}
		RGB(const unsigned char red, const unsigned char green, const unsigned char blue) : r(red), g(green), b(blue) {}
	};

	struct XY
	{
		int x;
		int y;

		XY() : x(0), y(0) {}
		XY(const int inX, const int inY) : x(inX), y(inY) {}
	};

	struct FillModeDef { enum type { NONE, SOLID }; };
	typedef TypeSafeEnum<FillModeDef> FillMode;

	class MigImage
	{
	public:
		MigImage(const int width, const int height);
		~MigImage();

		void drawPixel(const XY &xy, const RGB &rgb);
		void drawPixel(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue);

		void drawRectangle(const XY &topLeft, const XY &bottomRight, const RGB &color, const FillMode fillMode = FillMode::NONE);
		void drawCircle(const XY &center, const int radius, const RGB &color, const FillMode fillMode = FillMode::NONE);
		void drawLine(const XY &a, const XY &b, const RGB &rgb);

		bool isValid(const XY &xy) const;
		bool isValid(const int x, const int y) const;

		void writeToPPM(const std::string &filename) const;
		void writeToBMP(const std::string &filename) const;
		void writeToPNG(const std::string &filename) const;

	private:
		const int _width;
		const int _height;
		RGB *_pixels;

		size_t calculateIndex(const int x, const int y) const;

		void copyRgbPixelsTo(unsigned char *pixelData) const;

		void drawLineLow(const int x0, const int y0, const int x1, const int y1, const RGB &rgb);
		void drawLineHigh(const int x0, const int y0, const int x1, const int y1, const RGB &rgb);
	};

	namespace Util
	{
		static double distance(const XY &a, const XY &b);
		static double norm(const int x, const int y);
		static int squaredNorm(const int x, const int y);
	}
}

#endif
