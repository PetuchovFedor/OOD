﻿#pragma once
#include "IBeverage.h"

// Базовая реализация напитка, предоставляющая его описание
class CBeverage : public IBeverage
{
public:
	CBeverage(const std::string& description)
		:m_description(description)
	{}

	std::string GetDescription() const override
	{
		return m_description;
	}
private:
	std::string m_description;
};

// Кофе
class CCoffee : public CBeverage
{
public:
	CCoffee(const std::string& description = "Coffee")
		:CBeverage(description)
	{}

	double GetCost() const override
	{
		return 60;
	}
};

enum class CoffeePortion
{
	Standart,
	Double
};
// Капуччино
class CCappuccino : public CCoffee
{
public:
	CCappuccino(CoffeePortion portion)
		:CCoffee("Cappuccino")
	{
		switch (portion)
		{
		case CoffeePortion::Standart:
			m_portion = "Standart";
			m_cost = 80;
			break;
		case CoffeePortion::Double:
			m_portion == "Double";
			m_cost = 120;
			break;
		default:
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

	std::string GetDescription() const override
	{
		return m_portion + ' ' + CBeverage::GetDescription();
	}
private:
	unsigned m_cost;
	std::string m_portion;
};

// Латте
class CLatte : public CCoffee
{
public:
	CLatte(CoffeePortion portion)
		:CCoffee("Latte")
	{
		switch (portion)
		{
		case CoffeePortion::Standart:
			m_portion = "Standart";
			m_cost = 90;
			break;
		case CoffeePortion::Double:
			m_portion = "Double";
			m_cost = 130;
			break;
		default:
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

	std::string GetDescription() const override
	{
		return m_portion + ' ' + CBeverage::GetDescription();
	}

private:
	std::string m_portion;
	unsigned m_cost;
};


enum class TeaType
{
	Black,
	Green,
	Oolong,
	Chamomile
};
// Чай
class CTea : public CBeverage
{
public:
	CTea(TeaType type)
		:CBeverage("Tea")
	{
		switch (type)
		{
		case TeaType::Black:
			m_type = "Black";
			break;
		case TeaType::Green:
			m_type = "Green";
			break;
		case TeaType::Oolong:
			m_type = "Oolong";
			break;
		case TeaType::Chamomile:
			m_type = "Chamomile";
			break;
		default:
			break;
		}
	}

	double GetCost() const override
	{
		return 30;
	}

	std::string GetDescription() const override
	{
		return m_type + ' ' + CBeverage::GetDescription();
	}
private:
	std::string m_type;
};

enum class MilkShakePortion
{
	Small,
	Medium,
	Large
};
// Молочный коктейль
class CMilkShake : public CBeverage
{
public:
	CMilkShake(MilkShakePortion portion)
		:CBeverage("Milkshake")
	{
		switch (portion)
		{
		case MilkShakePortion::Small:
			m_cost = 50;
			m_portion = "Small";
			break;
		case MilkShakePortion::Medium:
			m_cost = 60;
			m_portion = "Medium";
			break;
		case MilkShakePortion::Large:
			m_cost = 80;
			m_portion = "Large";
			break;
		default:
			break;
		}
	}

	double GetCost() const override
	{
		return m_cost;
	}

	std::string GetDescription() const override
	{
		return m_portion + ' ' + CBeverage::GetDescription();
	}
private:
	unsigned m_cost;
	std::string m_portion;
};