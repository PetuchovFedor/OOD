#pragma once
#include "AbstractCommand.h"
#include <vector>
#include "CItems.h"

class DeleteItemCommand : public AbstractCommand
{
public:
	DeleteItemCommand(std::vector<CDocumentItem>& items, size_t idx)
		: m_items(items)
		, m_index(idx)
		, m_item(items[idx])
	{
	}

	void DoExecute() override
	{
		m_items.erase(m_items.begin() + m_index);
	}

	void DoUnExecute() override
	{
		m_items.insert(m_items.begin() + m_index, m_item);
	}

	~DeleteItemCommand()
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
	size_t m_index;
};