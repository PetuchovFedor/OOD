#include "CMenu.h"
#include <string>
#include <sstream>

void CMenu::AddItem(const std::string& shortcut, const std::string& description, const Command& command)
{
	m_items.push_back(Item(shortcut, description, command));
}

void CMenu::Run()
{
	ShowInstructions();
	std::string command;
	while (getline(std::cin, command))
	{
		try
		{
			if (!ExecuteCommand(command))
				break;
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

void CMenu::ShowInstructions() const
{
	std::cout << "Command list: " << std::endl;
	for (auto& item : m_items)
	{
		std::cout << item.shortcut << ": " << item.description << std::endl;
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const std::string& command)
{
	std::stringstream stream(command);
	std::string name;
	stream >> name;
	auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item)
		{
			return item.shortcut == name;
		});
	if (it == m_items.end())
	{
		std::cout << "Unknown command" << std::endl;
	}
	else
	{
		it->command(stream);
	}
	return !m_exit;
}
