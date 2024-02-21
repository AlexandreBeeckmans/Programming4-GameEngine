#include "Scene.h"
#include "TextObject.h"

#include <algorithm>
#include <iostream>
#include "FPS.h"
#include "TextComponent.h"

#include <sstream>
#include <iomanip>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(const float deltaTime)
{
	for(auto& object : m_objects)
	{
		object->Update(deltaTime);

		if (object->HasComponent<FPSComponent>() && object->HasComponent<TextComponent>())
		{
			FPSComponent* fpsComp{ dynamic_cast<FPSComponent*>(object->GetComponent<FPSComponent>()) };
			TextComponent* pTextComp{ dynamic_cast<TextComponent*>(object->GetComponent<TextComponent>()) };

			std::stringstream stream;
			stream << std::fixed << std::setprecision(1) << fpsComp->GetFPS();

			std::string fpsString{ stream.str() + "FPS"};
			pTextComp->SetText(fpsString);
		}
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

