#pragma once
#include "CFrame.h"
#include "ICanvas.h"
#include <memory>
#include "IOutlineStyle.h"
#include "CommonTypes.h"
#include "IDrawable.h"

class IGroup;

class IShape : public IDrawable
{
public:
	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD& frame) = 0;
	virtual std::string GetType() const = 0;
	virtual const IOutlineStyle& GetOutlineStyle() const = 0;
	virtual IOutlineStyle& GetOutlineStyle() = 0;
	virtual const IStyle& GetFillStyle() const = 0;
	virtual IStyle& GetFillStyle() = 0;
	virtual const IGroup* GetGroup() const = 0;
	virtual IGroup* GetGroup()  = 0;
	virtual ~IShape() = default;
};

using IShapePtr = std::shared_ptr<IShape>;
