#ifndef SPRITECOMPONENT_ECHO2D_H
#define SPRITECOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct SpriteComponent {
	std::string texture;
	int zIndex;
	SDL_Rect srcRect;
	int flip;
	bool isStatic;
	SpriteComponent(std::string pTexture = "", int pWidth = 0, int pHeight = 0, int pZIndex = 0, bool pIsStatic = false ,int srcRectX = 0, int srcRectY = 0, int pFlip = SDL_FLIP_NONE) {
		texture = pTexture;
		srcRect = { srcRectX, srcRectY, pWidth, pHeight };
		zIndex = pZIndex;
		isStatic = pIsStatic;
		flip = pFlip;
	};
};

#endif // !SPRITECOMPONENT_ECHO2D_H
