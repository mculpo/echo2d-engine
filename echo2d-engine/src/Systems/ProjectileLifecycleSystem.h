#ifndef PROJETILELIFECYCLESYSTEM_ECHO2D
#define PROJETILELIFECYCLESYSTEM_ECHO2D

#include "../Core/Core.h"
#include "../Components/ProjectileComponent.h"

class ProjectileLifecycleSystem : public System {
public:
	ProjectileLifecycleSystem() {
		RequireComponent<ProjectileComponent>();
	}

	void Update() {
		for (auto entity : GetSystemEntities()) {
			auto projectile = entity.GetComponent<ProjectileComponent>();

			if (SDL_GetTicks() - projectile.startTime > projectile.duration) {
				entity.Destroy();
			}
		}
	}
};

#endif
