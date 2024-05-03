#include "Game.h"

EchoGame::EchoGame() : mIsRunning(false)
{
	std::cout << "Game construction called" << std::endl;
}

EchoGame::~EchoGame()
{
	std::cout << "Game destruction called" << std::endl;
}

void EchoGame::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != ECHO2D_SUCCESS) {
		std::cerr << "Error initializing SDL" << std::endl;
	}

	mWindow = SDL_CreateWindow(
		NULL,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		800,
		600,
		SDL_WINDOW_BORDERLESS
	);

	if (!mWindow) {
		std::cerr << "Error creating SDL window" << std::endl;
		return;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
	if (!mRenderer) {
		std::cerr << "Error creating SDL renderer" << std::endl;
		return;
	}

	mIsRunning = true;
}

void EchoGame::Run()
{
	std::cout << "Game run called" << std::endl;
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

void EchoGame::Update()
{
	//TODO: Update game objects
}

void EchoGame::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_RenderClear(mRenderer); 

	//TODO: Renderer all gameobjects

	SDL_RenderPresent(mRenderer);
	
}

void EchoGame::Destroy()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	std::cout << "Game destroy called" << std::endl;
}
