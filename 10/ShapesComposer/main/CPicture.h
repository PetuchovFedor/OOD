#pragma once
#include "PictureData.h"
#include "Observer.h"
#include <map>
#include <stdexcept>
#include "CHistory.h"
#include "CItems.h"

class CPicture : public CObservable<PictureDataToObserver>
{
public:
	CPicture(Size size)
		: m_size(size)
	{

	}

	Size GetSize() const;

	void SetSize(Size size);

	size_t GetShapesCount() const;

	void AddShape(IShapePtr shape);

	void AddImage(IImagePtr img);


	void DeleteItem(const std::string& id);

	CConstDocumentItem GetItem(const std::string& id) const;

	CDocumentItem GetItem(const std::string& id);

	bool CanUndo() const;

	bool CanRedo() const;

	void Undo();

	void Redo();

protected:
	PictureDataToObserver GetChangedData() const override;

	PictureDataToObserver FindChangedData();
private:

	PictureDataToObserver m_changedData;
	std::map<std::string, CDocumentItem> m_items, m_copyItems;
	Size m_size, m_copySize;
	CHistory m_history;
};