#include "FPS.h"
#include "GameObject.h"

#include <iostream>


dae::FPSComponent::FPSComponent(GameObject* pGameObject) :
	BaseComponent::BaseComponent(pGameObject)
{

}

void dae::FPSComponent::Update(const float deltaTime)
{
	m_Fps = 1 / deltaTime;
	//std::cout << m_Fps << std::endl;
}