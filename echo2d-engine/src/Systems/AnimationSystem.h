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
				animation.currentTimeAnimation = 0;

				if (_curAnimation.isLoop) {
					_curAnimation.currentFrame = (_curAnimation.currentFrame + 1) % _curAnimation.animationFrames.size();
				}
				else {
					if (_curAnimation.currentFrame < _curAnimation.animationFrames.size() - 1) {
						_curAnimation.currentFrame++;
					}
				}
				
				_curAnimFrame = _curAnimation.animationFrames[_curAnimation.currentFrame];
			}

			sprite.srcRect.x = _curAnimFrame.rect.x;
			sprite.srcRect.y = _curAnimFrame.rect.y;
			sprite.srcRect.w = _curAnimFrame.rect.w;
			sprite.srcRect.h = _curAnimFrame.rect.h;
		}
	}
};

#endif
