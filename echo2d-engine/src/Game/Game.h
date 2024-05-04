#ifndef ECHO2D_GAME_H
#define ECHO2D_GAME_H
#include "../Core/Core.h"

class EchoGame {
private:
	bool mIsRunning;
	int mMillisecPreviousFrame = 0;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
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


