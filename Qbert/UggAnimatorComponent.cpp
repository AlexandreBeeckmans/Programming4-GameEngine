#include "UggAnimatorComponent.h"

#include "GameObject.h"
#include "MapComponent.h"
#include "UggDirectionComponent.h"

qbert::UggAnimatorComponent::UggAnimatorComponent(dae::GameObject* owner, MapComponent* pMap) :
BaseComponent(owner),
m_pMap(pMap)
{
}

void qbert::UggAnimatorComponent::Init()
{
	m_pImageComponent = GetOwner()->GetComponent<dae::ImageComponent>();

	/*const int decalX{ -m_pMap->GetTileByIndex(0)->GetWidth() };*/
	const int decalX{0 };

	const int decalY{ m_pMap->GetTileByIndex(0)->GetHeight() / 2 };


	m_pImageComponent->SetRelativePosition(static_cast<float>(decalX), static_cast<float>(decalY));

	m_pDirectionComponent = GetOwner()->GetComponent<UggDirectionComponent>();
	if(!m_pDirectionComponent->IsLeft())
	{
		m_pImageComponent->SetColumn(3);
		m_pImageComponent->SetRow(1);
	}
}
