#ifndef __MINIMAL_IMAGE_GENERATOR__5BE397E7C7867C3914F689451B69451A____
#define __MINIMAL_IMAGE_GENERATOR__5BE397E7C7867C3914F689451B69451A____
#pragma once

#include <cstdint>
#include <string>

namespace MIG 
{
	struct Pixel {
		unsigned char r;
		unsigned char g;
		unsigned char b;
		Pixel() : r(0), g(0), b(0) {}
		Pixel(unsigned char red, unsigned char green, unsigned char blue) : r(red), g(green), b(blue) {}
	};

	class Image
	{
	public:
		Image(const uint16_t width, const uint16_t height);
		~Image();

		void setPixel(const uint16_t x, const uint16_t y, const Pixel &color);
		void setPixel(const uint16_t x, const uint16_t y, const unsigned char red, const unsigned char green, const unsigned char blue);

		void writeToPNG(const std::string &filename) const;

	private:
		const uint16_t _width;
		const uint16_t _height;
		Pixel *_pixels;

		size_t calculateIndex(const uint16_t x, const uint16_t y) const;
	};
}

#endif
