#include "CPicture.h"
#include "AddItemCommand.h"
#include "DeleteItemCommand.h"
#include "SwapTwoValuesCommand.h"
#include "CShapeAndHistory.h"
#include "CImageAndHistory.h"

Size CPicture::GetSize() const
{
	return m_size;
}

void CPicture::SetSize(Size size)
{
	ICommandPtr command = std::make_unique<SwapTwoValuesCommand<Size>>(m_size, size);
	m_changedData = { PictureOperations::CHANGE_SIZE, size };
	m_history.AddAndExecuteCommand(move(command));
	m_copySize = size;
	NotifyObservers();
}

size_t CPicture::GetShapesCount() const
{
	return m_items.size();
}

void CPicture::AddShape(IShapePtr shape)
{
	if (m_items.find(shape->GetId()) != m_items.end())
	{
		throw std::runtime_error("Shape with this id is already on picture");
	}
	IShapePtr shapeWithHistory = std::make_shared<CShapeAndHistory>(move(shape), m_history);
	auto id = shapeWithHistory->GetId();
	CDocumentItem item(move(shapeWithHistory));
	m_changedData = { PictureOperations::ADD_ITEM, item };
	ICommandPtr command = std::make_unique<AddItemCommand>(m_items, item);
	//m_shapes.insert({ shape->GetId(), move(shape) });
	m_history.AddAndExecuteCommand(move(command));
	m_copyItems.insert({ id, item });
	NotifyObservers();
}

void CPicture::AddImage(IImagePtr img)
{
	if (m_items.find(img->GetId()) != m_items.end())
	{
		throw std::runtime_error("Shape with this id is already on picture");
	}
	IImagePtr imageWithHistory = std::make_shared<CImageAndHistory>(move(img), m_history);
	auto id = imageWithHistory->GetId();
	CDocumentItem item(move(imageWithHistory));
	m_changedData = { PictureOperations::ADD_ITEM, item };
	ICommandPtr command = std::make_unique<AddItemCommand>(m_items, item);
	//m_shapes.insert({ shape->GetId(), move(shape) });
	m_history.AddAndExecuteCommand(move(command));
	m_copyItems.insert({ id, item });
	NotifyObservers();
}

void CPicture::DeleteItem(const std::string& id)
{
	if (m_items.find(id) == m_items.end())
	{
		throw std::runtime_error("There is no shape with this id on picture");
	}
	m_changedData = { PictureOperations::DELETE_SELECT_ITEM, m_items[id] };
	ICommandPtr command = std::make_unique<DeleteItemCommand>(m_items, id);
	m_history.AddAndExecuteCommand(move(command));
	m_copyItems.erase(id);
	NotifyObservers();
}

CConstDocumentItem CPicture::GetItem(const std::string& id) const
{
	return m_items.at(id);
}

CDocumentItem CPicture::GetItem(const std::string& id)
{
	if (m_items.find(id) == m_items.end())
	{
		throw std::runtime_error("There is no shape with this id on picture");
	}
	return m_items.at(id);
}

bool CPicture::CanUndo() const
{
	return m_history.CanUndo();
}

bool CPicture::CanRedo() const
{
	return m_history.CanRedo();
}

void CPicture::Undo()
{
	m_history.Undo();
	m_changedData = FindChangedData();
	m_copyItems = m_items;
	m_copySize = m_size;
	NotifyObservers();
}

void CPicture::Redo()
{
	m_history.Redo();
	m_changedData = FindChangedData();
	m_copyItems = m_items;
	m_copySize = m_size;
	NotifyObservers();
}

PictureDataToObserver CPicture::GetChangedData() const
{	
	return m_changedData;
}

PictureDataToObserver CPicture::FindChangedData()
{
	PictureDataToObserver data;
	if (m_size != m_copySize)
	{
		data = { PictureOperations::CHANGE_SIZE, m_size };
	}
	else if (m_items.size() != m_copyItems.size())
	{
		IPictureItemPtr sh;
		auto itOrig = m_items.begin();
		auto itCopy = m_copyItems.begin();
		while (itOrig != m_items.end() && itCopy != m_copyItems.end())
		{
			if (itOrig->first != itCopy->first && itOrig->second != itCopy->second)
			{
				if (m_items.size() > m_copyItems.size())
				{
					data = { PictureOperations::ADD_ITEM, itOrig->second };
					break;
				}
				else
				{
					data = { PictureOperations::DELETE_ITEM, itCopy->second };
					break;
				}
			}
			++itCopy;
			++itOrig;
		}
		if (itOrig != m_items.end())
		{
			data = { PictureOperations::ADD_ITEM, itOrig->second };
		}
		if (itCopy != m_copyItems.end())
		{
			data = { PictureOperations::DELETE_ITEM, itCopy->second };
		}
	}
	else if (m_items.size() == m_copyItems.size())
	{
		auto it = m_items.begin();
		while (it != m_items.end())
		{
			if (it->second.GetImage())
			{
				it->second.GetImage()->NotifyObservers();
			}
			else
				it->second.GetShape()->NotifyObservers();
			++it;
		}
	}
	return data;
}
