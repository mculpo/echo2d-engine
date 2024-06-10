#ifndef ANIMATIONCOMPONENT_ECHO2D_H
#define ANIMATIONCOMPONENT_ECHO2D_H

#include "../Core/Core.h"

struct AnimationComponent {

	int numFrames;
	int frameSpeedRate;
	int currentFrame;
	int startTime;
	int lastUpdateTime;

	bool isLoop;

	AnimationComponent(int pNumFrames = 1, int pFrameSpeedRate = 1, bool pIsLoop = true) {
		this->numFrames = pNumFrames;
		this->currentFrame = 1;
		this->frameSpeedRate = pFrameSpeedRate;
		this->isLoop = pIsLoop;
		this->startTime = SDL_GetTicks();
		this->lastUpdateTime = startTime;
	}
};

#endif // !ANIMATIONCOMPONENT_ECHO2D_H

