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
		auto deltaTime = Time::GetInstance().DeltaTime();
		for (auto entity : GetSystemEntities()) {
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			animation.currentTimeAnimation += deltaTime;

			auto& _curAnimation = animation.animations[animation.currentAnimation];
			auto _curAnimFrame = _curAnimation.animationFrames[_curAnimation.currentFrame];
			if (animation.currentTimeAnimation >= _curAnimFrame.timeToEnd) {
				bool isLastFrame = _curAnimation.currentFrame >= _curAnimation.animationFrames.size() - 1;
				if (isLastFrame && _curAnimation.isLoop) {
					_curAnimation.currentFrame = 0;
				}
				else {
					_curAnimation.currentFrame++;
				}
				animation.currentTimeAnimation = 0;
				_curAnimFrame = _curAnimation.animationFrames[_curAnimation.currentFrame];
			}

			sprite.srcRect.x = _curAnimFrame.rect.x;
			sprite.srcRect.y = _curAnimFrame.rect.y;
			sprite.srcRect.w = _curAnimFrame.rect.w;
			sprite.srcRect.h = _curAnimFrame.rect.h;


			//// Verifica se é hora de avançar para o próximo quadro
			//if (currentTime - animation.lastUpdateTime >= (1000 / animation.frameSpeedRate)) {
			//	animation.currentFrame = (animation.currentFrame + 1) % animation.numFrames;
			//	animation.lastUpdateTime = currentTime;
			//}

			///*animation.currentFrame = 
			//	((SDL_GetTicks() - animation.startTime) * animation.frameSpeedRate / 1000) % animation.numFrames;*/
		}
	}
};

#endif
