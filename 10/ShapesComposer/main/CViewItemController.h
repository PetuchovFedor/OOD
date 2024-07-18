#pragma once
#include "IViewItemController.h"

class CViewItemController : public IViewItemController
{
public:
	CViewItemController(IPictureItemPtr model)
		: m_model(model)
	{}

	void SetPosition(Point pos) override
	{
		m_model->SetPosition(pos);
	}

	void SetFrame(const Rect& frame) override
	{
		m_model->SetFrame(frame);
	}
private:
	IPictureItemPtr m_model;
};