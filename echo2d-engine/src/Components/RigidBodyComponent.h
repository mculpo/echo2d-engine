#ifndef RIGIDBODYCOMPONENT_ECHO2D_H
#define RIGIDBODYCOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct RigidBodyComponent {
	glm::vec2 mVelocity;
	RigidBodyComponent(glm::vec2 pVelocity = glm::vec2(0.0, 0.0)) {
		this->mVelocity = pVelocity;
	}
};

#endif // !RIGIDBODYCOMPONENT_ECHO2D_H

