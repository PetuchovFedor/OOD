#pragma once
#include "ICommand.h"

class AbstractCommand : public ICommand
{
public:
	void Execute() final
	{
		if (!m_executed)
		{
			DoExecute();
			m_executed = true;
		}
	}

	void UnExecute() final
	{
		if (m_executed)
		{
			DoUnExecute();
			m_executed = false;
		}
	}

protected:
	virtual void DoExecute() = 0;
	virtual void DoUnExecute() = 0;

private:
	bool m_executed = false;
};