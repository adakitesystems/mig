#ifndef __MIG_H__5BE397E7C7867C3914F689451B69451A____
#define __MIG_H__5BE397E7C7867C3914F689451B69451A____
#pragma once

#include <memory>
#include <string>

#include "mig_xy.h"
#include "mig_rgb.h"

namespace MIG
{
	class MigImage
	{
	public:
		MigImage() = delete;
		MigImage(const int width, const int height);

		int getWidth() const noexcept;
		int getHeight() const noexcept;

		void drawPixel(const XY &xy, const RgbPixel &rgb);
		void drawPixel(const int x, const int y, const unsigned char red, const unsigned char green, const unsigned char blue);

		bool isValid(const XY &xy) const noexcept;
		bool isValid(const int x, const int y) const noexcept;

		void writeToPPM(const std::string &filename) const;
		void writeToBMP(const std::string &filename) const;
		void writeToPNG(const std::string &filename) const;

	private:
		const int _width;
		const int _height;
		std::unique_ptr<RgbPixel[]> _pixels;

		size_t calculateIndex(const int x, const int y) const noexcept;

		void copyRgbPixelsTo(std::unique_ptr<unsigned char[]> &pixelData) const;
	};
}

#endif
