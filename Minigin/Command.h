#pragma once
namespace dae
{
	class GameObject;
	class TextComponent;

	class Command
	{
	public:
		virtual ~Command() = default;

		virtual void Execute() = 0;
	};

	class MuteCommand final : public Command
	{
	public:
		MuteCommand() = default;
		virtual void Execute() override;
	};


	class GameObjectCommand : public Command
	{
	private:
		GameObject* m_pActor;
	protected:
		GameObject* GetGameActor() const { return m_pActor; }
	public:

		GameObjectCommand(GameObject* pActor);
		virtual ~GameObjectCommand() = default;
	};
}
