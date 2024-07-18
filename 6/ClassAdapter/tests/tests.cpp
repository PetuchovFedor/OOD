#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/ModernGraphicsLibAdapter.h"
#include "../main/modern_graphics_lib.h"
#include "../main/shape_drawing_lib.h"
#include <sstream>
using namespace modern_graphics_lib;
using namespace shape_drawing_lib;
using namespace std;

TEST_CASE("Check Methods")
{
	stringstream stream;
	ModernGraphicsLibAdapter adapter(stream);
	THEN("Call BeginDraw with constructor")
	{
		REQUIRE(stream.str() == "<draw>\n");
	}
	WHEN("MoveTo and LineTo")
	{
		adapter.MoveTo(3, 5);
		adapter.LineTo(10, 10);
		string out = "<draw>\n  <line fromX=\"3\" fromY=\"5\" toX=\"10\" toY=\"10\"/>\n";
		REQUIRE(stream.str() == out);
	}
}

TEST_CASE("Drawing shapes")
{
	stringstream stream;
	ModernGraphicsLibAdapter adapter(stream);
	WHEN("Triangle")
	{
		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		triangle.Draw(adapter);
		string out = R"(<draw>
  <line fromX="10" fromY="15" toX="100" toY="200"/>
  <line fromX="100" fromY="200" toX="150" toY="250"/>
  <line fromX="150" fromY="250" toX="10" toY="15"/>
)";
		REQUIRE(stream.str() == out);
	}
	WHEN("Rectangle")
	{
		CRectangle rectangle({ 30, 40 }, 18, 24);
		rectangle.Draw(adapter);
		string out = R"(<draw>
  <line fromX="30" fromY="40" toX="48" toY="40"/>
  <line fromX="48" fromY="40" toX="48" toY="64"/>
  <line fromX="48" fromY="64" toX="30" toY="64"/>
  <line fromX="30" fromY="64" toX="30" toY="40"/>
)";
		REQUIRE(stream.str() == out);
	}
}