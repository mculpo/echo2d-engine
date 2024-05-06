#ifndef RENDERSYSTEM_ECHO2D_H
#define RENDERSYSTEM_ECHO2D_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Core/Core.h"

class RenderSystem : public System {
public:
	RenderSystem() {
		RequireComponent<TranformComponent>();
		RequireComponent<SpriteComponent>();
	}
	~RenderSystem() {};
	void Update(SDL_Renderer* pRenderer) {
		// TODO
		for (auto& entity : GetSystemEntities()) {
			const auto transform = entity.GetComponent<TranformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect objRect = {
				static_cast<int>(transform.mPosition.x),
				static_cast<int>(transform.mPosition.y),
				sprite.width,
				sprite.height
			};
			SDL_SetRenderDrawColor(pRenderer, 255, 255, 255, 255);
			SDL_RenderFillRect(pRenderer, &objRect);
		}
	}
};
#endif
