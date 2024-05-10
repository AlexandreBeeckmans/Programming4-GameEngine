#pragma once
namespace dae
{
	class SceneCollection
	{
	public:
		virtual ~SceneCollection() {}
		virtual void Update() = 0;
		//virtual void Init() 
	};
}


