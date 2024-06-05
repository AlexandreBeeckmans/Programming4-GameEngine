#pragma once
namespace dae
{
	class SceneCollection
	{
	public:
		virtual ~SceneCollection() = default;
		virtual void Update() = 0;
	};
}


