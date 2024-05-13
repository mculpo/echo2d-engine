#ifndef KEYPRESSEDEVENT_ECHO2D_H
#define KEYPRESSEDEVENT_ECHO2D_H
#include "../Core/Core.h"
#include "../Event/Event.h"
class KeyPressedEvent : public Event {
public:
	SDL_Keycode mSymbol;
	KeyPressedEvent(SDL_Keycode pSimbol) : mSymbol(pSimbol) {}
};
#endif // !KEYPRESSEDEVENT_ECHO2D_H

