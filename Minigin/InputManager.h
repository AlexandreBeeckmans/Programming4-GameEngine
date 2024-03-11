#pragma once
#include "Singleton.h"
#include <memory>

#include "Command.h"



namespace dae
{
	class GameObject;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void SetMoveUpCommandActor(GameObject* pActor);


	private:
		std::unique_ptr <Move> m_pMoveP1Command;
	};
}
