#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <vector>
#include "Observer.h"
#include "SWeatherInfo.h"

class CWeatherData : public CObservable<SWeatherInfo, WeatherEvent>
{
public:
	CWeatherData(const std::string& id)
		: m_id(id)
	{}
	std::string GetId() const
	{
		return m_id;
	}
	// Температура в градусах Цельсия
	double GetTemperature() const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity() const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure() const
	{
		return m_pressure;
	}

	Wind GetWind() const
	{
		return m_wind;
	}
	void MeasurementsChanged(std::vector<WeatherEvent> events)
	{
		for (auto& ev : events)
			NotifyObservers(ev);
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		std::vector<WeatherEvent> events;
		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			events.push_back(WeatherEvent::HUMIDITY);
		}
		if (m_temperature != temp)
		{
			m_temperature = temp;
			events.push_back(WeatherEvent::TEMPERATURE);
		}
		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			events.push_back(WeatherEvent::PRESSURE);
		}
		MeasurementsChanged(events);
	}

	void SetMeasurements(double temp, double humidity, double pressure, Wind wind)
	{
		std::vector<WeatherEvent> events;
		if (m_humidity != humidity)
		{
			m_humidity = humidity;
			events.push_back(WeatherEvent::HUMIDITY);
		}
		if (m_temperature != temp)
		{
			m_temperature = temp;
			events.push_back(WeatherEvent::TEMPERATURE);
		}
		if (m_pressure != pressure)
		{
			m_pressure = pressure;
			events.push_back(WeatherEvent::PRESSURE);
		}
		if (m_wind.direction != wind.direction || m_wind.speed != wind.speed)
		{
			m_wind = wind;
			events.push_back(WeatherEvent::WIND);
		}
		MeasurementsChanged(events);
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.sensorId = GetId();
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		info.wind = GetWind();
		return info;
	}
private:
	std::string m_id;
	double m_temperature = 0.0;
	double m_humidity = 0.0;
	double m_pressure = 760.0;
	Wind m_wind;
};