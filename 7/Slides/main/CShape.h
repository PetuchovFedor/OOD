#pragma once
#include "IShape.h"
#include "CFillStyle.h"
#include "COutlineStyle.h"

class CShape : public IShape
{
public:
	CShape(const RectD& rect)
		: m_rect(rect)
	{}

	RectD GetFrame() const override
	{
		return m_rect;
	}

	void SetFrame(const RectD& frame) override
	{
		m_rect = frame;
	}

	const IOutlineStyle& GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}

	IOutlineStyle& GetOutlineStyle() override
	{
		return m_outlineStyle;
	}

	const IStyle& GetFillStyle() const override
	{
		return m_fillStyle;
	}

	IStyle& GetFillStyle() override
	{
		return m_fillStyle;
	}
	//void Draw(ICanvas& canvas) const override;
	
	const IGroup* GetGroup() const override
	{
		return nullptr;
	}

	IGroup* GetGroup() override
	{
		return nullptr;
	}

private:
	RectD m_rect;
	CFillStyle m_fillStyle;
	COutlineStyle m_outlineStyle;
};