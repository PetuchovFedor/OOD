#pragma once
#include "CImage.h"
#include "GenerateRandomString.h"

class CImageFactory
{
public:
	CImageFactory()
	{
		auto tmpDir = std::filesystem::current_path();
		m_pathToTmpImagesDir = tmpDir / "images";
		if (std::filesystem::exists(m_pathToTmpImagesDir))
		{
			m_pathToTmpImagesDir = tmpDir / GenerateRandomString();
		}
		std::filesystem::create_directory(m_pathToTmpImagesDir);
	}

	std::shared_ptr<IImage> CreateImage(const std::string& id, 
		const std::filesystem::path& path, Rect frame)
	{
		std::string newName = GenerateRandomString() + ".png";
		std::string newPath = m_pathToTmpImagesDir.stem().string() + "/" + newName;
		std::filesystem::copy_file(path, newPath, std::filesystem::copy_options::overwrite_existing);
		return std::make_shared<CImage>(id, newPath, frame);
	}

	~CImageFactory()
	{
		if (std::filesystem::exists(m_pathToTmpImagesDir))
			std::filesystem::remove_all(m_pathToTmpImagesDir);
	}

private:
	std::filesystem::path m_pathToTmpImagesDir;
};