#ifndef RIGIDBODYCOMPONENT_ECHO2D_H
#define RIGIDBODYCOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct RigidBodyComponent {
	glm::vec2 velocity;
	RigidBodyComponent(glm::vec2 pVelocity = glm::vec2(0.0, 0.0)) {
		this->velocity = pVelocity;
	}
};

#endif // !RIGIDBODYCOMPONENT_ECHO2D_H

