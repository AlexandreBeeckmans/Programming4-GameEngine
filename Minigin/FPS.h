#pragma once

namespace dae
{
	class FPSComponent
	{
	private:
		float m_Fps;

	public:
		void Update(const float deltaTime);
		float GetFPS() { return m_Fps; };
	};
}

