#include "Image.h"
#include <cassert>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <vector>

/**
 * ������������ ����������� ��������� �������. ���� ������� �� �������� ��������������,
 * ����������� ���������� std::out_of_range.
 */
Image::Image(Size size, char color)
{
	if (size.height < 0 || size.width < 0)
		throw std::out_of_range("sizes shoud be > 0");
	m_size = size;
	Tile tile(color);
	CoW<Tile> cowTile(tile);
	//����� ������ ������
	double resultHeight = ceil(static_cast<double>(size.height) /
		static_cast<double>(Tile::SIZE));
	double resultWidth = ceil(static_cast<double>(size.width) /
		static_cast<double>(Tile::SIZE));
	size_t countTiles = static_cast<size_t>(resultHeight * resultWidth);
	Point leftTop;
	for (size_t i = 0; i < countTiles; i++)
	{
		if (leftTop.x > size.width)
		{
			leftTop.x = 0;
			leftTop.y += Tile::SIZE;
		}
		m_tiles.push_back({ leftTop, cowTile });
		leftTop.x += Tile::SIZE;
	}
	/* ���������� ����������� �������������� */
}

// ���������� ������ ����������� � ��������.
Size Image::GetSize() const noexcept
{
	/* ���������� ����� ��������������. */

	return m_size;
}

/**
 * ���������� ����� ������� � ��������� �����������.���� ���������� ������� �� �������
 * �����������, ���������� �������.
 */
char Image::GetPixel(Point p) const noexcept
{
	/* ���������� ����� ��������������. */
	if (!IsPointInSize(p, m_size))
	{
		return ' ';
	}
	//�� 0(1)
	for (auto& tile : m_tiles)
	{
		if (IsPointInSize(p, { tile.leftTop.x +
			tile.tile->SIZE, tile.leftTop.y + tile.tile->SIZE }))
		{
			Point point;
			point.x = p.x - tile.leftTop.x;
			point.y = p.y - tile.leftTop.y;
			return tile.tile->GetPixel(point);
		}
	}
}

/**
 * ����� ����� ������� � ��������� �����������. ���� ���������� ������� �� ������� �����������
 * �������� ������������.
 */
void Image::SetPixel(Point p, char color)
{
	if (!IsPointInSize(p, m_size))
	{
		return;
	}
	//�� 0(1)
	for (auto& tile : m_tiles)
	{
		if ((p.x >= tile.leftTop.x && p.x <= tile.leftTop.x + Tile::SIZE) 
			&& (p.y >= tile.leftTop.y && p.y <= tile.leftTop.y + Tile::SIZE))
		{
			Point point;
			point.x = p.x - tile.leftTop.x;
			point.y = p.y - tile.leftTop.y;
			tile.tile.Write()->SetPixel(point, color);
			//return tile.tile->GetPixel(point);
		}
	}
	/* ���������� ����� ��������������. */
}

/**
 * ������� � ����� out ����������� � ���� ��������.
 */
void Print(const Image& img, std::ostream& out)
{
	const auto size = img.GetSize();
	for (int y = 0; y < size.height; ++y)
	{
		for (int x = 0; x < size.width; ++x)
		{
			out.put(img.GetPixel({ x, y }));
		}
		out.put('\n');
	}
}

/**
 * ��������� ����������� �� pixels. ����� ����������� ����������� ��������� \n.
 * ������� �������� ������������ �� ���������� ��������� ������ � ����� ������� �����.
 */
Image LoadImage(const std::string& pixels)
{
	std::istringstream s(pixels);
	Size size;
	std::string line;
	while (std::getline(s, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	s = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(s, line))
			break;

		int x = 0;
		for (char ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}