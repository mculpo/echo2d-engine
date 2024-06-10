#include "EchoGame.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmmiterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/ColliderSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/ProjectileEmmiterSystem.h"
#include "../Systems/ProjectileLifecycleSystem.h"
#include "../Systems/RenderColliderDebugSystem.h"
#include "../Systems/RenderSpriteDebugSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../Systems/RenderHealthBarSystem.h"
#include "../Systems/RenderEditorSystem.h"
#include "../Systems/ScriptSystem.h"

#include "LoaderLevel.h"

int EchoGame::windowWidth;
int EchoGame::windowHeight;
int EchoGame::mapWidth;
int EchoGame::mapHeight;

EchoGame::EchoGame() : mIsRunning(false), mTime(Time::GetInstance())
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

	if (TTF_Init() != ECHO2D_SUCCESS) {
		LOG_ERROR("Error initializing TTF");
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
		SDL_WINDOW_OPENGL
	);

	if (!mWindow) {
		LOG_ERROR("Error creating SDL window");
		return;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED 
	);

	if (!mRenderer) {
		LOG_ERROR("Error creating SDL renderer");
		return;
	}

#ifdef _DEBUG
	// Inicializa ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Configura o estilo do ImGui
	ImGui::StyleColorsDark();

	// Inicializa ImGui para SDL2
	ImGui_ImplSDL2_InitForSDLRenderer(mWindow, mRenderer);
	ImGui_ImplSDLRenderer2_Init(mRenderer);
#endif

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
#ifdef _DEBUG
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
#endif
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

void EchoGame::Setup() {
	mRegistry->AddSystem<MovementSystem>();
	mRegistry->AddSystem<AnimationSystem>();
	mRegistry->AddSystem<ColliderSystem>();
	mRegistry->AddSystem<DamageSystem>();
	mRegistry->AddSystem<KeyboardControlSystem>();
	mRegistry->AddSystem<CameraMovementSystem>();
	mRegistry->AddSystem<ProjectileEmmiterSystem>();
	mRegistry->AddSystem<ProjectileLifecycleSystem>();
	mRegistry->AddSystem<ScriptSystem>();
	mRegistry->AddSystem<RenderColliderDebugSystem>();
	mRegistry->AddSystem<RenderSpriteDebugSystem>();
	mRegistry->AddSystem<RenderTextSystem>();
	mRegistry->AddSystem<RenderHealthBarSystem>();
	mRegistry->AddSystem<RenderSystem>();
#ifdef _DEBUG
	mRegistry->AddSystem<RenderEditorSystem>();
#endif // !_DEBUG

	

	//BINDING lua Scripts
	mRegistry->GetSystem<ScriptSystem>().CreateLuaBindings(mLua);

	LoaderLevel loaderLevel;
	mLua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os);
	loaderLevel.LoadLevel(mLua, mRegistry, mAssetStore, mRenderer, 1);
}

void EchoGame::Update()
{
	// run logical to calculet deltatime and timeToWait a Fps control
	mTime.Run();

	mEventBus->Reset();
	mRegistry->Update();

	mRegistry->GetSystem<KeyboardControlSystem>().SubscribeToEvents(mEventBus);
	mRegistry->GetSystem<DamageSystem>().SubscribeToEvents(mEventBus);
	mRegistry->GetSystem<ProjectileEmmiterSystem>().SubscribeToEvents(mEventBus);

	mRegistry->GetSystem<MovementSystem>().Update();
	mRegistry->GetSystem<AnimationSystem>().Update();
	mRegistry->GetSystem<ColliderSystem>().Update(mEventBus);
	mRegistry->GetSystem<ProjectileEmmiterSystem>().Update(mRegistry);
	mRegistry->GetSystem<ProjectileLifecycleSystem>().Update();
	mRegistry->GetSystem<CameraMovementSystem>().Update(mCamera);
	mRegistry->GetSystem<ScriptSystem>().Update();

	// update
	mTime.UpdateMillisecPreviousFrame();
}

void EchoGame::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 21, 21, 21, 255);
	SDL_RenderClear(mRenderer);

	mRegistry->GetSystem<RenderSystem>().Update(mRenderer, mAssetStore, mCamera);
	mRegistry->GetSystem<RenderHealthBarSystem>().Update(mRenderer, mAssetStore, mCamera);
	mRegistry->GetSystem<RenderTextSystem>().Update(mRenderer, mAssetStore, mCamera);
#ifdef _DEBUG
	mRegistry->GetSystem<RenderColliderDebugSystem>().Update(mRenderer, mCamera);
	mRegistry->GetSystem<RenderSpriteDebugSystem>().Update(mRenderer, mCamera);
	//mRegistry->GetSystem<RenderEditorSystem>().Update(mRenderer, mAssetStore, mCamera, mRegistry);
#endif

	SDL_RenderPresent(mRenderer);
}

void EchoGame::Destroy()
{
#ifdef _DEBUG
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
#endif
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	LOG_INFO("Game destroy called");
}
