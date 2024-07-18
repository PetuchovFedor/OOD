#pragma once
#include <variant>
#include "CItems.h"

enum class PictureOperations
{
	ADD_ITEM,
	DELETE_SELECT_ITEM,
	DELETE_ITEM,
	CHANGE_SIZE,
	NONE
};

class PictureDataToObserver
{
public:
	PictureDataToObserver()
		: m_operation(PictureOperations::NONE)
		, m_data(Size(0,0))
	{}
	PictureDataToObserver(PictureOperations operation, CDocumentItem data)
		: m_operation(operation)
		, m_data(data)
	{}

	PictureDataToObserver(PictureOperations operation, Size size)
		: m_operation(operation)
		, m_data(size)
	{}

	PictureOperations GetOperation() const
	{
		return m_operation;
	}

	CDocumentItem* GetItem() const
	{
		const CDocumentItem* itemPtr = std::get_if<CDocumentItem>(&m_data);
		if (itemPtr)
			return const_cast<CDocumentItem*>(itemPtr);
		return nullptr;
	}

	Size* GetSize() const
	{
		const Size* sizePtr = std::get_if<Size>(&m_data);
		if (sizePtr)
			return const_cast<Size*>(sizePtr);
		return nullptr;
	}

private:
	PictureOperations m_operation;
	std::variant<CDocumentItem, Size> m_data;
};