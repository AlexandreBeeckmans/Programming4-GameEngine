#include "Subject.h"

#include "GameObject.h"

void dae::Subject::AddObserver(std::unique_ptr<BaseObserver> pObserver)
{
	m_pObservers.push_back(std::move(pObserver));
}

void dae::Subject::RemoveObserver(BaseObserver* pObserver)
{
	std::erase_if(m_pObservers, [=](std::unique_ptr<dae::BaseObserver>& observer)
		{
			return observer.get() == pObserver;
		});
}


void dae::Subject::NotifyObservers(const Event& event, GameObject* pObject)
{
	for (auto& observer : m_pObservers)
		observer->Notify(event, pObject);
}
