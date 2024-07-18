#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include "CStatisticData.h"
#include "CWindStatistic.h"

struct StatsDataGroup
{
	StatsDataGroup()
		: temperature{}
		, humidity{}
		, pressure{}
		, wind{}
	{}
	CStatisticData temperature;
	CStatisticData humidity;
	CStatisticData pressure;
	CWindStatistic wind;
};

class CStatsDisplay : public IObserver<SWeatherInfo, WeatherEvent>
{
public:
	CStatsDisplay(IObservable<SWeatherInfo, WeatherEvent>& in, IObservable<SWeatherInfo, WeatherEvent>& out,
		std::ostream& output)
		: m_output(output)
		, m_inObservable(&in)
		, m_outObservable(&out)
	{
		m_indicators.insert({ &in, StatsDataGroup() });
		m_indicators.insert({ &out, StatsDataGroup() });
	}
private:
	void Update(SWeatherInfo const& data, IObservable<SWeatherInfo, WeatherEvent>& observable,
		WeatherEvent event) override
	{
		//id лишний
		m_output << data.sensorId << ':' << std::endl;
		if (event == WeatherEvent::TEMPERATURE)
		{
			m_indicators.at(&observable).temperature.Update(data.temperature);
			m_output << "Temp: ";
			PrintStatistic(m_indicators.at(&observable).temperature);
		}
		else if (event == WeatherEvent::HUMIDITY)
		{
			m_indicators.at(&observable).humidity.Update(data.humidity);
			m_output << "Hum: ";
			PrintStatistic(m_indicators.at(&observable).humidity);
		}
		else if (event == WeatherEvent::PRESSURE)
		{
			m_indicators.at(&observable).pressure.Update(data.pressure);
			m_output << "Pres: ";
			PrintStatistic(m_indicators.at(&observable).pressure);
		}
		else if (event == WeatherEvent::WIND)
		{
			m_indicators.at(&observable).wind.Update(data.wind);
			m_output << "Wind: ";
			PrintWindStatistic(observable, data.wind);
		}
		m_output << "----------------" << std::endl;
	}

	void PrintStatistic(const CStatisticData& data)
	{
		m_output << "min: " << data.GetMin() << ", max: " << data.GetMax()
			<< ", average: " << data.GetAverage() << std::endl;
	}

	void PrintWindStatistic(IObservable<SWeatherInfo, WeatherEvent>& observable, Wind wind)
	{
		auto windStats = m_indicators.at(&observable).wind;
		auto aver = windStats.AverageWind(wind);
		m_output << "Wind: min speed " << windStats.GetMinSpeed()
			<< " max speed " << windStats.GetMaxSpeed() << " average speed "
			<< aver.second << " average direction: " << aver.first << std::endl;
	}

	std::map<IObservable<SWeatherInfo, WeatherEvent>*, StatsDataGroup> m_indicators;
	IObservable<SWeatherInfo, WeatherEvent>* m_inObservable;
	IObservable<SWeatherInfo, WeatherEvent>* m_outObservable;
	std::ostream& m_output;
};