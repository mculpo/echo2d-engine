#ifndef COLLISIONEVENT_ECHO2D_H
#define COLLISIONEVENT_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Event/Event.h"

class CollisionEvent : public Event
{
public:
	Entity a;
	Entity b;
	CollisionEvent(Entity pA, Entity pB) : a(pA) , b(pB) {}
};

#endif

