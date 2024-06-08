#pragma once
namespace dae
{
	class SceneCollection
	{
	public:
		virtual ~SceneCollection() = default;
		virtual void Init() = 0;
		virtual void Update() = 0;
	};
}


