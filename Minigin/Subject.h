#pragma once
#include<vector>
#include<memory>

#include "Observer.h"

namespace dae
{
	class Observer;
	class GameObject;

	class Subject
	{
	public:

		//Observers
		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void NotifyObservers();

	private:
		std::vector<Observer*> m_pObservers{};
	};
}


