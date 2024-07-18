#pragma once

#include <set>
#include <functional>
#include <map>
#include <algorithm>

/*
Шаблонный интерфейс IObserver. Его должен реализовывать класс,
желающий получать уведомления от соответствующего IObservable
Параметром шаблона является тип аргумента,
передаваемого Наблюдателю в метод Update
*/
template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data) = 0;
	virtual ~IObserver() = default;
};

/*
Шаблонный интерфейс IObservable. Позволяет подписаться и отписаться на оповещения, а также
инициировать рассылку уведомлений зарегистрированным наблюдателям.
*/
template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

// Реализация интерфейса IObservable
template <class T>
class CObservable : public IObservable<T>
{
public:
	typedef IObserver<T> ObserverType;

	void RegisterObserver(ObserverType& observer, int priority) override
	{
		auto iters = m_observers.equal_range(priority);
		for (auto it = iters.first; it != iters.second; ++it)
		{
			if (it->second == &observer)
			{
				return;
			}
		}
		m_observers.insert({ priority, &observer});
		/*if (m_observers.find(&observer) == m_observers.end())
			m_observers.insert({&observer, priority});*/
	}

	void NotifyObservers() override
	{
		T data = GetChangedData();
		auto observers = m_observers;
		for (auto& pair : observers)
		{
			pair.second->Update(data);
		}
		//std::vector<std::pair<ObserverType*, int>> pairsArr;
		//// сделать так чтобы не было постоянной сортировки
		//std::copy(m_observers.begin(), m_observers.end(), std::back_inserter(pairsArr));
		//std::sort(pairsArr.begin(), pairsArr.end(), [](const auto& p1, const auto& p2)
		//	{
		//		return p1.second > p2.second;
		//	});
		//for (auto& observer : pairsArr)
		//{
		//	observer.first->Update(data);
		//}
	}

	void RemoveObserver(ObserverType& observer) override
	{
		for (auto it = m_observers.begin(); it != m_observers.end(); ++it)
		{
			if (it->second == &observer)
			{
				m_observers.erase(it);
				break;
			}
		}
	}

protected:
	// Классы-наследники должны перегрузить данный метод, 
	// в котором возвращать информацию об изменениях в объекте
	virtual T GetChangedData() const = 0;

private:
	//std::map<ObserverType*, int> m_observers;
	std::multimap<int, ObserverType*, std::greater<>> m_observers;
};