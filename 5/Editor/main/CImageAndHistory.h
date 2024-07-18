#pragma once
#include "CImage.h"
#include "CHistory.h"
#include "ChangeImageCommand.h"

class CImageAndHistory : public IImage
{
public:
	//приниматьпо значению и делать move
	CImageAndHistory(std::shared_ptr<IImage>& img, CHistory& history)
		: m_img(img)
		, m_history(history)
	{}

	std::string GetPath()const override
	{
		return m_img->GetPath();
	}

	int GetWidth()const override
	{
		return m_img->GetWidth();
	}

	int GetHeight()const override
	{
		return m_img->GetHeight();
	}

	void Resize(int width, int height) override
	{
		ICommandPtr command = std::make_unique<ChangeImageCommand>(m_img, std::make_shared
			<CImage>(m_img->GetPath(), width, height));
		m_history.AddAndExecuteCommand(move(command));
	}
private:
	CHistory& m_history;
	std::shared_ptr<IImage> m_img;
};