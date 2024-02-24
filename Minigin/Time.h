#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void Update(const float deltaTime);

		float GetDeltaTime() const;
		float GetFixedStep() const { return m_FixedTimeStep; };
		int GetMsPerFrame() const { return m_MinMsPerFrame; };
	private:
		friend class Singleton<Time>;
		Time() = default;


		float m_DeltaTime{};
		float m_AccumulatedTime{};

		const float m_FixedTimeStep{ 0.25f };
		const int m_MinMsPerFrame{ 17 };

	};
}


