#pragma once
#include "CWindStatistic.h"
#include "Observer.h"
#include "CWindStatistic.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	void Update(SWeatherInfo const& data) override
	{
		m_temperature.Update(data.temperature);
		m_humidity.Update(data.humidity);
		m_pressure.Update(data.pressure);
		m_wind.Update(data.wind);
		std::cout << "Temp: ";
		PrintStatistic(m_temperature);
		std::cout << "Hum: ";
		PrintStatistic(m_humidity);
		std::cout << "Pres: ";
		PrintStatistic(m_pressure);
		PrintWindStatistic(data.wind);
		std::cout << "----------------" << std::endl;
	}

	void PrintStatistic(CStatisticData data)
	{
		std::cout << "min: " << data.GetMin() << ", max: " << data.GetMax()
			<< ", average: " << data.GetAverage() << std::endl;
	}

	void PrintWindStatistic(Wind wind)
	{
		auto aver = m_wind.AverageWind(wind);
		std::cout << "Wind: min speed " << m_wind.GetMinSpeed()
			<< " max speed " << m_wind.GetMaxSpeed() << " average speed "
			<< aver.second << " average direction: " << aver.first << std::endl;
	}

	CStatisticData m_temperature;
	CStatisticData m_humidity;
	CStatisticData m_pressure;
	CWindStatistic m_wind;
};