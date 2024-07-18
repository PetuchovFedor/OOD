#pragma once
#include "IShape.h"
#include "IImage.h"

class IMainFrameController
{
public:
	virtual void AddShape(IShapePtr item) = 0;

	virtual void AddImage(IImagePtr item) = 0;

	virtual void DeleteItem(const std::string& id) = 0;

	virtual void Undo() = 0;

	virtual void Redo () = 0;

	virtual ~IMainFrameController() = default;
};