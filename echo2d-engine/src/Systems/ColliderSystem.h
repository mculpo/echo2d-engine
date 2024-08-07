#ifndef BOXCOLLIDERSYSTEM_ECHO2D_H
#define BOXCOLLIDERSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"
#include "../Events/CollisionEvent.h"
#include "../Event/EventBus.h"

class ColliderSystem : public System {
public:
	ColliderSystem() {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TransformComponent>();
	}

	void Update(std::unique_ptr<EventBus>& pEventBus) {

		TaskTime::start("Collider");

		auto entities = GetSystemEntities();

		for (auto i = entities.begin(); i != entities.end(); i++) {
			Entity a = *i;
			auto aTransform = a.GetComponent<TransformComponent>();
			auto aCollider = a.GetComponent<BoxColliderComponent>();
			for (auto j = i; j != entities.end(); j++) {
				Entity b = *j;
			
				if (a == b) continue;

				auto bTransform = b.GetComponent<TransformComponent>();
				auto bCollider = b.GetComponent<BoxColliderComponent>();

				bool isCollision = CheckAABBCollision(	aTransform.position.x, aTransform.position.y, aCollider.width * aTransform.scale.x, aCollider.height * aTransform.scale.y,
														bTransform.position.x, bTransform.position.y, bCollider.width * bTransform.scale.x, bCollider.height * bTransform.scale.y);

				if (isCollision) {
					//TODO: Event
					pEventBus->InvokeEvent<CollisionEvent>(a, b);
				}
			}
		}
		TaskTime::stop("Collider");
	}

	bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH) {
		return (
			aX < bX + bW &&
			aX + aW > bX &&
			aY < bY + bH &&
			aY + aH > bY
		);
	}
};

#endif
