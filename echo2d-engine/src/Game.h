#ifndef ECHO2D_GAME_H
#define ECHO2D_GAME_H
#include "Core.h"

class EchoGame {
private:
	bool mIsRunning;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
public:
	EchoGame();
	~EchoGame();
	void Initialize();
	void Run();
	void ProcessingInput();
	void Update();
	void Render();
	void Destroy();
};

#endif // !ECHO2D_GAME_H


