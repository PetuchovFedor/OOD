#pragma once
#include "IPictureItem.h"
#include "CHistory.h"
#include "SwapTwoValuesCommand.h"

class CPictureItemAndHistory : public IPictureItem
{
public:
	CPictureItemAndHistory(IPictureItemPtr item, CHistory& history)
		: m_item(move(item))
		, m_history(history)
	{
		m_frame = m_item->GetFrame();
	}

	ItemType GetItemType() const
	{
		return m_item->GetItemType();
	}

	std::string GetId() const  override
	{
		return m_item->GetId();
	}

	Rect GetFrame() const override
	{
		return m_frame;
	}

	void SetFrame(const Rect& frame)  override
	{
		m_item->SetFrame(frame);
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
		m_item->SetPosition(leftTop);
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
	IPictureItemPtr m_item;
};