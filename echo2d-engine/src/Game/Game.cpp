#include "Game.h"


EchoGame::EchoGame() : mIsRunning(false)
{
	mRegistry = std::make_unique<Registry>();
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
	mWindowWidth = 800; //displayMode.w;
	mWindowHeight = 600; //displayMode.h;
	mWindow = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		mWindowWidth,
		mWindowHeight,
		SDL_WINDOW_BORDERLESS
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
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) {
				mIsRunning = false;
				break;
			}
		}
	}
}

glm::vec2 position;
glm::vec2 velocity;

void EchoGame::Setup() {

	mRegistry->AddSystem<MovementSystem>();
	mRegistry->AddSystem<RenderSystem>();

	//TODO: Initialize the GameObjects
	Entity tank = mRegistry->CreateEntity();
	Entity tank2 = mRegistry->CreateEntity();

	tank.AddComponent<TranformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
	tank.AddComponent<RigidBodyComponent>(glm::vec2(30.0, 0.0));
	tank.AddComponent<SpriteComponent>(20 , 20);

	tank2.AddComponent<TranformComponent>(glm::vec2(10.0, 10.0), glm::vec2(1.0, 1.0), 0.0);
	tank2.AddComponent<RigidBodyComponent>(glm::vec2(0.0, 30.0));
	tank2.AddComponent<SpriteComponent>(10, 100);
}

void EchoGame::Update()
{
	int timeToWait = ECHO2D_MILLISECS_PER_FRAME - (SDL_GetTicks() - mMillisecPreviousFrame);
	if (timeToWait > 0)
		SDL_Delay(timeToWait);

	double deltaTime = (SDL_GetTicks() - mMillisecPreviousFrame) / 1000.0;
	mMillisecPreviousFrame = SDL_GetTicks();

	mRegistry->GetSystem<MovementSystem>().Update(deltaTime);

	mRegistry->Update();
}

void EchoGame::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 21, 21, 21, 255);
	SDL_RenderClear(mRenderer);
	//TODO: Renderer all gameobjects
	mRegistry->GetSystem<RenderSystem>().Update(mRenderer);

	SDL_RenderPresent(mRenderer);
}

void EchoGame::Destroy()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	LOG_INFO("Game destroy called");
}
