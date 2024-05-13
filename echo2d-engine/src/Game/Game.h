#ifndef ECHO2D_GAME_H
#define ECHO2D_GAME_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/BoxColliderSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/RenderColliderDebugSystem.h"
#include "../Systems/RenderSpriteDebugSystem.h"
#include "../Event/EventBus.h"

class EchoGame {
private:
	bool mIsRunning;
	int mMillisecPreviousFrame = 0;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	std::unique_ptr<Registry> mRegistry;
	std::unique_ptr<AssetStore> mAssetStore;
	std::unique_ptr<EventBus> mEventBus;
public:
	EchoGame();
	~EchoGame();
	void Initialize();
	void Run();
	void ProcessingInput();
	void LoadLevel(int level = 0);
	void Setup();
	void Update();
	void Render();
	void Destroy();

	int mWindowWidth;
	int mWindowHeight;
};

#endif // !ECHO2D_GAME_H


