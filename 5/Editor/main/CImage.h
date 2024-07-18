#pragma once
#include "IImage.h"
#include <filesystem>
#include <random>

class CImage : public IImage
{
public:
	CImage(const std::string& path, int width, int height)
		: m_path(path)
		, m_width(width)
		, m_height(height)
	{}

	std::string GetPath()const override
	{
		return m_path;
	}

	int GetWidth()const override
	{
		return m_width;
	}

	int GetHeight()const override
	{
		return m_height;
	}

	void Resize(int width, int height) override
	{
		m_width = width;
		m_height = height;
	}
	
	/*~CImage()
	{
	}*/
private:

	/*std::filesystem::path GeneratePath(const std::string& path)
	{
		std::filesystem::path pathOrigin(path);
		std::string pathCopy = std::filesystem::current_path().string();
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<int> dist('a', 'z');
		std::string fileName(6, ' ');
		for (auto& ch : fileName)
		{			
			ch = dist(rng);
		}
		fileName += pathOrigin.extension().string();
		pathCopy += fileName;
		std::filesystem::copy_file(pathOrigin, pathCopy);
		return std::filesystem::path(pathCopy);
	}*/
	std::string m_path;
	int m_width, m_height;
};