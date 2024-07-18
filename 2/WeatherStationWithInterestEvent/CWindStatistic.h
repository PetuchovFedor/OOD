#pragma once
#include <valarray>
#include <cmath>
#include "CStatisticData.h"
#include "SweatherInfo.h"

const double PI = std::atan(1.0) * 4;

class CWindStatistic
{
public:
	CWindStatistic()
		: m_speed{}
	{
		m_sinSum = 0.0;
		m_cosSum = 0.0;
		m_countAcc = 0;
	}

	void Update(Wind wind)
	{
		m_speed.Update(wind.speed);
		//double t = cos(wind.direction * (PI / 180));
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
		result.first = floor(fmod(((atan2(sinSum, cosSum) * 180 / PI) + 360), 360) * 100) / 100;
		result.second = floor(sqrt(cosSum * cosSum + sinSum * sinSum) * 100) / 100;
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
	/*void PrintStatistic(Wind wind)
	{
		auto aver = AverageWind(wind);
		m_output << "Wind: min speed " << m_speed.GetMin()
			<< " max speed " << m_speed.GetMax() << " average speed "
			<< aver.second << " average direction: " << aver.first << std::endl;
	}*/

private:
	double m_sinSum;
	double m_cosSum;
	CStatisticData m_speed;
	unsigned m_countAcc;
};