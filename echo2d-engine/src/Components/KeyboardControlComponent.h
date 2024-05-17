#ifndef KEYBOARDCONTROLLERCOMPONENT_ECHO2D_H
#define KEYBOARDCONTROLLERCOMPONENT_ECHO2D_H

#include "../Core/Core.h"

struct KeyboardControlComponent {
	glm::vec2 velocityObject;

	KeyboardControlComponent(glm::vec2 pVelocityObject =  glm::vec2(0)) {
		velocityObject = pVelocityObject;
	}
};

#endif
