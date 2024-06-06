#ifndef RENDERSYSTEM_ECHO2D_H
#define RENDERSYSTEM_ECHO2D_H

#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Core/Core.h"

class RenderSystem : public System {
public:
	RenderSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
	}
	~RenderSystem() {};
	void Update(SDL_Renderer* pRenderer, std::unique_ptr<AssetStore>& pAssetStore, SDL_Rect& pCamera) {

		struct RenderableEntity {
			std::reference_wrapper <TransformComponent> transformComponent;
			std::reference_wrapper <SpriteComponent> spriteComponent;
		};

		std::vector<RenderableEntity> _renderableEntity;
		_renderableEntity.reserve(GetSystemEntities().size());

		for (auto& entity : GetSystemEntities()) {
			
			auto &spriteComponent = entity.GetComponent<SpriteComponent>();
			auto &transformComponent = entity.GetComponent<TransformComponent>();

			if (IsEntityOutsideCameraView(transformComponent, spriteComponent, pCamera) && !spriteComponent.isStatic) {
				continue;
			}

			_renderableEntity.push_back({ transformComponent , spriteComponent});
		}

		//sort the vector by the z-index value
		std::sort(
			_renderableEntity.begin(),
			_renderableEntity.end(),
			[](const RenderableEntity& a, const RenderableEntity& b) {
				return a.spriteComponent.get().zIndex < b.spriteComponent.get().zIndex;
			}
		);

		// TODO
		for (auto& entity : _renderableEntity) {
			SDL_Rect destRect;
			destRect.x = static_cast<int>(entity.transformComponent.get().position.x) - (entity.spriteComponent.get().isStatic ? 0 : pCamera.x);
			destRect.y = static_cast<int>(entity.transformComponent.get().position.y) - (entity.spriteComponent.get().isStatic ? 0 : pCamera.y);
			destRect.w = static_cast<int>(entity.spriteComponent.get().srcRect.w * entity.transformComponent.get().scale.x);
			destRect.h = static_cast<int>(entity.spriteComponent.get().srcRect.h * entity.transformComponent.get().scale.y);

			SDL_RenderCopyEx(
				pRenderer,
				pAssetStore->GetTexture(entity.spriteComponent.get().texture),
				&entity.spriteComponent.get().srcRect,
				&destRect,
				entity.transformComponent.get().rotation,
				NULL,
				entity.spriteComponent.get().flip
			);
		}
	}
private:
	bool IsEntityOutsideCameraView(const TransformComponent& transformComponent, const SpriteComponent& spriteComponent, const SDL_Rect& pCamera) const {
		return (
			transformComponent.position.x + (transformComponent.scale.x * spriteComponent.srcRect.w) < pCamera.x ||
			transformComponent.position.x > pCamera.x + pCamera.w ||
			transformComponent.position.y + (transformComponent.scale.y * spriteComponent.srcRect.h) < pCamera.y ||
			transformComponent.position.y > pCamera.y + pCamera.h
			);
	}
};
#endif
