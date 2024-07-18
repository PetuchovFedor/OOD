#pragma once
#include <stdexcept>

class CFrame
{
public:
	CFrame(int width, int height)
	{
		if (width < 0 || height < 0)
		{
			throw std::invalid_argument("Frame's width and height shoud be > 0");
		}
		m_width = static_cast<size_t>(width);
		m_height = static_cast<size_t>(height);
	}

	size_t GetWidth() const
	{
		return m_width;
	}

	size_t GetHeight() const
	{
		return m_height;
	}
private:
	size_t m_width, m_height;
};