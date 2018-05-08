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

	int MigImage::getWidth() const
	{
		return _width;
	}

	int MigImage::getHeight() const
	{
		return _height;
	}

	void MigImage::drawPixel(const XY &xy, const RGB &rgb)
	{
		drawPixel(xy.x, xy.y, rgb.r, rgb.g, rgb.b);
	}

	void MigImage::drawPixel(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue)
	{
		const auto index = calculateIndex(x, y);
		auto &pixel = _pixels[index];
		pixel.r = red;
		pixel.g = green;
		pixel.b = blue;
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
}
