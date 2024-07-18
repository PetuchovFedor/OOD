#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/CGroup.h"
#include "../main/IStyle.h"
#include "../main/IOutlineStyle.h"
#include "../main/CShape.h"
#include "../main/CTriangle.h"
#include "../main/CRectangle.h"
#include "../main/CEllipse.h"
//using namespace std;

TEST_CASE("Check group methods")
{
	GIVEN("Group")
	{
		CGroup g;
		WHEN("InsertShape, DeleteShape and GetShape")
		{
			IShapePtr sh1 = std::make_shared<CTriangle>(RectD({3, 4}, 4, 1));
			g.InsertShape(sh1, 0);
			REQUIRE(g.GetShapesCount() == 1);
			REQUIRE(g.GetShapeAtIndex(0) == sh1);
			WHEN("Remove")
			{
				REQUIRE_NOTHROW(g.RemoveShape(0));
				REQUIRE(g.GetShapesCount() == 0);
			}			
			WHEN("Insert and remove not at the end")
			{
				IShapePtr sh2 = std::make_shared<CTriangle>(RectD({ 3, 4 }, 4, 1));
				g.InsertShape(sh2, 1);				
				IShapePtr sh3 = std::make_shared<CTriangle>(RectD({ 3, 4 }, 4, 1));
				g.InsertShape(sh3, 2);				
				IShapePtr sh4 = std::make_shared<CTriangle>(RectD({ 3, 4 }, 4, 1));
				g.InsertShape(sh4, 3);
				IShapePtr sh5 = std::make_shared<CTriangle>(RectD({ 3, 4 }, 4, 1));
				g.InsertShape(sh5, 2);
				REQUIRE(sh5 == g.GetShapeAtIndex(2));
				g.RemoveShape(1);
				REQUIRE(g.GetShapeAtIndex(1) == sh5);
			}
		}
		/*WHEN("Frame Methods")
		{
			IShapePtr tr = std::make_shared<CTriangle>(RectD({ 3, 4 }, 4, 2));
			g.InsertShape(tr, 0);
			IShapePtr rect = std::make_shared<CRectangle>(RectD({ 1, 0 }, 2, 5));
			g.InsertShape(rect, 0);
			IShapePtr el = std::make_shared<CEllipse>(RectD({ 3, 4 }, 4, 1));
			g.InsertShape(el, 0);
			WHEN("GetFrame")
			{
				auto frame = g.GetFrame();
			}
		}*/
		WHEN("Styles methods")
		{
			IShapePtr tr = std::make_shared<CTriangle>(RectD({ 3, 4 }, 4, 1));
			g.InsertShape(tr, 0);
			IShapePtr rect = std::make_shared<CRectangle>(RectD({ 3, 4 }, 4, 1));
			g.InsertShape(rect, 0);
			IShapePtr el = std::make_shared<CEllipse>(RectD({ 3, 4 }, 4, 1));
			g.InsertShape(el, 0);
			WHEN("OutlineStyle")
			{
				WHEN("Initial values")
				{
					REQUIRE(g.GetOutlineStyle().GetColor() == 0xffffff);
					REQUIRE(g.GetOutlineStyle().GetThickness() == 2);
				}
				WHEN("Same colors and same thickness")
				{
					g.GetOutlineStyle().SetColor(0xffcfab66);
					g.GetOutlineStyle().SetThickess(5);
					REQUIRE(g.GetOutlineStyle().GetColor() == 0xffcfab66);
					REQUIRE(g.GetOutlineStyle().GetThickness() == 5);
				}
				WHEN("Differen color and thickness")
				{
					tr->GetOutlineStyle().SetColor(0xffe4c4);
					tr->GetOutlineStyle().SetThickess(6);
					el->GetOutlineStyle().SetColor(0xffcfab66);
					el->GetOutlineStyle().SetThickess(10);
					REQUIRE(g.GetOutlineStyle().GetColor() == std::nullopt);
					REQUIRE(g.GetOutlineStyle().GetThickness() == 0);
				}
			}
			WHEN("FillStyle")
			{
				WHEN("Initial values")
				{
					REQUIRE(g.GetFillStyle().GetColor() == 0xffffff);					
				}
				WHEN("Same colors and same thickness")
				{
					g.GetFillStyle().SetColor(0xffcfab66);					
					REQUIRE(g.GetFillStyle().GetColor() == 0xffcfab66);				
				}
				WHEN("Differen color and thickness")
				{
					tr->GetFillStyle().SetColor(0xffe4c4);
					el->GetFillStyle().SetColor(0xffcfab66);
					REQUIRE(g.GetFillStyle().GetColor() == std::nullopt);
				}
			}
		}
	}
}