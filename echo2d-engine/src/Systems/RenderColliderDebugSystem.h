#ifndef RENDERCOLLIDERDEBUGSYSTEM_ECHO2D_H
#define RENDERCOLLIDERDEBUGSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"


class RenderColliderDebugSystem : public System {
public:
	RenderColliderDebugSystem() {
		RequireComponent<TranformComponent>();
		RequireComponent<BoxColliderComponent>();
	}

	void Update(SDL_Renderer* pRenderer, SDL_Rect pCamera) {
		SDL_SetRenderDrawColor(pRenderer, 0, 255, 0, 255); // Verde
		for (auto entity : GetSystemEntities()) {

			auto& transform = entity.GetComponent<TranformComponent>();
			auto& collider = entity.GetComponent<BoxColliderComponent>();

			SDL_Rect rect;
			rect.x = static_cast<int>(transform.position.x + collider.offset.x - pCamera.x);
			rect.y = static_cast<int>(transform.position.y + collider.offset.y - pCamera.y);
			rect.w = static_cast<int>(collider.width * transform.scale.x);
			rect.h = static_cast<int>(collider.height * transform.scale.y);

			// Desenhando o retângulo
			SDL_RenderDrawRect(pRenderer, &rect);

		}
	}
};

#endif
