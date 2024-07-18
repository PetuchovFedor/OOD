#pragma once
#include "IShape.h"

class IGroup : public IShape
{
public:
	virtual size_t GetShapesCount() const = 0;
	virtual IShapePtr GetShapeAtIndex(size_t idx) = 0;
	virtual void InsertShape(IShapePtr shape, size_t idx) = 0;
	virtual void RemoveShape(size_t idx) = 0;
	virtual ~IGroup() = default;
};