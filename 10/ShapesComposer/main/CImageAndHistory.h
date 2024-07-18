#pragma once
#include "IImage.h"
#include "CHistory.h"
#include "SwapTwoValuesCommand.h"

class CImageAndHistory : public IImage
{
public:
	CImageAndHistory(IImagePtr img, CHistory& history)
		: m_img(move(img))
		, m_history(history)
	{
		m_frame = m_img->GetFrame();
	}

	std::string GetId() const  override
	{
		return m_img->GetId();
	}

	Rect GetFrame() const override
	{
		return m_frame;
	}

	void SetFrame(const Rect& frame)  override
	{
		m_img->SetFrame(frame);
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
		m_img->SetPosition(leftTop);
		ICommandPtr command =
			std::make_unique<SwapTwoValuesCommand<Point>>(m_frame.leftTop, leftTop);
		m_history.AddAndExecuteCommand(move(command));
	}

	std::filesystem::path GetPath() const override
	{
		return m_img->GetPath();
	}

protected:
	Rect GetChangedData() const override
	{
		return m_frame;
	}

private:
	CHistory& m_history;
	Rect m_frame;
	IImagePtr m_img;
};