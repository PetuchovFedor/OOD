#pragma once
#include "IShape.h"
#include "CHistory.h"
#include "SwapTwoValuesCommand.h"

class CShapeAndHistory : public IShape
{
public:
	CShapeAndHistory(IShapePtr shape, CHistory& history)
		: m_shape(move(shape))
		, m_history(history)
	{
		m_frame = m_shape->GetFrame();
	}

	std::string GetId() const  override
	{
		return m_shape->GetId();
	}

	ShapeTypes GetType() const override
	{
		return m_shape->GetType();
	}

	Rect GetFrame() const override
	{
		return m_frame;
	}

	void SetFrame(const Rect& frame)  override
	{
		m_shape->SetFrame(frame);
		ICommandPtr command =
			std::make_unique<SwapTwoValuesCommand<Rect>>(m_frame, frame);
		m_history.AddAndExecuteCommand(move(command));
		//m_rect = frame;
	}

	Point GetPosition() const override
	{
		return m_frame.leftTop;
	}

	void SetPosition(Point leftTop) override
	{
		m_shape->SetPosition(leftTop);
		ICommandPtr command =
			std::make_unique<SwapTwoValuesCommand<Point>>(m_frame.leftTop, leftTop);
		m_history.AddAndExecuteCommand(move(command));
	}

protected:
	Rect GetChangedData() const override
	{
		return m_frame;
	}

private:
	CHistory& m_history;
	Rect m_frame;
	IShapePtr m_shape;
};