#pragma once

#include <functional>
#include <iostream>

using Strategy = std::function<void()>;

class Duck
{
public:
	Duck(const Strategy& flyBehavior, const Strategy& quackBehavior,
		const Strategy& danceBehavior)
		: m_quackBehavior(quackBehavior)
		, m_danceBehavior(danceBehavior)
	{
		SetFlyBehavior(flyBehavior);
	}

	void Quack() const
	{
		if (m_quackBehavior)
		{
			m_quackBehavior();
		}
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		if (m_flyBehavior)
		{
			m_flyBehavior();
			m_countOfFlights++;
		}
	}

	void Dance()
	{
		if (m_danceBehavior)
		{
			m_danceBehavior();
		}
	}

	void SetFlyBehavior(Strategy flyBehavior)
	{
		m_flyBehavior = flyBehavior;
	}

	void ShowCountOfFlights()
	{
		if (m_flyBehavior)
		{
			std::cout << "I'm have " << m_countOfFlights << " flights" << std::endl;
		}
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	Strategy m_flyBehavior;
	Strategy m_quackBehavior;
	Strategy m_danceBehavior;
	int m_countOfFlights = 0;
};