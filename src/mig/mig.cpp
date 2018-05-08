#include "mig.h"

#include <math.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <sstream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBI_MSC_SECURE_CRT

#include "../stb_image/stb_image_write.h"

namespace MIG
{

	MigImage::MigImage(const int width, const int height)
		: _width(width)
		, _height(height)
	{
		const auto pixelsLength = size_t(_width) * size_t(_height);

		_pixels = new RGB[pixelsLength];
		for (int y = 0; y < _height; ++y) {
			for (int x = 0; x < _width; ++x) {
				drawPixel(x, y, 0, 0, 0);
			}
		}
	}

	MigImage::~MigImage()
	{
		delete[] _pixels;
	}

	void MigImage::drawPixel(const XY &xy, const RGB &rgb)
	{
		drawPixel(xy.x, xy.y, rgb.r, rgb.g, rgb.b);
	}

	void MigImage::drawPixel(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)
	{
		if (!isValid(x, y)) {
			return;
		}

		const auto index = calculateIndex(x, y);
		auto &pixel = _pixels[index];
		pixel.r = red;
		pixel.g = green;
		pixel.b = blue;
	}

	void MigImage::drawRectangle(const XY &topLeft, const XY &bottomRight, const RGB &rgb, const FillMode fillMode)
	{
		for (uint16_t y = topLeft.y; y <= bottomRight.y; ++y) {
			for (uint16_t x = topLeft.x; x <= bottomRight.x; ++x) {
				const bool isBorderPixel = x == topLeft.x || x == bottomRight.x || y == topLeft.y || y == bottomRight.y;
				if (fillMode == FillMode::SOLID || isBorderPixel) {
					drawPixel(x, y, rgb.r, rgb.g, rgb.b);
				}
			}
		}
	}

	void MigImage::drawCircle(const XY &center, const int radius, const RGB &rgb, const FillMode fillMode)
	{
		const auto leftX = center.x - radius;
		const auto rightX = center.x + radius;

		const auto topY = center.y - radius;
		const auto bottomY = center.y + radius;

		for (int y = topY; y <= bottomY; ++y) {
			for (int x = leftX; x <= rightX; ++x) {
				const auto &xy = XY(x, y);
				if (Util::distance(xy, center) <= radius) {
					const bool isBorderPixel = Util::distance(xy, center) >= radius - 1;
					if (fillMode == FillMode::SOLID || isBorderPixel) {
						drawPixel(x, y, rgb.r, rgb.g, rgb.b);
					}
				}
			}
		}
	}

	// https://en.wikipedia.org/wiki/Bresenham's_line_algorithm#All_cases
	void MigImage::drawLine(const XY &a, const XY &b, const RGB &rgb)
	{
		const auto x0 = a.x;
		const auto y0 = a.y;
		const auto x1 = b.x;
		const auto y1 = b.y;

		if (std::abs(y1 - y0) < std::abs(x1 - x0)) {
			if (x0 > x1) {
				drawLineLow(x1, y1, x0, y0, rgb);
			}
			else {
				drawLineLow(x0, y0, x1, y1, rgb);
			}
		}
		else {
			if (y0 > y1) {
				drawLineHigh(x1, y1, x0, y0, rgb);
			}
			else {
				drawLineHigh(x0, y0, x1, y1, rgb);
			}
		}
	}

	void MigImage::drawLineLow(const int x0, const int y0, const int x1, const int y1, const RGB &rgb)
	{
		auto dx = x1 - x0;
		auto dy = y1 - y0;

		int yi = 1;
		if (dy < 0) {
			yi = -yi;
			dy = -dy;
		}

		int d = 2 * dy - dx;
		int y = y0;

		for (int x = x0; x <= x1; ++x) {
			drawPixel(x, y, rgb.r, rgb.g, rgb.b);
			if (d > 0) {
				y += yi;
				d -= 2 * dx;
			}
			d += 2 * dy;
		}
	}

	void MigImage::drawLineHigh(const int x0, const int y0, const int x1, const int y1, const RGB &rgb)
	{
		auto dx = x1 - x0;
		auto dy = y1 - y0;

		int xi = 1;
		if (dx < 0) {
			xi = -xi;
			dx = -dx;
		}

		int d = 2 * dx - dy;
		int x = x0;

		for (int y = y0; y <= y1; ++y) {
			drawPixel(x, y, rgb.r, rgb.g, rgb.b);
			if (d > 0) {
				x += xi;
				d -= 2 * dy;
			}
			d += 2 * dx;
		}
	}
	
	bool MigImage::isValid(const XY &xy) const
	{
		return isValid(xy.x, xy.y);
	}

	bool MigImage::isValid(const int x, const int y) const
	{
		return (x >= 0 && x < _width && y >= 0 && y < _height);
	}

	void MigImage::writeToPPM(const std::string &filename) const
	{
		std::ofstream outputFile;
		outputFile.open(filename.c_str());

		if (outputFile) {
			std::ostringstream header;
			header << "P3 " << _width << " " << _height << " 255 "; // PPM image header
			outputFile << header.str();

			const size_t bufsize = 128;
			char buf[bufsize];

			for (int y = 0; y < _height; ++y) {
				std::ostringstream row;

				for (int x = 0; x < _width; ++x) {
					const auto &pixel = _pixels[calculateIndex(x, y)];

					memset(buf, 0, bufsize);
					snprintf(buf, bufsize, "%d %d %d ", pixel.r, pixel.g, pixel.b);

					row << buf;
				}

				row << '\n';

				outputFile << row.str();
			}

			outputFile.flush();
			outputFile.close();
		}
	}

	void MigImage::writeToBMP(const std::string &filename) const
	{
		const size_t pixelDataLength = _width * _height * RGB::comp;
		unsigned char *pixelData = new unsigned char[pixelDataLength];
		copyRgbPixelsTo(pixelData);

		stbi_write_bmp(filename.c_str(), _width, _height, RGB::comp, pixelData);

		delete[] pixelData;
	}

	void MigImage::writeToPNG(const std::string &filename) const
	{
		const size_t pixelDataLength = _width * _height * RGB::comp;
		unsigned char *pixelData = new unsigned char[pixelDataLength];
		copyRgbPixelsTo(pixelData);

		const int strideInBytes = _width * RGB::comp;

		stbi_write_png(filename.c_str(), _width, _height, RGB::comp, pixelData, strideInBytes);

		delete[] pixelData;
	}

	size_t MigImage::calculateIndex(const int x, const int y) const
	{
		return size_t(_width) * size_t(y) + size_t(x);
	}

	void MigImage::copyRgbPixelsTo(unsigned char *pixelData) const
	{
		size_t index = 0;
		for (int y = 0; y < _height; ++y) {
			for (int x = 0; x < _width; ++x) {
				const auto &pixel = _pixels[calculateIndex(x, y)];
				pixelData[index++] = pixel.r;
				pixelData[index++] = pixel.g;
				pixelData[index++] = pixel.b;
			}
		}
	}

	namespace Util 
	{
		double distance(const XY &a, const XY &b)
		{
			const auto dx = a.x - b.x;
			const auto dy = a.y - b.y;
			return norm(dx, dy);
		}

		double norm(const int x, const int y)
		{
			return sqrt(squaredNorm(x, y));
		}

		int squaredNorm(const int x, const int y)
		{
			return (x * x + y * y);
		}
	}
}
