#pragma once
#include "AbstractCommand.h"
#include "IPictureItem.h"
#include <map>
#include <optional>

class DeleteItemCommand : public AbstractCommand
{
public:
	DeleteItemCommand(std::map<std::string, CDocumentItem>& items,
		const std::string& id)
		: m_items(items)
		, m_item(items.at(id))
		, m_id(id)
	{
	}

	void DoExecute() override
	{
		m_items.erase(m_id);
	}

	void DoUnExecute() override
	{
		m_items.insert({ m_id, m_item });
	}

	~DeleteItemCommand()
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
	std::string m_id;
};