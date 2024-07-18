#pragma once
#include "AbstractCommand.h"

template <class T>
class SwapTwoValuesCommand : public AbstractCommand
{
public:
	//осторожнее с классом 
	SwapTwoValuesCommand(T& targetValue, T newValue)
		: m_targetValue(targetValue)
		, m_newValue(newValue)
	{}

	void DoExecute() override
	{
		std::swap(m_targetValue, m_newValue);
	}

	void DoUnExecute() override
	{
		std::swap(m_targetValue, m_newValue);
	}

private:
	T& m_targetValue;
	T m_newValue;
};