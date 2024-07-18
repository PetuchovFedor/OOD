#pragma once
#include "../main/Observer.h"
#include <string>
#include <iostream>

class ObservableTest : public CObservable<std::string>
{
public:
	void Notify()
	{
		NotifyObservers();
	}
protected:
	std::string GetChangedData() const override
	{
		return "changed";
	}
};

class ObserverTest : public IObserver<std::string>
{
public:
	ObserverTest(std::ostream& out, int priority)
		: m_output(out)
		, m_priority(priority)
	{}
	void Update(std::string const& val) override
	{
		m_output << m_priority;
	}

	int GetPriority() const
	{
		return m_priority;
	}
private:
	std::ostream& m_output;
	int m_priority;
};