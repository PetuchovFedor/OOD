#pragma once
#include "IParagraph.h"
#include "CHistory.h"
#include "ChangeParagraphCommand.h"

class CParagraphAndHistory : public IParagraph
{
public:
	CParagraphAndHistory(std::shared_ptr<IParagraph>& p, CHistory& history)
		: m_paragraph(p)
		, m_history(history)
	{
		//m_paragraphText = ;
	}

	std::string GetText()const override
	{
		return m_paragraph->GetText();
	}

	void SetText(const std::string& text) override
	{
		ICommandPtr command = std::make_unique<ChangeParagraphCommand>(m_paragraph, 
			std::make_shared<CParagraph>(text));
		m_history.AddAndExecuteCommand(move(command));
	}
private:
	std::shared_ptr<IParagraph> m_paragraph;
	CHistory& m_history;
};