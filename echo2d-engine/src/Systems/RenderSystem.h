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
	void Update(SDL_Renderer* pRenderer, std::unique_ptr<AssetStore>& pAssetStore) {

		struct RenderableEntity {
			TranformComponent tranformComponent;
			SpriteComponent spriteComponent;
		};

		std::vector<RenderableEntity> _renderableEntity;
		for (auto& entity : GetSystemEntities()) {
			RenderableEntity renderableEntity;
			renderableEntity.spriteComponent = entity.GetComponent<SpriteComponent>();
			renderableEntity.tranformComponent = entity.GetComponent<TranformComponent>();
			_renderableEntity.emplace_back(renderableEntity);
		}
		//sort the vector by the z-index value
		std::sort(
			_renderableEntity.begin(),
			_renderableEntity.end(),
			[](const RenderableEntity& a, const RenderableEntity& b) {
				return a.spriteComponent.zIndex < b.spriteComponent.zIndex;
			}
		);

		// TODO
		for (auto& entity : _renderableEntity) {
			const auto transform = entity.tranformComponent;
			const auto sprite = entity.spriteComponent;

			SDL_Rect dstRect = {
				static_cast<int> (transform.position.x),
				static_cast<int> (transform.position.y),
				static_cast<int> (sprite.srcRect.w * transform.scale.x),
				static_cast<int> (sprite.srcRect.h * transform.scale.y)
			};

			SDL_RenderCopyEx(
				pRenderer,
				pAssetStore->GetTexture(sprite.texture),
				&sprite.srcRect,
				&dstRect,
				transform.rotation,
				NULL,
				SDL_FLIP_NONE
			);
		}
	}
};
#endif
