#pragma once
#include<vector>
#include<memory>

#include "Observer.h"

namespace dae
{
	class BaseObserver;
	class GameObject;

	class Subject
	{
	public:

		//Observers
		void AddObserver(std::unique_ptr<BaseObserver> pObserver);
		void RemoveObserver(BaseObserver* pObserver);
		void NotifyObservers(const Event& event, GameObject* pObject);

	private:
		std::vector<std::unique_ptr<BaseObserver>> m_pObservers{};
	};
}


