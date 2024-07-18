#pragma once
#include "AbstractCommand.h"
#include "CItems.h"
#include <vector>
#include <optional>

class InsertItemCommand : public AbstractCommand
{
public:
	InsertItemCommand(std::vector<CDocumentItem>& items, 
		 CDocumentItem& item, std::optional<size_t>& position)
		: m_items(items)
		, m_item(item)
	{
		if (position.has_value())
		{
			m_pos = position.value();
		}
		else
		{
			m_pos = items.size();
		}
	}

	void DoExecute() override
	{
		if (m_pos == m_items.size())
			m_items.push_back(m_item);
		else
			m_items.insert(m_items.begin() + m_pos, m_item);
	}

	void DoUnExecute() override
	{
		m_items.erase(m_items.begin() + m_pos);
	}

	~InsertItemCommand()
	{
		auto it = std::find(m_items.begin(), m_items.end(), m_item);
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
	std::vector<CDocumentItem>& m_items;
	CDocumentItem m_item;
	size_t m_pos;

};