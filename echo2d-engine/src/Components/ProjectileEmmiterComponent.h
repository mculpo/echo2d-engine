#ifndef PROJECTILEEMMITERCOMPONENT_ECHO2D_H
#define PROJECTILEEMMITERCOMPONENT_ECHO2D_H

#include "../Core/Core.h"

struct ProjectileEmmiterComponent {
	glm::vec2 projectileVelocity;
	int repeatFrequency;
	int projectileDuration;
	int hitPercentDamage;
	bool isFriendly;
	int lastEmissionTime;

	ProjectileEmmiterComponent(glm::vec2 pProjectileVelocity = VEC2_ZERO, int pRepeatFrequency = 0, int pProjectileDuration = 0, int pHitPercentDamage = 0, bool pIsFriendly = false) {
		projectileVelocity = pProjectileVelocity;
		repeatFrequency = pRepeatFrequency;
		projectileDuration = pProjectileDuration;
		hitPercentDamage = pHitPercentDamage;
		isFriendly = pIsFriendly;
		lastEmissionTime= SDL_GetTicks();
	}
};

#endif
