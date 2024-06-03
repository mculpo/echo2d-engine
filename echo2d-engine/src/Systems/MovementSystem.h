#ifndef MOVEMENTSYSTEM_ECHO2D_H
#define MOVEMENTSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"

class MovementSystem : public System {
public:
	MovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<RigidBodyComponent>();
	}
	~MovementSystem() {};
	void Update(double deltaTime) {
		// TODO
		for (auto& entity : GetSystemEntities()) {
			auto& transform = entity.GetComponent<TransformComponent>();
			const auto rigdibody = entity.GetComponent<RigidBodyComponent>();

			transform.position.x += (rigdibody.velocity.x * deltaTime);
			transform.position.y += (rigdibody.velocity.y * deltaTime);
		}
	}
};

#endif // !MOVEMENTSYSTEM_ECHO2D_H
