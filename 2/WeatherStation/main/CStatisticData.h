#pragma once
#include <climits>

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
	// Переделать класс
	void PrintStatistic() const
	{
		std::cout << "min: " << m_min << ", max: " << m_max
			<< ", average: " << m_acc / m_countAcc << std::endl;
	}

private:
	double m_min = std::numeric_limits<double>::infinity();
	double m_max= -std::numeric_limits<double>::infinity();
	double m_acc = 0;
	unsigned m_countAcc = 0;
};
