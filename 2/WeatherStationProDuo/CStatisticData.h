#pragma once
#include <climits>
#include <iostream>

class CStatisticData
{
public:
	CStatisticData()
	{
		m_min = std::numeric_limits<double>::infinity();
		m_max = -std::numeric_limits<double>::infinity();
		m_acc = 0;
		m_countAcc = 0;
	}
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
	/*void PrintStatistic() const
	{
		m_output << "min: " << m_min << ", max: " << m_max
			<< ", average: " << m_acc / m_countAcc << std::endl;
	}*/
private:
	double m_min;
	double m_max;
	double m_acc;
	unsigned m_countAcc;
};
