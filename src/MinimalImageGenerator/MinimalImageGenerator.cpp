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
				drawPixel(x, y, 0, 0, 0);
			}
		}
	}

	Image::~Image()
	{
		delete[] _pixels;
	}

	void Image::drawPixel(const XY &xy, const Color &color)
	{
		drawPixel(xy.x, xy.y, color.r, color.g, color.b);
	}

	void Image::drawPixel(const uint16_t x, const uint16_t y, const unsigned char red, const unsigned char green, const unsigned char blue)
	{
		const auto index = calculateIndex(x, y);
		auto &pixel = _pixels[index];
		pixel.r = red;
		pixel.g = green;
		pixel.b = blue;
	}

	void Image::drawRectangle(const XY &topLeft, const XY &bottomRight, const Color &color, const FillMode fillMode)
	{
		const auto topLeftX = topLeft.x;
		const auto topLeftY = topLeft.y;
		const auto bottomRightX = bottomRight.x;
		const auto bottomRightY = bottomRight.y;

		/* top line */
		for (uint16_t x = topLeftX; x <= bottomRightX; ++x) {
			drawPixel(x, topLeftY, color.r, color.g, color.b);
		}

		/* left line */
		for (uint16_t y = topLeftY; y <= bottomRightY; ++y) {
			drawPixel(topLeftX, y, color.r, color.g, color.b);
		}

		/* bottom line */
		for (uint16_t x = topLeftX; x <= bottomRightX; ++x) {
			drawPixel(x, bottomRightY, color.r, color.g, color.b);
		}

		/* right line */
		for (uint16_t y = topLeftY; y <= bottomRightY; ++y) {
			drawPixel(bottomRightX, y, color.r, color.g, color.b);
		}

		if (fillMode == FillMode::SOLID) {
			for (uint16_t y = topLeftY + 1; y <= bottomRightY - 1; ++y) {
				for (uint16_t x = topLeftX + 1; x <= bottomRightX - 1; ++x) {
					drawPixel(x, y, color.r, color.g, color.b);
				}
			}
		}
	}

	void Image::writeToPPM(const std::string &filename) const
	{
		const size_t pixelsLength = _width * _height;

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
	}

	void Image::writeToBMP(const std::string &filename) const
	{
		const int comp = 3;

		unsigned char *pixelData = new unsigned char[_width * _height * comp];
		copyPixelsTo(pixelData);

		stbi_write_bmp(filename.c_str(), _width, _height, comp, pixelData);

		delete[] pixelData;
	}

	void Image::writeToPNG(const std::string &filename) const
	{
		const int comp = 3;

		unsigned char *pixelData = new unsigned char[_width * _height * comp];
		copyPixelsTo(pixelData);

		stbi_write_png(filename.c_str(), _width, _height, 3, pixelData, _width * comp);

		delete[] pixelData;
	}

	size_t Image::calculateIndex(const uint16_t x, const uint16_t y) const
	{
		return size_t(_width * y + x);
	}

	void Image::copyPixelsTo(unsigned char *pixelData) const
	{
		size_t index = 0;
		for (uint16_t y = 0; y < _height; ++y) {
			for (uint16_t x = 0; x < _width; ++x) {
				const auto &pixel = _pixels[calculateIndex(x, y)];
				pixelData[index++] = pixel.r;
				pixelData[index++] = pixel.g;
				pixelData[index++] = pixel.b;
			}
		}
	}
}
