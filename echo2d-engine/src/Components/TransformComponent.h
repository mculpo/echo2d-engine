#ifndef TRANSFORMCOMPONENT_ECHO2D_H
#define TRANSFORMCOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct TransformComponent {
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;

	TransformComponent(glm::vec2 pPosition = glm::vec2(0.0, 0.0), glm::vec2 pScale = glm::vec2(0.0, 0.0), float pRotation = 0) {
		this->position = pPosition;
		this->scale = pScale;
		this->rotation = pRotation;
	}
};

#endif