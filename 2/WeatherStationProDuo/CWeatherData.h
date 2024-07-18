#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Observer.h"
#include "SWeatherInfo.h"

class CWeatherData : public CObservable<SWeatherInfo>
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
	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		MeasurementsChanged();
	}

	void SetMeasurements(double temp, double humidity, double pressure, Wind wind)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;
		m_wind = wind;
		MeasurementsChanged();
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