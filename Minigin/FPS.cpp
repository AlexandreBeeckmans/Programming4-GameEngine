#include "FPS.h"
#include "GameObject.h"

#include "Time.h"

#include <iostream>


dae::FPSComponent::FPSComponent(GameObject* pGameObject) :
	BaseComponent::BaseComponent(pGameObject)
{

}

void dae::FPSComponent::Update()
{
	m_Fps = 1 / Time::GetInstance().GetDeltaTime();
}