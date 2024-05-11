#ifndef BOXCOLLIDERSYSTEM_ECHO2D_H
#define BOXCOLLIDERSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/TransformComponent.h"

class BoxColliderSystem : public System {
public:
	BoxColliderSystem () {
		RequireComponent<BoxColliderComponent>();
		RequireComponent<TranformComponent>();
	}

	void Update() {
		auto entities = GetSystemEntities();

		for (auto i = entities.begin(); i != entities.end(); i++) {
			Entity a = *i;
			auto aTransform = a.GetComponent<TranformComponent>();
			auto aCollider = a.GetComponent<BoxColliderComponent>();
			for (auto j = i; j != entities.end(); j++) {
				Entity b = *j;
			
				if (a == b) continue;

				auto bTransform = b.GetComponent<TranformComponent>();
				auto bCollider = b.GetComponent<BoxColliderComponent>();

				bool isCollision = CheckAABBCollision(	aTransform.position.x, aTransform.position.y, aCollider.width, aCollider.height,
														bTransform.position.x, bTransform.position.y, bCollider.width, bCollider.height);

				if (isCollision) {
					//TODO: Event
				}
			}
		}
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
