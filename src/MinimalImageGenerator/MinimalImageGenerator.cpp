#include "MinimalImageGenerator.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "../stb_image/stb_image_write.h"

namespace MIG
{
	Image::Image(const uint16_t width, const uint16_t height)
		: _width(width)
		, _height(height)
	{
		const size_t pixelsLength = size_t(uint16_t(_width) * uint16_t(_height));

		_pixels = new Pixel[pixelsLength];
		for (uint16_t y = 0; y < _height; ++y) {
			for (uint16_t x = 0; x < _width; ++x) {
				setPixel(x, y, 0, 0, 0);
			}
		}
	}

	Image::~Image() 
	{
		delete[] _pixels;
	}

	void Image::setPixel(const uint16_t x, const uint16_t y, const Pixel &color)
	{
		setPixel(x, y, color.r, color.g, color.b);
	}

	void Image::setPixel(const uint16_t x, const uint16_t y, const unsigned char red, const unsigned char green, const unsigned char blue) 
	{
		const auto index = calculateIndex(x, y);
		auto &pixel = _pixels[index];
		pixel.r = red;
		pixel.g = green;
		pixel.b = blue;
	}

	void Image::writeToPNG(const std::string &filename) const
	{
		stbi_write_png(filename.c_str(), _width, _height, 3, _pixels, 3);
	}

	size_t Image::calculateIndex(const uint16_t x, const uint16_t y) const
	{
		const size_t index = _width * x + y;
		return index;
	}
}
