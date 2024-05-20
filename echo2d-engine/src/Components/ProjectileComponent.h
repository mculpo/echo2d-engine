#ifndef PROJECTILECOMPONENT_ECHO2D_H
#define PROJECTILECOMPONENT_ECHO2D_H

#include "../Core/Core.h"

struct ProjectileComponent {

	bool isFriendly;
	int hitPercentDamage;
	int duration;
	int startTime;

	ProjectileComponent(bool pIsFriendly = false, int pHitPercentDamage = 0, int pDuration = 0) {
		isFriendly = pIsFriendly;
		hitPercentDamage = pHitPercentDamage;
		duration = pDuration;
		startTime = SDL_GetTicks();
	}

};

#endif
