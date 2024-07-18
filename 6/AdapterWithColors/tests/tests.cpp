#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/ModernGraphicsLibAdapter.h"
#include "../main/modern_graphics_lib_pro.h"
#include "../main/shape_drawing_lib.h"
#include <sstream>
using namespace modern_graphics_lib_pro;
using namespace shape_drawing_lib;
using namespace std;

TEST_CASE("Check Methods")
{
	stringstream stream;
	CModernGraphicsRenderer renderer(stream);
	ModernGraphicsLibAdapter adapter(renderer);
	THEN("Call BeginDraw with constructor")
	{
		REQUIRE(stream.str() == "<draw>\n");
	}
	WHEN("MoveTo and LineTo without color")
	{
		adapter.MoveTo(3, 5);
		adapter.LineTo(10, 10);
		string out = R"(<draw>
  <line fromX="3" fromY="5" toX="10" toY="10">
	<color r="0" g="0" b="0" a="0" />
  </line>
)";
		REQUIRE(stream.str() == out);
	}
	WHEN("MoveTo and LineTo with color")
	{
		adapter.SetColor(10322362);
		adapter.MoveTo(3, 5);
		adapter.LineTo(10, 10);
		string out = R"(<draw>
  <line fromX="3" fromY="5" toX="10" toY="10">
	<color r="0.62" g="0.51" b="0.73" a="1" />
  </line>
)";
		REQUIRE(stream.str() == out);
	}
}

TEST_CASE("Drawing shapes")
{
	stringstream stream;
	CModernGraphicsRenderer renderer(stream);
	ModernGraphicsLibAdapter adapter(renderer);
	WHEN("DrawTriangle")
	{
		//Цвета прокидывать в hex
		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x9d81ba);
		triangle.Draw(adapter);
		string out = R"(<draw>
  <line fromX="10" fromY="15" toX="100" toY="200">
	<color r="0.62" g="0.51" b="0.73" a="1" />
  </line>
  <line fromX="100" fromY="200" toX="150" toY="250">
	<color r="0.62" g="0.51" b="0.73" a="1" />
  </line>
  <line fromX="150" fromY="250" toX="10" toY="15">
	<color r="0.62" g="0.51" b="0.73" a="1" />
  </line>
)";
		REQUIRE(stream.str() == out);
	}
	WHEN("DrawRectangle")
	{
		CRectangle rectangle({ 30, 40 }, 18, 24, 0x2271b3);
		rectangle.Draw(adapter);
		string out = R"(<draw>
  <line fromX="30" fromY="40" toX="48" toY="40">
	<color r="0.13" g="0.44" b="0.7" a="1" />
  </line>
  <line fromX="48" fromY="40" toX="48" toY="64">
	<color r="0.13" g="0.44" b="0.7" a="1" />
  </line>
  <line fromX="48" fromY="64" toX="30" toY="64">
	<color r="0.13" g="0.44" b="0.7" a="1" />
  </line>
  <line fromX="30" fromY="64" toX="30" toY="40">
	<color r="0.13" g="0.44" b="0.7" a="1" />
  </line>
)";
		REQUIRE(stream.str() == out);
	}
}