#include <cmath>
#include <iostream>
#include "CoW.h"
#include "drawer.h"

constexpr int STAR_COUNT = 20;

int main()
{
	Image img({ 50, 50 }, '.');
	for (size_t i = 45; i < 50; i++)
	{
		DrawLine(img, { 0, (int)i }, { 50, (int)i }, '#');
	}
	for (size_t i = 20; i < 46; i++)
	{
		DrawLine(img, { 10, (int)i }, { 40, (int)i }, '=');
	}
	DrawLine(img, { 10, 20 }, { 40, 15 }, '=');
	DrawLine(img, { 40, 15 }, { 40, 20 }, '=');
	DrawCircle(img, { 25, 30 }, 10, '0');
	DrawLine(img, { 21, 30 }, { 29, 30 }, '0');
	DrawLine(img, { 25, 26 }, { 25, 34 }, '0');
	FillCircle(img, { 44, 5 }, 5, '$');
	Print(img, std::cout);
}