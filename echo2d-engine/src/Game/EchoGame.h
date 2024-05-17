#ifndef ECHO2D_GAME_H
#define ECHO2D_GAME_H

#include "../Core/Core.h"
#include "../AssetStore/AssetStore.h"
#include "../Event/EventBus.h"

class EchoGame {
private:
	bool mIsRunning;
	int mMillisecPreviousFrame = 0;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Rect mCamera;

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

	static int windowWidth;
	static int windowHeight;
	static int mapWidth;
	static int mapHeight;
};

#endif // !ECHO2D_GAME_H


