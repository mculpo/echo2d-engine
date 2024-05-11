#ifndef BOXCOLLIDERCOMPONENT_ECHO2D_H
#define BOXCOLLIDERCOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct BoxColliderComponent {

	int width;
	int height;
	glm::vec2 offset;

	BoxColliderComponent(int pWidth = 0, int pHeight = 0, glm::vec2 pOffset = glm::vec2(0.0,0.0)) {
		this->width = pWidth;
		this->height = pHeight;
		this->offset = pOffset;
	}
};

#endif // !BOXCOLLIDERCOMPONENT_ECHO2D_H

