#ifndef RENDERHEALTHBARSYSTEM_ECHO2D_H
#define RENDERHEALTHBARSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../Components/SpriteComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../AssetStore/AssetStore.h"

class RenderHealthBarSystem : public System {
public:
	RenderHealthBarSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>(); 
		RequireComponent<HealthComponent>();
	}

	void Update(SDL_Renderer* pRenderer, std::unique_ptr<AssetStore>& pAssetStore, SDL_Rect& pCamera) {
		for (auto entity : GetSystemEntities()) {
			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();
			const auto health = entity.GetComponent<HealthComponent>();

			SDL_Color currentColor = SDL_COLOR_GREEN;
			
			int rectPositionX = transform.position.x - sprite.srcRect.x/2;
			int rectPositionY = transform.position.y - sprite.srcRect.y/2;
			int rectWidth = sprite.srcRect.x;
			int rectHeight = 3;

		}
	}
};

#endif