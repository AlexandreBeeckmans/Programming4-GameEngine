#include "Time.h"

void dae::Time::Update(const float deltaTime)
{
	m_DeltaTime = deltaTime;
	m_AccumulatedTime += deltaTime;
}

float dae::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}