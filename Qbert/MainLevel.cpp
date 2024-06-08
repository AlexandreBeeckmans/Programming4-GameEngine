#include "MainLevel.h"

#include"ImageComponent.h"
#include "AnimatorComponent.h"
#include "BubbleManagerComponent.h"
#include "GridMoveComponent.h"
#include "LevelLoader.h"
#include "MapComponent.h"
#include "Minigin.h"
#include "QbertGameState.h"
#include "QbertScenes.h"

qbert::MainLevel::MainLevel(const int levelNb, const int roundNb, const int nbPlayer, const bool isVersus):
m_LevelNb(levelNb),
m_RoundNb(roundNb),
m_NbPlayer(nbPlayer),
m_IsVersus(isVersus)
{
}

void qbert::MainLevel::Load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Main Level");
	LevelInfo levelInfo{ LevelLoader::GetInstance().LoadLevel(m_LevelNb + 1, m_RoundNb + 1) };

	QbertGameState::GetInstance().SetNbPlayer(m_NbPlayer);
	dae::ImageComponent::SetSpriteScale(QbertGameState::GetInstance().GetScale());


#pragma region SET_MAP

	constexpr int nbOfRow{ 7 };
	int nbOfTiles{ nbOfRow };
	std::unique_ptr<dae::GameObject> pMapObject{ std::make_unique<dae::GameObject>() };

	pMapObject->AddComponent<qbert::MapComponent>(nbOfRow);
	float baseTileX{ 0.0f };
	float baseTileY{ 0.0f };

	std::vector<std::unique_ptr<dae::GameObject>> tiles{};


	for (int j{ 0 }; j < nbOfRow; ++j)
	{
		for (int i{ 0 }; i < nbOfTiles; ++i)
		{
			auto tileObject = std::make_unique<dae::GameObject>();
			tileObject->AddComponent<qbert::TileComponent>(m_LevelNb % 2 + 1, m_LevelNb >= 2);
			tileObject->AddComponent<dae::ImageComponent>("qbert/Qbert Cubes.png", true, 0.0f, 0.0f, 3, 6, 0, m_RoundNb);
			tileObject->AddComponent<dae::AnimatorComponent>(false, 0.1f, 1, 3, m_RoundNb, 0);

			tileObject->SetParent(pMapObject.get(), true);
			tileObject->SetLocalPosition(baseTileX + i * tileObject->GetComponent<dae::ImageComponent>()->GetShape().w, baseTileY);

			pMapObject->GetComponent<qbert::MapComponent>()->AddTile(tileObject->GetComponent<qbert::TileComponent>());
			tiles.emplace_back(std::move(tileObject));
		}

		--nbOfTiles;
		baseTileX += tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().w / 2.0f;
		baseTileY -= 3 * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().h / 4.0f;
	}

	const glm::vec2 mapPosition
	{
		static_cast<float>(dae::Minigin::GetWindowWidth()) / 2.0f - static_cast<float>(nbOfRow * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().w) / 2.0f,
		static_cast<float>(dae::Minigin::GetWindowHeight()) / 2.0f + static_cast<float>(nbOfRow * tiles[0]->GetComponent<dae::ImageComponent>()->GetShape().h) / 4.0f
	};
	pMapObject->SetLocalPosition(mapPosition);

#pragma endregion

	std::vector<std::unique_ptr<dae::GameObject>> playerObjects{};
	std::vector<std::unique_ptr<dae::GameObject>> bubbleObjects{};
	for (int i{ 0 }; i < m_NbPlayer; ++i)
	{
		playerObjects.push_back(QbertScenes::GetInstance().CreatePlayer(i + 1, pMapObject->GetComponent<MapComponent>()));
		bubbleObjects.push_back(QbertScenes::GetInstance().CreateBubble(playerObjects[i].get()));
		playerObjects[i]->GetComponent<qbert::BubbleManagerComponent>()->SetBubbleImage(bubbleObjects[i]->GetComponent<dae::ImageComponent>());
	}

	//reposition if multiple players
	if (m_NbPlayer > 1)
	{
		playerObjects[0]->GetComponent<GridMoveComponent>()->SetCurrentIndex(0);
		playerObjects[1]->GetComponent<GridMoveComponent>()->SetCurrentIndex(nbOfRow - 1);
	}


	std::vector<std::unique_ptr<dae::GameObject>> coilyObjects{};
	for (int i{ 0 }; i < levelInfo.nbCoily; ++i)
	{
		coilyObjects.push_back(QbertScenes::GetInstance().CreateCoily(i, &playerObjects, pMapObject->GetComponent<MapComponent>(), m_IsVersus));
	}

	std::vector<std::unique_ptr<dae::GameObject>> slickObjects{};
	for (int i{ 0 }; i < levelInfo.nbSlick; ++i)
	{
		slickObjects.push_back(QbertScenes::GetInstance().CreateSlick(static_cast<bool>(i % 2), &playerObjects, pMapObject->GetComponent<MapComponent>()));
	}

	std::vector<std::unique_ptr<dae::GameObject>> uggObjects{};
	for (int i{ 0 }; i < levelInfo.nbUgg; ++i)
	{
		uggObjects.push_back(QbertScenes::GetInstance().CreateUgg(static_cast<bool>(i % 2), &playerObjects, pMapObject->GetComponent<MapComponent>()));
	}

	QbertScenes::GetInstance().CreateDiscObject(&scene, pMapObject->GetComponent<MapComponent>(), true, m_RoundNb);
	QbertScenes::GetInstance().CreateDiscObject(& scene, pMapObject->GetComponent<MapComponent>(), false, m_RoundNb);


	QbertScenes::GetInstance().CreateGameUI(&scene, playerObjects, m_LevelNb, m_RoundNb);


	for (auto& tile : tiles)
	{
		scene.Add(std::move(tile));
	}
	scene.Add(std::move(pMapObject));

	for (auto& bubble : bubbleObjects)
	{
		scene.Add(std::move(bubble));
	}

	for (auto& player : playerObjects)
	{
		scene.Add(std::move(player));
	}

	for (auto& coily : coilyObjects)
	{
		scene.Add(std::move(coily));
	}

	for (auto& slick : slickObjects)
	{
		scene.Add(std::move(slick));
	}

	for (auto& ugg : uggObjects)
	{
		scene.Add(std::move(ugg));
	}
}
