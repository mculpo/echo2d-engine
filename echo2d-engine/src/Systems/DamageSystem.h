#include "../Events/CollisionEvent.h"

#ifndef DAMAGESYSTEM_ECHO2D_h
#define DAMAGESYSTEM_ECHO2D_h
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Event/EventBus.h"
#include "../Components/BoxColliderComponent.h"

class DamageSystem : public System {
public:
	DamageSystem() {
		RequireComponent<BoxColliderComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& pEventBus) {
		pEventBus->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
	}

	void OnCollision(CollisionEvent& pEvent) {
		LOG_INFO(
			"The Damage System received an event collision between entites " + 
			std::to_string(pEvent.a.GetId()) + 
			" and " + 
			std::to_string(pEvent.b.GetId())
		);
		pEvent.a.Destroy();
		pEvent.b.Destroy();
	}

	void Update() {

	}
};

#endif // !DAMAGESYSTEM_ECHO2D_h

