#pragma once
#include <cstdint>
#include <string>

template <typename T>
struct Point
{
	Point(T x, T y)
		: x(x)
		, y(y)
	{}
	T x;
	T y;
};

template <typename T>
struct Rect
{
	Rect(Point<T> leftTop, T width, T height)
		: leftTop(leftTop)
		, width(width)
		, height(height)
	{}
	Point<T> leftTop;
	T width;
	T height;
};

using PointD = Point<double>;
using RectD = Rect<double>;
using RGBAColor = uint64_t;

std::string TransformRGBAToHex(RGBAColor color);
