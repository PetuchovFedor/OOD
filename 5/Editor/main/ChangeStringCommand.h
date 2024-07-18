#pragma once
#include "AbstractCommand.h"
#include <string>

class ChangeStringCommand : public AbstractCommand
{
public:
	ChangeStringCommand(std::string& target, std::string const& newValue)
		: m_target(target)
		, m_newValue(newValue)
	{
	}

	void DoExecute() override
	{
		m_newValue.swap(m_target);
	}

	void DoUnExecute() override
	{
		m_newValue.swap(m_target);
	}

private:
	std::string m_newValue;
	std::string& m_target;
};