#pragma once
#include "ICommand.h"
#include <vector>
#include "CItems.h"

class CHistory
{
public:
	bool CanUndo() const
	{
		return m_currentCommandIdx != 0;
	}

	bool CanRedo() const
	{
		return m_currentCommandIdx != m_commands.size();
	}

	void Undo()
	{
		if (CanUndo())
		{
			m_commands[m_currentCommandIdx - 1]->UnExecute();
			m_currentCommandIdx--;
		}
	}

	void Redo()
	{
		if (CanRedo())
		{
			m_currentCommandIdx++;
			m_commands[m_currentCommandIdx - 1]->Execute();
		}		
	}

	void AddAndExecuteCommand(ICommandPtr&& command)
	{
		command->Execute();
		if (m_currentCommandIdx != m_commands.size())
		{
			m_commands.resize(m_currentCommandIdx);
		}
		if (m_commands.size() == 10)
		{
			m_commands.erase(m_commands.begin());
			m_currentCommandIdx--;
		}
		m_commands.push_back(move(command));
		m_currentCommandIdx++;

	}
private:
	std::vector<ICommandPtr> m_commands;
	size_t m_currentCommandIdx;
};