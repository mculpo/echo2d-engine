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

			if (entity.HasTag("player")) {
				transform.position.x = transform.position.x < 0 ? 0 : transform.position.x;
				transform.position.y = transform.position.y < 0 ? 0 : transform.position.y;
				transform.position.x = transform.position.x > EchoGame::mapWidth - 40 ? EchoGame::mapWidth - 40: transform.position.x;
				transform.position.y = transform.position.y > EchoGame::mapHeight - 40 ? EchoGame::mapHeight - 40 : transform.position.y;
			}

			if (IsEntityOutsideMap(transform) && !entity.HasTag("player")) {
				entity.Destroy();
			}
		}
	}
private:
	bool IsEntityOutsideMap(TransformComponent pTranformComponent) {
		return (
			pTranformComponent.position.x < 0 || pTranformComponent.position.y > EchoGame::mapWidth ||
			pTranformComponent.position.y < 0 || pTranformComponent.position.y > EchoGame::mapHeight
		);
	}
};

#endif // !MOVEMENTSYSTEM_ECHO2D_H
