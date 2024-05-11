#ifndef EVENT_ECHO2D_H
#define EVENT_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
class Event
{
public:
	Event() {
		LOG_INFO("Event constructor called");
	}
	~Event() {
		LOG_INFO("Event destructor called");
	}
	/*
	void SubscribeToEvent<>() {
		//TODO
	};
	void UnsubscribeToEvent<>() {
		//TODO
	};
	void InvokeEvent<>() {
		//TODO
	};*/
};

#endif

