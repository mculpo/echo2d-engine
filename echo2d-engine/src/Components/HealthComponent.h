#ifndef HEALTHCOMPONENT_ECHO2D_H
#define HEALTHCOMPONENT_ECHO2D_H

#include "../Core/Core.h"

struct HealthComponent {
	int healthPercentage;
	HealthComponent(int pHealthPercentage = 0) {
		healthPercentage = pHealthPercentage;
	}
};

#endif
