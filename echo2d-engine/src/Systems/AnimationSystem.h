#ifndef ANIMATIONSYSTEM_ECHO2D_H
#define ANIMATIONSYSTEM_ECHO2D_H

#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"

class AnimationSystem : public System {
public:
	AnimationSystem() {
		RequireComponent<AnimationComponent>();
		RequireComponent<SpriteComponent>();
	}

	void Update() {

		int currentTime = SDL_GetTicks(); // Obter o tempo atual

		for (auto entity : GetSystemEntities()) {
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			// Verifica se é hora de avançar para o próximo quadro
			if (currentTime - animation.lastUpdateTime >= (1000 / animation.frameSpeedRate)) {
				animation.currentFrame = (animation.currentFrame + 1) % animation.numFrames;
				animation.lastUpdateTime = currentTime;
			}

			/*animation.currentFrame = 
				((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;*/

			sprite.srcRect.x = animation.currentFrame * sprite.srcRect.w;
			//sprite.srcRect.y = animation.currentFrame * sprite.srcRect.h;
		}
	}
};

#endif
