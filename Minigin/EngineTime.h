#pragma once
#include "Singleton.h"

namespace dae
{
	class EngineTime final : public Singleton<EngineTime>
	{
	public:
		void Update(const float deltaTime);

		float GetDeltaTime() const;
		float GetFixedStep() const { return m_FixedTimeStep; };
		int GetMsPerFrame() const { return m_MinMsPerFrame; };
	private:
		friend class Singleton<EngineTime>;
		EngineTime() = default;


		float m_DeltaTime{};
		float m_AccumulatedTime{};

		const float m_FixedTimeStep{ 0.25f };
		const int m_MinMsPerFrame{ 1000/60 };

	};
}


