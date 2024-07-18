#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../main/Tile.h"
#include "../main/Image.h"

TEST_CASE("Check tile methods")
{
	GIVEN("Tile")
	{
		Tile tile('.');
		WHEN("GetPixel")
		{
			REQUIRE(tile.GetPixel({ 3, 4 }) == '.');			
		}
		WHEN("GetPixel(out of range tile`s size")
		{
			REQUIRE(tile.GetPixel({ 8, 10 }) == ' ');
		}
		WHEN("SetTile")
		{
			tile.SetPixel({ 3, 5 }, '&');
			REQUIRE(tile.GetPixel({ 3, 5 }) == '&');
		}
		WHEN("GetInstanceCount")
		{
			REQUIRE(tile.GetInstanceCount() == 1);
			WHEN("Adding another tile")
			{
				Tile tmp;
				REQUIRE(tile.GetInstanceCount() == 2);
			}
		}
	}
}

TEST_CASE("Check image methods")
{
	GIVEN("image")
	{
		Image img({ 50, 30 }, '@');
		WHEN("copy construct and check count tiles")
		{
			Image tmp(img);
			REQUIRE(Tile::GetInstanceCount() == 1);
		}
		WHEN("GetSizes")
		{
			//Size size = { 50, 30 };
			REQUIRE(img.GetSize().width == 50);
			REQUIRE(img.GetSize().height == 30);
		}
		WHEN("SetPixel")
		{
			img.SetPixel({ 20, 21 }, '$');
			REQUIRE(img.GetPixel({ 20, 21 }) == '$');			
			THEN("Count of tiles is 2")
			{
				REQUIRE(Tile::GetInstanceCount() == 2);
			}
			WHEN("Set pixel in the same tile")
			{
				img.SetPixel({ 22, 19 }, '0');
				THEN("Count of tiles is 2")
				{
					REQUIRE(Tile::GetInstanceCount() == 2);
				}
			}
			WHEN("Copy img")
			{
				Image copy(img);
				THEN("Count of tiles is 2")
				{
					REQUIRE(Tile::GetInstanceCount() == 2);
				}
				WHEN("Set pixel at the copy")
				{
					copy.SetPixel({ 2, 5 }, '.');
					REQUIRE(copy.GetPixel({ 2, 5 }) == '.');
					THEN("Count of tiles is 3")
					{
						REQUIRE(Tile::GetInstanceCount() == 3);
					}
					THEN("original img don`t change")
					{
						REQUIRE(img.GetPixel({ 2, 5 }) != '.');
					}
				}
			}
		}
	}
}