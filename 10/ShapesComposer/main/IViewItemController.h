#pragma once
#include "IPictureItem.h"

class IViewItemController
{
public:
	virtual void SetPosition(Point pos) = 0;
	virtual void SetFrame(const Rect& frame) = 0;
	virtual ~IViewItemController() = default;
};