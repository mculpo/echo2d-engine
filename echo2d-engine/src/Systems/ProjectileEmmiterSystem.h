#ifndef PROJETILEEMMITERSYSTEM_ECHO2D
#define PROJETILEEMMITERSYSTEM_ECHO2D

#include "../Core/Core.h"
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmmiterComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Event/EventBus.h"

#include "../Events/CollisionEvent.h"

class ProjectileEmmiterSystem : public System {
public:
	ProjectileEmmiterSystem() {
		RequireComponent<ProjectileEmmiterComponent>();
		RequireComponent<TransformComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& pEventBus) {
		pEventBus->SubscribeToEvent<KeyPressedEvent>(this, &ProjectileEmmiterSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& event) {
		if (event.mSymbol == SDLK_SPACE) {
			for (auto entity : GetSystemEntities()) {
				if (entity.HasComponent<CameraFollowComponent>()) {
					const auto projectileEmmiter = entity.GetComponent<ProjectileEmmiterComponent>();
					const auto transform = entity.GetComponent<TransformComponent>();
					const auto rigidbody = entity.GetComponent<RigidBodyComponent>();

					glm::vec2 projectilePosition = transform.position;
					if (entity.HasComponent<SpriteComponent>()) {
						const auto sprite = entity.GetComponent<SpriteComponent>();
						projectilePosition.x += (transform.scale.x * sprite.srcRect.w / 2);
						projectilePosition.y += (transform.scale.y * sprite.srcRect.h / 2);
					}

					glm::vec2 projectileVelocity = projectileEmmiter.projectileVelocity;
					int directionX = 0;
					int directionY = 0;
					if (rigidbody.velocity.x > 0) directionX = +1;
					if (rigidbody.velocity.x < 0) directionX = -1;
					if (rigidbody.velocity.y > 0) directionY = +1;
					if (rigidbody.velocity.y < 0) directionY = -1;

					projectileVelocity.x = projectileEmmiter.projectileVelocity.x * directionX;
					projectileVelocity.y = projectileEmmiter.projectileVelocity.y * directionY;

					Entity projectile = entity.mRegistry->CreateEntity();
					projectile.Group("projectiles");
					projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0.0);
					projectile.AddComponent<RigidBodyComponent>(projectileVelocity);
					projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
					projectile.AddComponent<BoxColliderComponent>(4, 4);
					projectile.AddComponent<ProjectileComponent>(projectileEmmiter.isFriendly, projectileEmmiter.hitPercentDamage, projectileEmmiter.projectileDuration);

				}
			}
		}
	}

	void Update(std::unique_ptr<Registry>& pRegistry) {
		for (auto entity : GetSystemEntities()) {
			auto& projectileEmmiter = entity.GetComponent<ProjectileEmmiterComponent>();
			const auto transform = entity.GetComponent<TransformComponent>();

			if (projectileEmmiter.repeatFrequency == 0)
				continue;

			if (SDL_GetTicks() - projectileEmmiter.lastEmissionTime > projectileEmmiter.repeatFrequency) {

				glm::vec2 projectilePosition = transform.position;
				if (entity.HasComponent<SpriteComponent>()) {
					const auto sprite = entity.GetComponent<SpriteComponent>();
					projectilePosition.x += (transform.scale.x * sprite.srcRect.w / 2);
					projectilePosition.y += (transform.scale.y * sprite.srcRect.h / 2);
				}

				Entity projectile = pRegistry->CreateEntity();
				projectile.Group("projectiles");
				projectile.AddComponent<TransformComponent>(projectilePosition, glm::vec2(1.0, 1.0), 0.0);
				projectile.AddComponent<RigidBodyComponent>(projectileEmmiter.projectileVelocity);
				projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
				projectile.AddComponent<BoxColliderComponent>(4, 4);
				projectile.AddComponent<ProjectileComponent>(projectileEmmiter.isFriendly, projectileEmmiter.hitPercentDamage, projectileEmmiter.projectileDuration);


				projectileEmmiter.lastEmissionTime = SDL_GetTicks();
			}
		}
	}
};

#endif // !PROJETILEEMMITERSYSTEM_ECHO2D



