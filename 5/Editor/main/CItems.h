#pragma once
#include <memory>
#include "IParagraph.h"
#include "IImage.h"
#include <variant>

class CConstDocumentItem
{
public:

	CConstDocumentItem(std::shared_ptr<IImage>& img)
		: m_item(img)
	{
		//m_item = img;
	}

	bool operator==(const CConstDocumentItem& other) const
	{
		return m_item == other.m_item;
	}

	CConstDocumentItem(std::shared_ptr<IParagraph>& paragraph)
		: m_item(paragraph)
	{
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
	std::shared_ptr<const IParagraph> GetParagraph()const
	{
		auto paragraphPtr = std::get_if< std::shared_ptr<IParagraph>>(&m_item);
		if (paragraphPtr)
			return *paragraphPtr;
		return nullptr;
	}
	virtual ~CConstDocumentItem() = default;
private:
	std::variant< std::shared_ptr<IImage>, std::shared_ptr<IParagraph>> m_item;
};

class CDocumentItem : public CConstDocumentItem
{
public:

	CDocumentItem(std::shared_ptr<IImage>& img)
		: CConstDocumentItem(img)
	{}

	CDocumentItem(std::shared_ptr<IParagraph>& paragraph)
		: CConstDocumentItem(paragraph)
	{}

	/*bool operator==(const CDocumentItem& other) const
	{
		;
	}*/

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
	std::shared_ptr<IParagraph> GetParagraph()
	{
		auto constP = CConstDocumentItem::GetParagraph();
		if (constP)
		{
			auto paragraph = std::const_pointer_cast<IParagraph>(constP);
			return paragraph;
		}
		//auto p = CConstDocumentItem::GetParagraph().get();
		//return std::make_shared<IParagraph>(const_cast<IParagraph*>(p));
		return nullptr;
	}
};