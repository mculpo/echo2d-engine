#ifndef SPRITECOMPONENT_ECHO2D_H
#define SPRITECOMPONENT_ECHO2D_H
#include "../Core/Core.h"

struct SpriteComponent {
	std::string texture;
	int zIndex;
	SDL_Rect srcRect;
	SDL_RendererFlip flip;
	SpriteComponent(std::string pTexture = "", int pWidth = 0, int pHeight = 0, int pZIndex = 0, int srcRectX = 0, int srcRectY = 0, SDL_RendererFlip pFlip = SDL_FLIP_NONE) {
		texture = pTexture;
		srcRect = { srcRectX, srcRectY, pWidth, pHeight };
		zIndex = pZIndex;
		flip = pFlip;
	};
};

#endif // !SPRITECOMPONENT_ECHO2D_H
