#pragma once
struct IFlyBehavior
{
	virtual ~IFlyBehavior() {};
	virtual void Fly() = 0;
	virtual void ShowCountOfFlights() = 0;
};
