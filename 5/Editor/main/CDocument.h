#pragma once
#include <vector>
#include "IDocument.h"
#include "CItems.h"
#include "CHistory.h"

class CDocument : public IDocument
{
public:
	CDocument();
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position) override;

	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
		std::optional<size_t> position) override;

	size_t GetItemsCount()const override;

	CConstDocumentItem GetItem(size_t index)const override;

	CDocumentItem GetItem(size_t index) override;

	void DeleteItem(size_t index) override;

	std::string GetTitle()const override;

	void SetTitle(const std::string& title) override;

	bool CanUndo()const override;

	void Undo() override;

	bool CanRedo()const override;

	void Redo() override;

	void Save(const std::string& path)const override;

	~CDocument();
private:
	void CheckPosForException(size_t pos);
	std::filesystem::path m_pathToTmpImagesDir;
	CHistory m_history;
	std::string m_title;
	std::vector<CDocumentItem> m_items;
};