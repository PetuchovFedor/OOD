#pragma once
#include "../main/SWeatherInfo.h"
#include "../main/Observer.h"
#include <iostream>

class DestructObserver : public IObserver<SWeatherInfo>
{
public:
	 DestructObserver(IObservable<SWeatherInfo>& observer, std::ostream& out)
		 : m_observer(&observer)
		 , m_output(out)
	 {}
	 
private:
	void Update(SWeatherInfo const& data) override
	{
		m_observer->RemoveObserver(*this);
		m_output << "Observer was deleted" << std::endl;
	}
	IObservable<SWeatherInfo>* m_observer;
	std::ostream& m_output;
};