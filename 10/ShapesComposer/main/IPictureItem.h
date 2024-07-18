#pragma once
#include "CommonTypes.h"
#include "Observer.h"
#include <string>
#include <memory>

class IPictureItem : public CObservable<Rect>
{
public:
	virtual Rect GetFrame() const = 0;
	virtual void SetFrame(const Rect& frame) = 0;
	virtual std::string GetId() const = 0;
	virtual Point GetPosition() const = 0;
	virtual void SetPosition(Point leftTop) = 0;
	virtual ~IPictureItem() = default;
};

using IPictureItemPtr = std::shared_ptr<IPictureItem>;