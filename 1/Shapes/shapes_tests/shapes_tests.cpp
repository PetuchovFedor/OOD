#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include "../main/Shape.h"
#include "../main/CircleStrategy.h"
#include "../main/LineStrategy.h"
#include "../main/RectangleStrategy.h"
#include "../main/TextStrategy.h"
#include "../main/TriangleStrategy.h"
#include "../main/Picture.h"
#include "MockCanvas.h"

using namespace shapes;
using namespace std;

TEST_CASE("Checking shape method")
{
	GIVEN("Line")
	{
		Shape shape("1", "#000000", make_unique<LineStrategy>(Point(10, 80), Point(15, 90)));
		WHEN("Move and ToString")
		{
			shape.Move(Point(10, 10));
			REQUIRE(shape.ToString() == "line 1 #000000 20 90 25 100"s);
		}
		WHEN("GetId")
		{
			REQUIRE(shape.GetId() == "1"s);
		}
		WHEN("GetColor")
		{
			REQUIRE(shape.GetColor() == "#000000"s);
		}
		WHEN("ChangeColor")
		{
			shape.ChangeColor("#123456");
			REQUIRE(shape.GetColor() == "#123456"s);
		}
		WHEN("Draw")
		{
			MockCanvas mock;
			shape.Draw(mock);
			auto me = mock.GetMethods();
			auto args = mock.GetArgs();
			REQUIRE(me[0] == MockCanvas::ExecutedMethods::MoveTo);
			REQUIRE(me[1] == MockCanvas::ExecutedMethods::LineTo);
			cout << args[0] << endl;
			cout << args[1] << endl;
		}
		WHEN("ChangeShape")
		{
			shape.ChangeShape(make_unique<CircleStrategy>(Point(50, 50), 50));
			REQUIRE(shape.ToString() == "circle 1 #000000 50 50 50"s);
		}
	}
	GIVEN("Circle")
	{
		Point center(50, 50);

		Shape shape("1", "#000000", make_unique<CircleStrategy>(center, 50));
		WHEN("Move and ToString")
		{
			shape.Move(Point(10, 10));
			REQUIRE(shape.ToString() == "circle 1 #000000 60 60 50"s);
		}
		WHEN("GetId")
		{
			REQUIRE(shape.GetId() == "1"s);
		}
		WHEN("GetColor")
		{
			REQUIRE(shape.GetColor() == "#000000"s);
		}
		WHEN("ChangeColor")
		{
			shape.ChangeColor("#123456");
			REQUIRE(shape.GetColor() == "#123456"s);
		}
		WHEN("Draw")
		{
			MockCanvas mock;
			shape.Draw(mock);
			auto me = mock.GetMethods();
			auto args = mock.GetArgs();
			cout << args[0] << endl;
		}
		WHEN("ChangeShape")
		{
			shape.ChangeShape(make_unique<LineStrategy>(Point(10, 80), Point(15, 90)));
			REQUIRE(shape.ToString() == "line 1 #000000 10 80 15 90"s);
		}
		
	}
	GIVEN("Rectangle")
	{
		Point leftTop(50, 50);

		Shape shape("1", "#000000", make_unique<RectangleStrategy>(leftTop, 50, 50));
		WHEN("Move and ToString")
		{
			shape.Move(Point(10, 10));
			REQUIRE(shape.ToString() == "rectangle 1 #000000 60 60 50 50"s);
		}
		WHEN("GetId")
		{
			REQUIRE(shape.GetId() == "1"s);
		}
		WHEN("GetColor")
		{
			REQUIRE(shape.GetColor() == "#000000"s);
		}
		WHEN("ChangeColor")
		{
			shape.ChangeColor("#123456");
			REQUIRE(shape.GetColor() == "#123456"s);
		}
		WHEN("Draw")
		{
			MockCanvas mock;
			shape.Draw(mock);
			auto me = mock.GetMethods();
			auto args = mock.GetArgs();
			copy(args.begin(), args.end(), std::ostream_iterator<std::string>(cout, "\n"));
		}
		WHEN("ChangeShape")
		{
			shape.ChangeShape(make_unique<LineStrategy>(Point(10, 80), Point(15, 90)));
			REQUIRE(shape.ToString() == "line 1 #000000 10 80 15 90"s);
		}

	}
	GIVEN("Triangle")
	{

		Shape shape("1", "#000000", make_unique<TriangleStrategy>(Point(10, 10), Point(20, 20), Point(30, 30)));
		WHEN("Move and ToString")
		{
			shape.Move(Point(10, 10));
			REQUIRE(shape.ToString() == "triangle 1 #000000 20 20 30 30 40 40"s);
		}
		WHEN("GetId")
		{
			REQUIRE(shape.GetId() == "1"s);
		}
		WHEN("GetColor")
		{
			REQUIRE(shape.GetColor() == "#000000"s);
		}
		WHEN("ChangeColor")
		{
			shape.ChangeColor("#123456");
			REQUIRE(shape.GetColor() == "#123456"s);
		}
		WHEN("Draw")
		{
			MockCanvas mock;
			shape.Draw(mock);
			auto me = mock.GetMethods();
			auto args = mock.GetArgs();
			copy(args.begin(), args.end(), std::ostream_iterator<std::string>(cout, "\n"));
		}
		WHEN("ChangeShape")
		{
			shape.ChangeShape(make_unique<LineStrategy>(Point(10, 80), Point(15, 90)));
			REQUIRE(shape.ToString() == "line 1 #000000 10 80 15 90"s);
		}
	}
	GIVEN("Text")
	{
		Point leftTop(50, 50);

		Shape shape("1", "#000000", make_unique<TextStrategy>(leftTop, 14, "qwerty"));
		WHEN("Move and ToString")
		{
			shape.Move(Point(10, 10));
			REQUIRE(shape.ToString() == "text 1 #000000 60 60 14 qwerty"s);
		}
		WHEN("GetId")
		{
			REQUIRE(shape.GetId() == "1"s);
		}
		WHEN("GetColor")
		{
			REQUIRE(shape.GetColor() == "#000000"s);
		}
		WHEN("ChangeColor")
		{
			shape.ChangeColor("#123456");
			REQUIRE(shape.GetColor() == "#123456"s);
		}
		WHEN("Draw")
		{
			MockCanvas mock;
			shape.Draw(mock);
			auto me = mock.GetMethods();
			auto args = mock.GetArgs();
			copy(args.begin(), args.end(), std::ostream_iterator<std::string>(cout, "\n"));
		}
		WHEN("ChangeShape")
		{
			shape.ChangeShape(make_unique<LineStrategy>(Point(10, 80), Point(15, 90)));
			REQUIRE(shape.ToString() == "line 1 #000000 10 80 15 90"s);
		}

	}
}

TEST_CASE("Check Picture methods")
{
	Picture picture;
	picture.AddShape("1", "#000000", make_unique<CircleStrategy>(Point(50, 50), 50));
	picture.AddShape("2", "#123456", make_unique<TriangleStrategy>(Point(10, 10), Point(20, 20), Point(30, 30)));
	WHEN("AddShape")
	{
		REQUIRE(picture.GetShapeById("1")->ToString() == "circle 1 #000000 50 50 50"s);
	}
	WHEN("Move")
	{
		picture.Move(Point(10, 10));
		REQUIRE(picture.GetShapeById("1")->ToString() == "circle 1 #000000 60 60 50"s);
		REQUIRE(picture.GetShapeById("2")->ToString() == "triangle 2 #123456 20 20 30 30 40 40"s);
	}
	WHEN("ShapedList")
	{
		vector<string> s = picture.ShapesList();
		REQUIRE(s[0] == "1 circle 1 #000000 50 50 50"s);
		REQUIRE(s[1] == "2 triangle 2 #123456 10 10 20 20 30 30"s);
	}
	WHEN("Draw")
	{
		
	}
	WHEN("DeleteShape")
	{
		picture.DeleteShape("2");
		vector<string> s = picture.ShapesList();
		REQUIRE(s[0] == "1 circle 1 #000000 50 50 50"s);
		REQUIRE(s.size() == 1);
	}
}