#ifndef ANIMATIONCOMPONENT_ECHO2D_H
#define ANIMATIONCOMPONENT_ECHO2D_H

#include "../Core/Core.h"
struct AnimationFrame {
	SDL_Rect rect;
	float timeToEnd;

	AnimationFrame(int pX = 0, int pY = 0, int pW = 0, int pH = 0, float pTimeToEnd = 0.0) {
		rect.x = pX;
		rect.y = pY;
		rect.w = pW;
		rect.h = pH;
		timeToEnd = pTimeToEnd;
	}
};
struct Animation {
	std::vector<AnimationFrame> animationFrames;
	int currentFrame;
	bool isLoop;

	Animation(std::vector<AnimationFrame> pAnimationFrames = {}, bool pIsLoop = false) {
		currentFrame = 0;
		animationFrames = pAnimationFrames;
		isLoop = pIsLoop;
	}
};
struct AnimationComponent {

	std::vector<Animation> animations;
	float currentTimeAnimation;
	int currentAnimation;
	
	AnimationComponent(int pCurrentAnimation = 0, std::vector<Animation> pAnimations = {}) {
		currentAnimation = pCurrentAnimation;
		animations = pAnimations;
		currentTimeAnimation = 0.0;
	}
};

#endif // !ANIMATIONCOMPONENT_ECHO2D_H

