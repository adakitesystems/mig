#ifndef __MINIMAL_IMAGE_GENERATOR__5BE397E7C7867C3914F689451B69451A____
#define __MINIMAL_IMAGE_GENERATOR__5BE397E7C7867C3914F689451B69451A____
#pragma once

#include <cstdint>
#include <string>

namespace MIG
{
	struct Color {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		Color() : r(0), g(0), b(0) {}
		Color(unsigned char red, unsigned char green, unsigned char blue) : r(red), g(green), b(blue) {}
	};

	struct XY {
		uint16_t x;
		uint16_t y;
		XY() : x(0), y(0) {}
		XY(uint16_t inX, uint16_t inY) : x(inX), y(inY) {}
	};

	enum FillMode { NONE, SOLID };

	class Image
	{
	public:
		Image(const uint16_t width, const uint16_t height);
		~Image();

		void setPixel(const XY &xy, const Color &color);
		void setPixel(const uint16_t x, const uint16_t y, const unsigned char red, const unsigned char green, const unsigned char blue);

		void drawBox(const XY &topLeft, const XY &bottomRight, const Color &color, const FillMode fillMode = FillMode::NONE);

		void writeToPPM(const std::string &filename) const;
		void writeToBMP(const std::string &filename) const;

	private:
		const uint16_t _width;
		const uint16_t _height;
		Color *_pixels;

		size_t calculateIndex(const uint16_t x, const uint16_t y) const;
	};
}

#endif
