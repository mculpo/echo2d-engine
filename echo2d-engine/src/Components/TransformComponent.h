#ifndef TRANSFORMCOMPONENT_ECHO2D_H
#define TRANSFORMCOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct TranformComponent {
	glm::vec2 mPosition;
	glm::vec2 mScale;
	double mRotation;
	TranformComponent(glm::vec2 pPosition = glm::vec2(0.0, 0.0), glm::vec2 pScale = glm::vec2(0.0, 0.0), double pRotation = 0) {
		this->mPosition = pPosition;
		this->mScale = pScale;
		this->mRotation = pRotation;
	}
};

#endif