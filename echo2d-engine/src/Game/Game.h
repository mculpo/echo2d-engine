#ifndef ECHO2D_GAME_H
#define ECHO2D_GAME_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"

class EchoGame {
private:
	bool mIsRunning;
	int mMillisecPreviousFrame = 0;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	std::unique_ptr<Registry> mRegistry;
public:
	EchoGame();
	~EchoGame();
	void Initialize();
	void Run();
	void ProcessingInput();
	void Setup();
	void Update();
	void Render();
	void Destroy();

	int mWindowWidth;
	int mWindowHeight;
};

#endif // !ECHO2D_GAME_H


