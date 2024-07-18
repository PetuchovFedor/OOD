#pragma once

//enum class ShapesTypes
struct Point
{
	Point (int x, int y)
		: x(x)
		, y(y)
	{}
	Point()
	{
		x = y = 0;
	}

	bool operator==(const Point& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Point& other) const
	{
		return x != other.x || y != other.y;
	}

	int x, y;
};

struct Size
{
	Size()
	{
		width = height = 0;
	}

	Size(int width, int height)
		: width(width)
		, height(height)
	{}

	bool operator==(const Size& other) const
	{
		return width == other.width && height == other.height;
	}

	bool operator!=(const Size& other) const
	{
		return width != other.width || height != other.height;
	}

	int width, height;
};
struct Rect
{
	Rect(Point leftTop, Size size)
		: leftTop(leftTop)
		, size(size)
	{}

	Rect(){}

	bool operator==(const Rect& other) const
	{
		return leftTop == other.leftTop && size == other.size;
	}

	bool operator!=(const Rect& other) const
	{
		return leftTop != other.leftTop || size != other.size;
	}

	Point leftTop;
	Size size;
};