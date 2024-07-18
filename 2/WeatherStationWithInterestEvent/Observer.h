#pragma once
#include <functional>
#include <map>
#include <algorithm>
#include <vector>

template <typename T, typename Event>
class IObservable;

template <typename T, typename Event>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T, Event>& observer, Event event) = 0;
	virtual ~IObserver() = default;
};

template <typename T, typename Event>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T, Event>& observer, Event event, int priority) = 0;
	virtual void NotifyObservers(Event event) = 0;
	virtual void RemoveObserver(IObserver<T, Event>& observer, Event event) = 0;
};

//EventType
template <class T, class EventType>
class CObservable : public IObservable<T, EventType>
{
public:
	typedef IObserver<T, EventType> ObserverType;

	void RegisterObserver(ObserverType& observer, EventType eventType, int priority) override
	{
		auto iters = m_observers.equal_range(eventType);
		for (auto it = iters.first; it != iters.second; ++it)
		{
			if (it->second.first = &observer)
			{
				return;
			}
		}
		m_observers.insert({ eventType, {&observer, priority} });
		m_priorityObservers.insert({priority, {&observer, eventType}});
		//if (m_observers.find({ &observer, eventType }) == m_observers.end())
		//{
		//	m_priorityObservers.insert({ priority, {&observer , eventType} });
		//	m_observers.insert({priority, {&observer, priority}});
		//	//m_priorityObservers.insert({ priority, &observer });
		//	//m_observersWithEventTypes.insert({ &observer, eventType });
		//}
		/*if (m_observers.find({ &observer, eventType }) == m_observers.end())
		{
			m_observers.insert({ {&observer, eventType}, priority });
			m_isChangedObservers = true;
		}*/
	}

	void NotifyObservers(EventType eventType) override
	{
		if (m_observers.empty())
			return;
		T data = GetChangedData();
		auto iters1 = m_observers.equal_range(eventType);
		std::vector<int> priorities;
		for (auto it = iters1.first; it != iters1.second; ++it)
		{
			priorities.push_back(it->second.second);
		}
		sort(priorities.begin(), priorities.end(), [](int pr1, int pr2)
			{
				return pr1 > pr2;
			});
		for (size_t i = 0; i < priorities.size(); i++)
		{
			//”простить код
			auto iters = m_priorityObservers.equal_range(priorities[i]);
			for (auto it = iters.first; it != iters.second; ++it)
			{
				if (it->second.second == eventType)
				{
					it->second.first->Update(data, *this, eventType);
				}
			}
			
		}
		//if (m_isChangedObservers)
		//{
		//	m_vectorObservers = CreateVectorObservers();
		//	m_isChangedObservers = false;
		//}
		////—ломаетс€ если наблюдатель вызовет notify
		////Ёффективнее чем обход всего
		//for (auto& observer : m_vectorObservers)
		//{
		//	if (observer.first.second == eventType)
		//	{
		//		observer.first.first->Update(data, *this, observer.first.second);
		//	}
		//}
	}

	void RemoveObserver(ObserverType& observer, EventType eventType) override
	{
		auto pair = std::make_pair(&observer, eventType);
		//auto pr = m_observers.at(eventType);
		auto iters1 = m_observers.equal_range(eventType);
		int pr = 0;
		for (auto it = iters1.first; it != iters1.second; ++it)
		{
			if (it->second.first == &observer)
			{
				pr = it->second.second;
				m_observers.erase(it);
				break;
			}
		}
		auto iters2 = m_priorityObservers.equal_range(pr);
		for (auto it = iters2.first; it != iters2.second; ++it)
		{
			if (it->second == pair)
			{
				m_priorityObservers.erase(it);
				break;
			}
		}
		//m_observers.erase(pair);
		/*m_observers.erase({&observer, eventType });
		m_isChangedObservers = true;*/
	}

protected:
	virtual T GetChangedData() const = 0;

private:
	std::vector<std::pair<std::pair<ObserverType*, EventType>, int>> CreateVectorObservers()
	{
		std::vector<std::pair<std::pair<ObserverType*, EventType>, int>> pairsArr;
		std::copy(m_observers.begin(), m_observers.end(), std::back_inserter(pairsArr));
		std::sort(pairsArr.begin(), pairsArr.end(), [](const auto& p1, const auto& p2)
			{
				return p1.second > p2.second;
			});
		return pairsArr;
	}
	bool m_isChangedObservers = false;
	//std::multimap<int, ObserverType*> m_priorityObservers;
	//std::multimap<ObserverType*, EventType> m_observersWithEventTypes;
	/*std::multimap<int, std::pair<ObserverType*, EventType>> m_priorityObservers;
	std::map<std::pair<ObserverType*, EventType>, int> m_observers;*/
	std::multimap<int, std::pair<ObserverType*, EventType>, std::greater<>> m_priorityObservers;
	std::multimap<EventType, std::pair<ObserverType*, int> > m_observers;

	//std::vector<std::pair<std::pair<ObserverType*, EventType>, int>> m_vectorObservers;

};