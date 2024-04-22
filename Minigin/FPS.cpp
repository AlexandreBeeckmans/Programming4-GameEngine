#include "FPS.h"
#include "GameObject.h"
#include "EngineTime.h"


dae::FPSComponent::FPSComponent(GameObject* pGameObject) :
	BaseComponent(pGameObject)
{
}

void dae::FPSComponent::Update()
{
	m_Fps = 1 / EngineTime::GetInstance().GetDeltaTime();
}