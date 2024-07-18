#pragma once
#include <climits>
#include <iostream>

class CStatisticData
{
public:

	void Update(double data)
	{
		if (m_min > data)
		{
			m_min = data;
		}
		if (m_max < data)
		{
			m_max = data;
		}
		m_acc += data;
		++m_countAcc;
	}

	double GetMin() const
	{
		return m_min;
	}

	double GetMax() const
	{
		return m_max;
	}

	double GetAverage() const
	{
		return m_acc / m_countAcc;
	}
	//void PrintStatistic() const
	//{
	//	std::cout << "min: " << m_min << ", max: " << m_max
	//		<< ", average: " << m_acc / m_countAcc << std::endl;
	//}
private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max = -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};
