#ifndef MAPAEDITOR_ECHO2D_H
#define MAPAEDITOR_ECHO2D_H

#include "../Core/Core.h"

class MapaEditor
{
private:

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	
	bool mIsRunning;

public:
	MapaEditor();
	~MapaEditor();
	void Initialize();
	void Run();
	void ProcessingInput();
	void Setup();
	void Update();
	void Render();
	void Destroy();
};

#endif

