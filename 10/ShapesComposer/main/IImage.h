#pragma once
#include "IPictureItem.h"
#include <filesystem>

class IImage : public IPictureItem
{
public:
	virtual std::filesystem::path GetPath() const = 0;
	virtual ~IImage() = default;
};

using IImagePtr = std::shared_ptr<IImage>;