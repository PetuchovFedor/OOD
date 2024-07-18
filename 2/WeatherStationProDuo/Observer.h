#pragma once
#include <functional>
#include <map>
#include <algorithm>

template <typename T>
class IObservable;

template <typename T>
class IObserver
{
public:
	virtual void Update(T const& data, IObservable<T>& observer) = 0;
	virtual ~IObserver() = default;
};

template <typename T>
class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver<T>& observer, int priority) = 0;
	virtual void NotifyObservers() = 0;
	virtual void RemoveObserver(IObserver<T>& observer) = 0;
};

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
		m_observers.insert({ priority, &observer });
			
	}

	void NotifyObservers() override
	{
		if (m_observers.empty())
			return;
		T data = GetChangedData();
		auto observers = m_observers;
		for (auto& pair : observers)
		{
			pair.second->Update(data, *this);
		}
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
	virtual T GetChangedData() const = 0;

private:
	/*std::vector<std::pair<ObserverType*, int>> CreateVectorObservers()
	{
		std::vector<std::pair<ObserverType*, int>> pairsArr;
		std::copy(m_observers.begin(), m_observers.end(), std::back_inserter(pairsArr));
		std::sort(pairsArr.begin(), pairsArr.end(), [](const auto& p1, const auto& p2)
			{
				return p1.second > p2.second;
			});
		return pairsArr;
	}*/
	//bool m_isChangeObservers = false;
	//std::map<ObserverType*, int> m_observers;
	std::multimap<int, ObserverType*, std::greater<>> m_observers;
	//std::vector<std::pair<ObserverType*, int>> m_vectorObservers;
};