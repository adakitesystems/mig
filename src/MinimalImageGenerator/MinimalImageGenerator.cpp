#include "MinimalImageGenerator.h"

#include <cstdio>
#include <fstream>
#include <sstream>

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

		_pixels = new Color[pixelsLength];
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

	void Image::setPixel(const XY &xy, const Color &color)
	{
		setPixel(xy.x, xy.y, color.r, color.g, color.b);
	}

	void Image::setPixel(const uint16_t x, const uint16_t y, const unsigned char red, const unsigned char green, const unsigned char blue)
	{
		const auto index = calculateIndex(x, y);
		auto &pixel = _pixels[index];
		pixel.r = red;
		pixel.g = green;
		pixel.b = blue;
	}

	void Image::drawBox(const XY &topLeft, const XY &bottomRight, const Color &color, const FillMode fillMode)
	{
		const auto topLeftX = topLeft.x;
		const auto topLeftY = topLeft.y;
		const auto bottomRightX = bottomRight.x;
		const auto bottomRightY = bottomRight.y;

		/* top line */
		for (uint16_t x = topLeftX; x <= bottomRightX; ++x) {
			setPixel(x, topLeftY, color.r, color.g, color.b);
		}

		/* left line */
		for (uint16_t y = topLeftY; y <= bottomRightY; ++y) {
			setPixel(topLeftX, y, color.r, color.g, color.b);
		}

		/* bottom line */
		for (uint16_t x = topLeftX; x <= bottomRightX; ++x) {
			setPixel(x, bottomRightY, color.r, color.g, color.b);
		}

		/* right line */
		for (uint16_t y = topLeftY; y <= bottomRightY; ++y) {
			setPixel(bottomRightX, y, color.r, color.g, color.b);
		}

		if (fillMode == FillMode::SOLID) {
			for (uint16_t y = topLeftY + 1; y <= bottomRightY - 1; ++y) {
				for (uint16_t x = topLeftX + 1; x <= bottomRightX - 1; ++x) {
					setPixel(x, y, color.r, color.g, color.b);
				}
			}
		}
	}

	void Image::writeToPPM(const std::string &filename) const
	{
		const size_t pixelsLength = _width * _height;
		unsigned char *pixels = new unsigned char[pixelsLength * 3 + 1];

		size_t index = 0;
		for (uint16_t y = 0; y < _height; ++y) {
			for (uint16_t x = 0; x < _width; ++x) {
				const auto &pixel = _pixels[calculateIndex(x, y)];
				pixels[index++] = pixel.r;
				pixels[index++] = pixel.g;
				pixels[index++] = pixel.b;
			}
		}

		std::ofstream fout;
		fout.open(filename.c_str());
		if (fout) {
			std::ostringstream ss;

			ss << "P3 " << _width << " " << _height << " 255 ";
			for (size_t i = 0; i < pixelsLength; ++i) {
				const auto &pixel = _pixels[i];

				char buffer[100];
				memset(buffer, 0, 100);
				snprintf(buffer, 100, "%d %d %d ", pixel.r, pixel.g, pixel.b);

				ss << buffer;

				if ((i + 1) % _width == 0) {
					ss << '\n';
				}
			}

			fout << ss.str();
			fout.flush();
			fout.close();
		}

		delete[] pixels;
	}

	void Image::writeToBMP(const std::string &filename) const
	{
		const size_t pixelsLength = _width * _height;
		unsigned char *pixels = new unsigned char[pixelsLength * 3];

		size_t index = 0;
		for (uint16_t y = 0; y < _height; ++y) {
			for (uint16_t x = 0; x < _width; ++x) {
				const auto &pixel = _pixels[calculateIndex(x, y)];
				pixels[index++] = pixel.r;
				pixels[index++] = pixel.g;
				pixels[index++] = pixel.b;
			}
		}

		stbi_write_bmp(filename.c_str(), _width, _height, 3, pixels);

		delete[] pixels;
	}

	size_t Image::calculateIndex(const uint16_t x, const uint16_t y) const
	{
		const size_t index = _width * y + x;
		return index;
	}
}
