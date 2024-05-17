#include "EchoGame.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/BoxColliderSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/RenderColliderDebugSystem.h"
#include "../Systems/RenderSpriteDebugSystem.h"
#include "../Systems/CameraMovementSystem.h"
int EchoGame::windowWidth;
int EchoGame::windowHeight;
int EchoGame::mapWidth;
int EchoGame::mapHeight;

EchoGame::EchoGame() : mIsRunning(false)
{
	mRegistry = std::make_unique<Registry>();
	mAssetStore = std::make_unique<AssetStore>();
	mEventBus = std::make_unique<EventBus>();
	LOG_INFO("Game construction called");
}

EchoGame::~EchoGame()
{
	LOG_INFO("Game destruction called");
}

void EchoGame::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != ECHO2D_SUCCESS) {
		LOG_ERROR("Error initializing SDL");
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);
	windowWidth = 800; //displayMode.w;
	windowHeight = 600; //displayMode.h;
	mWindow = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		windowWidth,
		windowHeight,
		SDL_WINDOW_BORDERLESS | SDL_WINDOW_VULKAN
	);

	if (!mWindow) {
		LOG_ERROR("Error creating SDL window");
		return;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mRenderer) {
		LOG_ERROR("Error creating SDL renderer");
		return;
	}

	mCamera.x = 0;
	mCamera.y = 0;
	mCamera.w = windowWidth;
	mCamera.h = windowHeight;

	//SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_BORDERLESS);
	mIsRunning = true;
}

void EchoGame::Run()
{
	Setup();
	while (mIsRunning) {
		ProcessingInput();
		Update();
		Render();
	}
}

void EchoGame::ProcessingInput()
{
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_KEYDOWN:
			mEventBus->InvokeEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
			break;
		case SDL_KEYUP:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				mIsRunning = false;
			}
			break;
		}
	}
}

glm::vec2 position;
glm::vec2 velocity;

void EchoGame::LoadLevel(int level) {
	mRegistry->AddSystem<MovementSystem>();
	mRegistry->AddSystem<AnimationSystem>();
	mRegistry->AddSystem<BoxColliderSystem>();
	mRegistry->AddSystem<DamageSystem>();
	mRegistry->AddSystem<RenderColliderDebugSystem>();
	mRegistry->AddSystem<RenderSpriteDebugSystem>();
	mRegistry->AddSystem<RenderSystem>();
	mRegistry->AddSystem<KeyboardControlSystem>();
	mRegistry->AddSystem<CameraMovementSystem>();

	mAssetStore->AddTexture(mRenderer, "tank-image", "./assets/images/tank-panther-right.png");
	mAssetStore->AddTexture(mRenderer, "truck-image", "./assets/images/truck-ford-left.png");
	mAssetStore->AddTexture(mRenderer, "chopper-image", "./assets/images/chopper-spritesheet.png");
	mAssetStore->AddTexture(mRenderer, "radar-image", "./assets/images/radar.png");
	mAssetStore->AddTexture(mRenderer, "tile-map", "./assets/tilemaps/jungle.png");

	int tileSize = 32;
	double tileScale = 2.0;
	int mapNumCols = 25;
	int mapNumRows = 20;

	std::fstream mapFile;
	mapFile.open("./assets/tilemaps/jungle.map");
	for (int y = 0; y < mapNumRows; y++) {
		for (int x = 0; x < mapNumCols; x++) {
			char ch;
			mapFile.get(ch);
			int srcRectY = std::atoi(&ch) * tileSize;
			mapFile.get(ch);
			int srcRectX = std::atoi(&ch) * tileSize;
			mapFile.ignore();

			Entity map = mRegistry->CreateEntity();
			map.AddComponent<TranformComponent>(glm::vec2(x * (tileScale * tileSize), y * (tileScale * tileSize)), glm::vec2(tileScale, tileScale), 0.0);
			map.AddComponent<SpriteComponent>("tile-map", tileSize, tileSize, 0, false, srcRectX, srcRectY);
		}
	}
	mapFile.close();
	mapWidth = mapNumCols * tileSize * tileScale;
	mapHeight = mapNumRows * tileSize * tileScale;

	//TODO: Initialize the GameObjects
	Entity chopper = mRegistry->CreateEntity();
	chopper.AddComponent<TranformComponent>(glm::vec2(10.0, 10.0), glm::vec2(2, 2), 0.0);
	chopper.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 1);
	chopper.AddComponent<AnimationComponent>(2, 20, true);
	chopper.AddComponent<KeyboardControlComponent>(glm::vec2(120, 120));
	chopper.AddComponent<CameraFollowComponent>();

	Entity radar = mRegistry->CreateEntity();
	radar.AddComponent<TranformComponent>(glm::vec2(windowWidth - 74.0, windowHeight - 74.0), glm::vec2(1, 1), 0.0);
	radar.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 0.0));
	radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 1, true);
	radar.AddComponent<AnimationComponent>(8, 3, true);


	Entity tank = mRegistry->CreateEntity();
	tank.AddComponent<TranformComponent>(glm::vec2(10.0, 10.0), glm::vec2(2.0, 2.0), 0.0);
	tank.AddComponent<RigidBodyComponent>(glm::vec2(25.0, 0.0));
	tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1);
	tank.AddComponent<BoxColliderComponent>(25, 25, glm::vec2(7.0, 7.0));

	Entity tank2 = mRegistry->CreateEntity();
	tank2.AddComponent<TranformComponent>(glm::vec2(450.0, 10.0), glm::vec2(2.0, 2.0), 0.0);
	tank2.AddComponent<RigidBodyComponent>(glm::vec2(25.0, 0));
	tank2.AddComponent<SpriteComponent>("truck-image", 32, 32, 1);
	tank2.AddComponent<BoxColliderComponent>(25, 25, glm::vec2(7.0, 7.0));
}
void EchoGame::Setup() {
	LoadLevel();
}

void EchoGame::Update()
{
	/*int timeToWait = ECHO2D_MILLISECS_PER_FRAME - (SDL_GetTicks() - mMillisecPreviousFrame);
	if (timeToWait > 0)
		SDL_Delay(timeToWait);*/

	double deltaTime = (SDL_GetTicks() - mMillisecPreviousFrame) / 1000.0;
	mMillisecPreviousFrame = SDL_GetTicks();

	mEventBus->Reset();
	mRegistry->Update();

	mRegistry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(mEventBus);
	mRegistry->GetSystem<DamageSystem>().SubscribeToEvents(mEventBus);

	mRegistry->GetSystem<MovementSystem>().Update(deltaTime);
	mRegistry->GetSystem<BoxColliderSystem>().Update(mEventBus);
	mRegistry->GetSystem<AnimationSystem>().Update();
	mRegistry->GetSystem<CameraMovementSystem>().Update(mCamera);
}

void EchoGame::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 21, 21, 21, 255);
	SDL_RenderClear(mRenderer);
	//TODO: Renderer all gameobjects
	mRegistry->GetSystem<RenderSystem>().Update(mRenderer, mAssetStore, mCamera);
	mRegistry->GetSystem<RenderColliderDebugSystem>().Update(mRenderer, mCamera);
	mRegistry->GetSystem<RenderSpriteDebugSystem>().Update(mRenderer, mCamera);

	SDL_RenderPresent(mRenderer);
}

void EchoGame::Destroy()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	LOG_INFO("Game destroy called");
}
