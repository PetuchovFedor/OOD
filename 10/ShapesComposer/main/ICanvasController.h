#pragma once
#include "IPictureItem.h"

class ICanvasController
{
public:

	virtual void DeleteItem(const std::string& id) = 0;

	virtual void Undo() = 0;

	virtual void Redo() = 0;

	virtual void SetSize(Size size) = 0;

	virtual ~ICanvasController() = default;
};