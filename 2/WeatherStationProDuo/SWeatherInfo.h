#pragma once

struct Wind
{
	double speed = 0;
	unsigned direction;
};

struct SWeatherInfo
{
	std::string sensorId;
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	Wind wind;
};
