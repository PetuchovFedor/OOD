#pragma once

struct Wind
{
	double speed = 0;
	unsigned direction;
};

enum class WeatherEvent
{
	TEMPERATURE,
	HUMIDITY,
	PRESSURE,
	WIND
};

struct SWeatherInfo
{
	std::string sensorId;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	Wind wind;
};
