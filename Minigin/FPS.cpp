#include "FPS.h"
#include <iostream>

void dae::FPSComponent::Update(const float deltaTime)
{
	m_Fps = 1 / deltaTime;
	//std::cout << m_Fps << std::endl;
}