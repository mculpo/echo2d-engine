#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "../Core/Core.h"

struct TextComponent {
	glm::vec2 mPosition;
	std::string mText;
	std::string mKeyAccess;
	SDL_Color mColor;
	bool mIsFixed;

	TextComponent(glm::vec2 pPosition = VEC2_ZERO, std::string pText = "", std::string pKeyAccess = "", const SDL_Color& pColor = {0,0,0}, bool pIsFixed = true) {
		this->mPosition = pPosition;
		this->mText = pText;
		this->mKeyAccess = pKeyAccess;
		this->mColor = pColor;
		this->mIsFixed = pIsFixed;
	}

};


#endif // !TEXTCOMPONENT_H

