#pragma once
#include "CDocument.h"
#include "CMenu.h"
#include <functional>

class CEditor
{
public:
	CEditor();

	void Start();
private:
	typedef void (CEditor::* MenuHandler)(std::istream& args);

	void AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler);
	
	void InsertParagraph(std::istream& args);

	void InsertImage(std::istream& args);

	void SetTitle(std::istream& args);

	void List(std::istream& args);

	void ReplaceText(std::istream& args);

	void ResizeImage(std::istream& args);

	void DeleteItem(std::istream& args);

	void Undo(std::istream& args);

	void Redo(std::istream& args);

	void Save(std::istream& args);

	//void CheckPosForException(size_t pos);

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};