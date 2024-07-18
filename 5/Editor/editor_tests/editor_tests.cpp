#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CImage.h"
#include <iostream>
#include "../main/CParagraph.h"
#include "../main/CItems.h"
#include "../main/CDocument.h"
#include "../main/CHistory.h"
#include "../main/InsertItemCommand.h"
#include "../main/CImageAndHistory.h"
#include "../main/ChangeImageCommand.h"
#include "../main/ChangeParagraphCommand.h"
#include "../main/ChangeStringCommand.h"
#include "../main/DeleteItemCommand.h"
#include "../main/CParagraphAndHistory.h"
using namespace std;
namespace fs = std::filesystem;

TEST_CASE("Chech CImage Methods")
{
	CImage img("qwerty.jpg", 300, 300);
	WHEN("GetPath()")
	{
		REQUIRE("qwerty.jpg" == img.GetPath());
	}
	WHEN("GetSizes()")
	{
		REQUIRE(img.GetHeight() == 300); 
		REQUIRE(img.GetWidth() == 300);
	}
	WHEN("Resize()")
	{
		img.Resize(120, 400);
		REQUIRE(img.GetHeight() == 400); 
		REQUIRE(img.GetWidth() == 120);
	}
}

TEST_CASE("Check Parargraph method")
{
	CParagraph p("qwerty");
	WHEN("GetText")
	{
		REQUIRE("qwerty" == p.GetText());
	}
	WHEN("SetText")
	{
		p.SetText("123456789");
		REQUIRE(p.GetText() == "123456789");
	}
}

TEST_CASE("Check Items")
{
	shared_ptr<IImage> img = make_shared<CImage>("qwerty.jpg", 300, 300);
	shared_ptr<IParagraph> p = make_shared<CParagraph>("qwerty");
	WHEN("CConstDocumentItem")
	{
		WHEN("img constructor")
		{
			CConstDocumentItem item(img);
			THEN("GetImage")
			{
				REQUIRE(item.GetImage() == img);
			}
			THEN("GetParagraph")
			{
				REQUIRE(item.GetParagraph() == nullptr);
			}
		}
		WHEN("paragraph constructor")
		{
			CConstDocumentItem item(p);
			THEN("GetImage")
			{
				REQUIRE(item.GetImage() == nullptr);
			}
			THEN("GetParagraph")
			{
				REQUIRE(item.GetParagraph() == p);
			}
		}
	}
	WHEN("CDocumentItem")
	{
		WHEN("img constructor")
		{
			CDocumentItem item(img);
			THEN("GetImage")
			{
				REQUIRE(item.GetImage() == img);				
			}
			THEN("GetParagraph")
			{
				REQUIRE(item.GetParagraph() == nullptr);
			}
		}
		WHEN("paragraph constructor")
		{
			CConstDocumentItem item(p);
			THEN("GetImage")
			{
				REQUIRE(item.GetImage() == nullptr);
			}
			THEN("GetParagraph")
			{
				REQUIRE(item.GetParagraph() == p);
			}
		}
	}
}

TEST_CASE("Check History")
{
	CHistory history;
	WHEN("CanUndo empty history")
	{
		REQUIRE(!history.CanUndo());
	}
	WHEN("InsertItem And ChangeItem")
	{
		WHEN("Image")
		{
			std::vector<CDocumentItem> items;
			shared_ptr<IImage> img = make_shared<CImage>("qwerty.jpg", 300, 300);
			shared_ptr<IImage> imgAndHistory = make_shared<CImageAndHistory>(img, history);
			CDocumentItem item(img);
			optional<size_t> pos = nullopt;
			ICommandPtr command = make_unique<InsertItemCommand>(items, item, pos);
			history.AddAndExecuteCommand(move(command));
			REQUIRE(items[0] == item);
			WHEN("Undo")
			{
				history.Undo();
				REQUIRE(items.empty());
				WHEN("Redo")
				{
					history.Redo();
					REQUIRE(items[0] == item);
					THEN("CanRedo()")
					{
						REQUIRE(!history.CanRedo());
					}
				}
			}
			WHEN("ResizeImage")
			{
				imgAndHistory->Resize(400, 400);
				REQUIRE(imgAndHistory->GetHeight() == 400);
				REQUIRE(imgAndHistory->GetWidth() == 400);
				WHEN("Undo")
				{
					history.Undo();
					REQUIRE(imgAndHistory->GetHeight() == 300);
					REQUIRE(imgAndHistory->GetWidth() == 300);
					WHEN("Redo")
					{
						history.Redo();
						REQUIRE(imgAndHistory->GetHeight() == 400);
						REQUIRE(imgAndHistory->GetWidth() == 400);
					}
				}
			}
		}
		WHEN("Paragraph")
		{
			std::vector<CDocumentItem> items;
			shared_ptr<IParagraph> p = make_shared<CParagraph>("qwerty");
			shared_ptr<IParagraph> pAndHistory = make_shared<CParagraphAndHistory>(p, history);
			CDocumentItem item(p);
			optional<size_t> pos = nullopt;
			ICommandPtr command = make_unique<InsertItemCommand>(items, item, pos);
			history.AddAndExecuteCommand(move(command));
			REQUIRE(items[0] == item);
			WHEN("Undo")
			{
				history.Undo();
				REQUIRE(items.empty());
				WHEN("Redo")
				{
					history.Redo();
					REQUIRE(items[0] == item);
					THEN("CanRedo()")
					{
						REQUIRE(!history.CanRedo());
					}
				}
			}
			WHEN("SetText")
			{
				pAndHistory->SetText("12345");
				REQUIRE(pAndHistory->GetText() == "12345");
				WHEN("Undo")
				{
					history.Undo();
					REQUIRE(pAndHistory->GetText() == "qwerty");
					WHEN("Redo")
					{
						history.Redo();
						REQUIRE(pAndHistory->GetText() == "12345");
					}
				}
			}
		}
	}
	WHEN("ChangeString")
	{
		string str1 = "qwerty";
		string str2 = "12345";
		ICommandPtr command = make_unique<ChangeStringCommand>(str1, str2);
		history.AddAndExecuteCommand(move(command));
		WHEN("Undo")
		{
			history.Undo();
			REQUIRE(str1 == "qwerty");
			WHEN("Redo")
			{
				history.Redo();
				REQUIRE(str1 == "12345");
			}
		}
	}
	WHEN("DeleteItem")
	{
		vector<CDocumentItem> items;
		shared_ptr<IParagraph> p = make_shared<CParagraph>("qwerty");
		CDocumentItem item(p);
		optional<size_t> pos = nullopt;
		ICommandPtr command = make_unique<InsertItemCommand>(items, item, pos);
		history.AddAndExecuteCommand(move(command));
		REQUIRE(items[0] == item);
		ICommandPtr command1 = make_unique<DeleteItemCommand>(items, 0);
		history.AddAndExecuteCommand(move(command1));
		REQUIRE(items.empty());
		WHEN("Undo")
		{
			history.Undo();
			REQUIRE(items[0] == item);
			WHEN("Redo")
			{
				history.Redo();
				REQUIRE(items.empty());
			}
		}
	}

	WHEN("Situation with new history")
	{
		vector<CDocumentItem> items;
		shared_ptr<IParagraph> p = make_shared<CParagraph>("qwerty");
		CDocumentItem item(p);
		optional<size_t> pos = nullopt;
		ICommandPtr command = make_unique<InsertItemCommand>(items, item, pos);
		history.AddAndExecuteCommand(move(command));
		REQUIRE(items[0] == item);
		history.Undo();
		REQUIRE(items.empty());
		shared_ptr<IParagraph> p1 = make_shared<CParagraph>("asdfg");
		CDocumentItem item1(p1);
		ICommandPtr command1 = make_unique<InsertItemCommand>(items, item1, pos);
		history.AddAndExecuteCommand(move(command1));
		REQUIRE(items[0] == item1);
		history.Undo();
		REQUIRE(!history.CanUndo());
	}
}

TEST_CASE("Check Document")
{
	CDocument doc;
	REQUIRE(fs::exists("images"));
	doc.InsertParagraph("qwerty", nullopt);
	doc.InsertParagraph("asdff", nullopt);
	doc.InsertImage("D:/User Files/Desktop/OjKj4gvUa3c.jpg", 200, 200, optional<size_t>(1));
	WHEN("InsertItems")
	{		
		REQUIRE(doc.GetItemsCount() == 3);
		auto img = doc.GetItem(1).GetImage();
		REQUIRE(img);
		REQUIRE(fs::exists(img->GetPath()));
		THEN("If Undo the physical deletion of the image will not happen")
		{
			doc.Undo();
			REQUIRE(!doc.GetItem(1).GetImage());
			REQUIRE(fs::exists(img->GetPath()));
			WHEN("If you start a new round of history, the picture will be physically deleted")
			{
				doc.InsertParagraph("1234", nullopt);
				REQUIRE(!fs::exists(img->GetPath()));
			}
		}
	}
	WHEN("Check length history")
	{
		for (size_t i = 0; i < 10; i++)
		{
			doc.InsertParagraph("qwerty", nullopt);
		}
		for (size_t i = 0; i < 10; i++)
		{
			doc.Undo();
		}
		REQUIRE(!doc.CanUndo());
	}
	WHEN("ModifyItems")
	{
		auto p = doc.GetItem(0).GetParagraph();
		auto img = doc.GetItem(1).GetImage();
		REQUIRE(p);
		REQUIRE(img);
		WHEN("ChangeParagraph")
		{
			REQUIRE(p->GetText() == "qwerty");
			p->SetText("12345");
			REQUIRE(p->GetText() == "12345");
			REQUIRE(doc.GetItem(0).GetParagraph()->GetText() == p->GetText());
			WHEN("Undo")
			{
				doc.Undo();
				REQUIRE(p->GetText() == "qwerty");
				REQUIRE(doc.GetItem(0).GetParagraph()->GetText() == "qwerty");
				WHEN("Redo")
				{
					doc.Redo();
					REQUIRE(p->GetText() == "12345");
					REQUIRE(doc.GetItem(0).GetParagraph()->GetText() == "12345");
				}
			}
		}
		WHEN("ChangeImage")
		{
			REQUIRE(img->GetWidth() == 200);
			REQUIRE(img->GetHeight() == 200);
			img->Resize(300, 300);
			REQUIRE(img->GetWidth() == 300);
			REQUIRE(img->GetHeight() == 300);
			REQUIRE(img->GetWidth() == doc.GetItem(1).GetImage()->GetWidth());
			REQUIRE(img->GetHeight() == doc.GetItem(1).GetImage()->GetHeight());
			WHEN("Undo")
			{
				doc.Undo();
				REQUIRE(img->GetWidth() == 200);
				REQUIRE(img->GetHeight() == 200);
				REQUIRE(doc.GetItem(1).GetImage()->GetWidth() == 200);
				REQUIRE(doc.GetItem(1).GetImage()->GetHeight() == 200);
				WHEN("Redo")
				{
					doc.Redo();
					REQUIRE(img->GetWidth() == 300);
					REQUIRE(img->GetHeight() == 300);
					REQUIRE(doc.GetItem(1).GetImage()->GetWidth() == 300);
					REQUIRE(doc.GetItem(1).GetImage()->GetHeight() == 300);
				}
			}
		}
		WHEN("CheckTitle")
		{
			doc.SetTitle("tests");
			REQUIRE(doc.GetTitle() == "tests");
			doc.SetTitle("not-tests");
			REQUIRE(doc.GetTitle() == "not-tests");
			WHEN("Undo")
			{
				doc.Undo();
				REQUIRE(doc.GetTitle() == "tests");
				WHEN("Redo")
				{
					doc.Redo();
					REQUIRE(doc.GetTitle() == "not-tests");
				}
			}
		}
		WHEN("DeleteItem")
		{
			auto img = doc.GetItem(1).GetImage();
			doc.DeleteItem(1);
			REQUIRE(!doc.GetItem(1).GetImage());
			THEN("does not lead to physical deletion")
			{
				REQUIRE(fs::exists(img->GetPath()));
			}
			WHEN("Undo")
			{
				doc.Undo();
				REQUIRE(doc.GetItem(1).GetImage());
				WHEN("Redo")
				{
					doc.Redo();
					REQUIRE(!doc.GetItem(1).GetImage());
					WHEN("commands count > 10, img deleted physically")
					{
						for (size_t i = 0; i < 10; i++)
						{
							doc.InsertParagraph("qwerty", nullopt);
						}
						REQUIRE(!fs::exists(img->GetPath()));
					}
				}				
			}
		}
	}
}