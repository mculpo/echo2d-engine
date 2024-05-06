#ifndef SPRITECOMPONENT_ECHO2D_H
#define SPRITECOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct SpriteComponent {
	int width;
	int height;
	SpriteComponent(int pWidth = 0, int pHeight = 0) {
		width = pWidth;
		height = pHeight;
	};
};

#endif // !SPRITECOMPONENT_ECHO2D_H
