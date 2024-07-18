#pragma once
#include "SWeatherInfo.h"
#include "Observer.h"
#include "CStatisticData.h"

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* ����� Update ������ ���������, ����� ���������� ����������� ��� ������ ��������
	������ CObservable �� ����� �������� ��� �����, �.�. � ���������� IObserver ��
	�������� ���������
	*/
	void Update(SWeatherInfo const& data) override
	{
		m_temperature.Update(data.temperature);
		m_humidity.Update(data.humidity);
		m_pressure.Update(data.pressure);
		//������� ��� ����� �� ������� ������� 
		std::cout << "Temp: "; 
		m_temperature.PrintStatistic();
		std::cout << "Hum: "; 
		m_humidity.PrintStatistic();
		std::cout << "Temp: ";
		m_pressure.PrintStatistic();
		std::cout << "----------------" << std::endl;
	}
	
	CStatisticData m_temperature;
	CStatisticData m_humidity;
	CStatisticData m_pressure;
};