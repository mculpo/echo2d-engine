
#ifndef DAMAGESYSTEM_ECHO2D_h
#define DAMAGESYSTEM_ECHO2D_h
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Event/EventBus.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/HealthComponent.h"
#include "../Events/CollisionEvent.h"

class DamageSystem : public System {
public:
	DamageSystem() {
		RequireComponent<BoxColliderComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& pEventBus) {
		pEventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
	}

	void OnCollision(CollisionEvent& pEvent) {
		Entity a = pEvent.a;
		Entity b = pEvent.b;
		if (a.BelongsToGroup("projectiles") && b.HasTag("player")) {
			OnProjectileHitsPlayer(a, b);
		} 
		
		if (b.BelongsToGroup("projectiles") && a.HasTag("player")) {
			OnProjectileHitsPlayer(b, a);
		}

		if (a.BelongsToGroup("projectiles") && b.BelongsToGroup("enemies")) {
			OnProjectileHitsEnemy(a, b);
		}

		if (b.BelongsToGroup("projectiles") && a.BelongsToGroup("enemies")) {
			OnProjectileHitsEnemy(b, a);
		}
	}

	void OnProjectileHitsPlayer(Entity projectile, Entity player) {
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();
		if (!projectileComponent.isFriendly) {
			auto &healthComponent = player.GetComponent<HealthComponent>();
			healthComponent.healthPercentage -= projectileComponent.hitPercentDamage;
			if (healthComponent.healthPercentage <= 0) {
				player.Destroy();
			}
			projectile.Destroy();
		}
	}

	void OnProjectileHitsEnemy(Entity projectile, Entity enemy) {
		auto projectileComponent = projectile.GetComponent<ProjectileComponent>();
		if (projectileComponent.isFriendly) {
			auto& healthComponent = enemy.GetComponent<HealthComponent>();
			healthComponent.healthPercentage -= projectileComponent.hitPercentDamage;
			if (healthComponent.healthPercentage <= 0) {
				enemy.Destroy();
			}
			projectile.Destroy();
		}
	}
};

#endif // !DAMAGESYSTEM_ECHO2D_h


