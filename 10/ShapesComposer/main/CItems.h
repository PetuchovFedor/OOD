#pragma once
#include <memory>
#include "IShape.h"
#include "IImage.h"
#include <variant>

class CConstDocumentItem
{
public:

	CConstDocumentItem(std::shared_ptr<IImage> img)
		: m_id(img->GetId())
		, m_item(img)
	{
		//m_item = img;
	}

	bool operator==(const CConstDocumentItem& other) const
	{
		return m_item == other.m_item;
	}

	CConstDocumentItem()
	{}
	CConstDocumentItem(std::shared_ptr<IShape> shape)
		: m_id(shape->GetId())
		, m_item(shape) 
	{
	}

	std::string GetId() const
	{
		return m_id;
	}
	// Возвращает указатель на константное изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const
	{
		auto imgPtr = std::get_if< std::shared_ptr<IImage>>(&m_item);
		if (imgPtr)
			return *imgPtr;
		return nullptr;
	}
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IShape> GetShape()const
	{
		auto shapePtr = std::get_if< std::shared_ptr<IShape>>(&m_item);
		if (shapePtr)
			return *shapePtr;
		return nullptr;
	}
	virtual ~CConstDocumentItem() = default;
private:
	std::variant< std::shared_ptr<IImage>, std::shared_ptr<IShape>> m_item;
	std::string m_id;
};

class CDocumentItem : public CConstDocumentItem
{
public:

	CDocumentItem(std::shared_ptr<IImage> img)
		: CConstDocumentItem(img)
	{}

	CDocumentItem(std::shared_ptr<IShape> paragraph)
		: CConstDocumentItem(paragraph)
	{}

	CDocumentItem()
		: CConstDocumentItem()
	{}
	/*bool operator==(const CDocumentItem& other) const
	{
		;
	}*/

	std::string GetId() const
	{
		return CConstDocumentItem::GetId();
	}

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage()
	{
		auto constImg = CConstDocumentItem::GetImage();
		if (constImg)
		{
			auto img = std::const_pointer_cast<IImage>(constImg);
			return img;
		}
		//IImage* imgPtr = CConstDocumentItem::GetImage().get();
		//auto img = CConstDocumentItem::GetImage().get();
		//return std::make_shared<IImage>(const_cast<IImage*>(img));
		return nullptr;
	}
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IShape> GetShape()
	{
		auto constS = CConstDocumentItem::GetShape();
		if (constS)
		{
			auto sh = std::const_pointer_cast<IShape>(constS);
			return sh;
		}
		//auto p = CConstDocumentItem::GetParagraph().get();
		//return std::make_shared<IParagraph>(const_cast<IParagraph*>(p));
		return nullptr;
	}
};