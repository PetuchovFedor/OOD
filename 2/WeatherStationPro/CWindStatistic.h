#pragma once
#include <valarray>
#include <cmath>
#include "CStatisticData.h"
#include "SweatherInfo.h"

const double PI = std::atan(1.0) * 4;

class CWindStatistic
{
public:

	void Update(Wind wind)
	{
		m_speed.Update(wind.speed);
		double t = cos(wind.direction * (PI / 180));
		double sinus = sin(wind.direction * PI / 180);
		double cosinus = cos(wind.direction * PI / 180);
		if (wind.direction == 0 || wind.direction == 180)
		{
			sinus = 0.0;
		}
		else if (wind.direction == 90 || wind.direction == 270)
		{
			cosinus = 0.0;
		}
		m_sinSum += wind.speed * sinus;
		m_cosSum += wind.speed * cosinus;
		m_countAcc++;
	}

	std::pair<double, double> AverageWind(Wind wind)
	{
		double sinSum = m_sinSum / m_countAcc;
		double cosSum = m_cosSum / m_countAcc;
		std::pair<double, double> result;
		result.first = fmod(((atan2(sinSum, cosSum) * 180 / PI) + 360), 360);
		result.second = sqrt(cosSum * cosSum + sinSum * sinSum);
		return result;
	}

	double GetMinSpeed() const
	{
		return m_speed.GetMin();
	}

	double GetMaxSpeed() const
	{
		return m_speed.GetMax();
	}

private:
	double m_sinSum = 0.0;
	double m_cosSum = 0.0;
	CStatisticData m_speed;
	unsigned m_countAcc = 0;
};