#ifndef __MIG_RGB_H__F433E25E34DD886CD304C494F12463F7____
#define __MIG_RGB_H__F433E25E34DD886CD304C494F12463F7____
#pragma once

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
}

#endif
