#pragma once
#include <array>
#include <cassert>

#include "geom.h"
#include <vector>

class Tile
{
public:
	// ������ ����� 8*8 ��������.
	constexpr static int SIZE = 8;

	// ����������� �� ���������. ��������� ���� ��������� ������.
	Tile(char color = ' ') noexcept
	{
		/* ���������� ����������� ��� ��������������. */
		for (auto& item: m_pixels)
			item.fill(color);
		// -------------- �� ������� ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
		// -------------- �� ������� ------------
	}

	Tile(const Tile& other)
	{
		/* ���������� ����������� ��� ��������������. */
		m_pixels = other.m_pixels;
		// -------------- �� ������� ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount; // ����������� ������� ������ (��� ����� ������������).
		// -------------- �� ������� ------------
	}

	~Tile()
	{
		// -------------- �� ������� ------------
		--m_instanceCount; // ��������� ������� ������.
		assert(m_instanceCount >= 0);
		// -------------- �� ������� ------------
	}

	/**
	 * �������� ���� ������� �����.
	 * ���� ���������� ������� �� ������� �����, ����� ������ �� ������.
	 */
	void SetPixel(Point p, char color) noexcept
	{
		if (IsPointInSize(p, { SIZE, SIZE }))
		{
			m_pixels[p.y][p.x] = color;
		}
		/* ���������� ����������� ��� ��������������. */
	}

	/**
	 * ���������� ���� �������. ���� ���������� ������� �� ������� �����, ������������ ������.
	 */
	char GetPixel(Point p) const noexcept
	{
		if (IsPointInSize(p, { SIZE, SIZE }))
		{
			return m_pixels[p.y][p.x];
		}
		/* ���������� ����������� ���������� ��������������. */
		return ' ';
	}

	// ���������� ���������� ���������� ������ Tile � ���������.
	static int GetInstanceCount() noexcept
	{
		// -------------- �� ������� ------------
		return m_instanceCount;
		// -------------- �� ������� ------------
	}

private:
	// -------------- �� ������� ------------
	inline static int m_instanceCount = 0;
	// -------------- �� ������� ------------
	std::array<std::array<char, SIZE>, SIZE> m_pixels;
	//std::vector<Point> m_pixels;
	/* ���������� ����� ���� ��� �������� �������� �����. */
};