#include "EngineTime.h"

void dae::EngineTime::Update(const float deltaTime)
{
	m_DeltaTime = deltaTime;
	m_AccumulatedTime += deltaTime;
}

float dae::EngineTime::GetDeltaTime() const
{
	return m_DeltaTime;
}