#ifndef RENDERSPRITEDEBUGSYSTEM_ECHO2D_H
#define RENDERSPRITEDEBUGSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"
class RenderSpriteDebugSystem : public System {
public:
	RenderSpriteDebugSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<BoxColliderComponent>();
	}

	void Update(SDL_Renderer* pRenderer, SDL_Rect pCamera) {
		SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255); // Vermelho
		for (auto entity : GetSystemEntities()) {

			auto& transform = entity.GetComponent<TransformComponent>();
			auto& sprite = entity.GetComponent<SpriteComponent>();

			SDL_Rect rect;
			rect.x = static_cast<int>(transform.position.x - pCamera.x);
			rect.y = static_cast<int>(transform.position.y - pCamera.y);
			rect.w = static_cast<int>(sprite.srcRect.w * transform.scale.x);
			rect.h = static_cast<int>(sprite.srcRect.h * transform.scale.y);

			// Desenhando o retângulo
			SDL_RenderDrawRect(pRenderer, &rect);

		}
	}
};

#endif
