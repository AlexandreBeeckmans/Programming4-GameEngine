#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "EngineTime.h"

#include <chrono>

#include "LoggingSoundSystem.h"
#include "SDLSoundSystem.h"
#include "ServiceLocator.h"


SDL_Window* g_window{};
const int dae::Minigin::m_WindowWidth = 600;
const int dae::Minigin::m_WindowHeight = 600;


void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_WindowWidth,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);
	ResourceManager::GetInstance().Init(dataPath);

#if _DEBUG
	ServiceLocator::GetInstance().RegisterSoundSystem(std::make_unique<dae::LoggingSoundSystem>(std::make_unique<SDLSoundSystem>()));
#else
	ServiceLocator::GetInstance().RegisterSoundSystem(std::make_unique<dae::SDLSoundSystem>());
#endif

	ServiceLocator::GetInstance().GetSoundSystem().Init();
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(const std::function<void()>& load)
{
	load();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& time{ EngineTime::GetInstance() };
	sceneManager.Init();

	// todo: this update loop could use some work.
	bool doContinue = true;
	auto lastTime{ std::chrono::high_resolution_clock::now() };
	float lag{ 0.0f };

	while (doContinue)
	{
		const auto currentTime{ std::chrono::high_resolution_clock::now() };
		const float deltaTime{ std::chrono::duration<float>(currentTime - lastTime).count() };
		lastTime = currentTime;
		lag += deltaTime;
		time.Update(deltaTime);

		ServiceLocator::GetInstance().Update();

		doContinue = input.ProcessInput();

		while (lag >= time.GetFixedStep())
		{
			sceneManager.FixedUpdate();
			lag -= time.GetFixedStep();
		}

		sceneManager.Update();
		sceneManager.LateUpdate();

		sceneManager.RemoveAllDeadComponents();
		renderer.Render();

		const auto sleepTime{ currentTime + std::chrono::milliseconds(time.GetMsPerFrame()) - std::chrono::high_resolution_clock::now() };
		std::this_thread::sleep_for(sleepTime);
	}
}
