#pragma once
#include "AbstractCommand.h"
#include "IShape.h"
#include <map>
#include <optional>

class AddItemCommand : public AbstractCommand
{
public:
	AddItemCommand(std::map<std::string, CDocumentItem>& items,
		CDocumentItem item)
		: m_items(items)
		, m_item(item)
	{
	}

	void DoExecute() override
	{
		m_items.insert({ m_item.GetId(), m_item });
	}

	void DoUnExecute() override
	{
		m_items.erase(m_item.GetId());
	}

	~AddItemCommand()
	{
		auto it = m_items.find(m_item.GetId());
		if (it == m_items.end())
		{
			auto img = m_item.GetImage();
			if (img && std::filesystem::exists(img->GetPath()))
			{
				std::filesystem::remove(img->GetPath());
			}
		}
	}
private:
	std::map<std::string, CDocumentItem>& m_items;
	CDocumentItem m_item;
};