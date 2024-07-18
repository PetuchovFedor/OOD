#pragma once
#include "AbstractCommand.h"
#include "IImage.h"
#include "CImage.h"

class ChangeImageCommand : public AbstractCommand
{
public:
	ChangeImageCommand(std::shared_ptr<IImage>& img, std::shared_ptr<IImage>&& copy)
		: m_img(img)
		, m_imgCopy(move(copy))
	{
	}

	void DoExecute() override
	{
		m_img.swap(m_imgCopy);
	}

	void DoUnExecute() override
	{
		m_img.swap(m_imgCopy);
	}

private:
	std::shared_ptr<IImage>& m_img;
	std::shared_ptr<IImage> m_imgCopy;
	//std::pair<int, int> m_oldSizes;
	//std::pair<int, int> m_newSizes;
};
