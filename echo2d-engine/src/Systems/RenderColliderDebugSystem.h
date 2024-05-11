#ifndef RENDERCOLLIDERDEBUGSYSTEM_ECHO2D_H
#define RENDERCOLLIDERDEBUGSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../AssetStore/AssetStore.h"


class RenderColliderDebugSystem : public System {
public:
	RenderColliderDebugSystem() {
		RequireComponent<TranformComponent>();
		RequireComponent<BoxColliderComponent>();
	}

	void Update(SDL_Renderer* pRenderer) {
		SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255); // Verde
		for (auto entity : GetSystemEntities()) {

			auto& transform = entity.GetComponent<TranformComponent>();
			auto& collider = entity.GetComponent<BoxColliderComponent>();

			SDL_Rect rect;
			rect.x = static_cast<int>(transform.position.x + collider.offset.x);
			rect.y = static_cast<int>(transform.position.y + collider.offset.y);
			rect.w = static_cast<int>(collider.width);
			rect.h = static_cast<int>(collider.height);

			// Desenhando o retângulo
			SDL_RenderDrawRect(pRenderer, &rect);

		}
	}
};

#endif
