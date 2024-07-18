#pragma once
#include "AbstractCommand.h"
#include "IParagraph.h"

class ChangeParagraphCommand : public AbstractCommand
{
public:
	ChangeParagraphCommand(std::shared_ptr<IParagraph>& img, std::shared_ptr<IParagraph>&& copy)
		: m_paragraph(img)
		, m_paragraphCopy(move(copy))
	{
	}

	void DoExecute() override
	{
		m_paragraph.swap(m_paragraphCopy);
	}

	void DoUnExecute() override
	{
		m_paragraph.swap(m_paragraphCopy);
	}

private:
	std::shared_ptr<IParagraph>& m_paragraph;
	std::shared_ptr<IParagraph> m_paragraphCopy;
};