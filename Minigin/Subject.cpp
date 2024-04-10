#include "Subject.h"

#include "GameObject.h"

void dae::Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	std::erase_if(m_pObservers, [=](dae::Observer* observer)
		{
			return observer == pObserver;
		});
}


void dae::Subject::NotifyObservers()
{
	for (auto& observer : m_pObservers)
		observer->UpdateObserver();
}
