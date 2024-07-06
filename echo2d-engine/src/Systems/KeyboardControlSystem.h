
#ifndef KEYBOARDCONTROLSYSTEM_ECHO2D_H
#define KEYBOARDCONTROLSYSTEM_ECHO2D_H

#include "../Core/Core.h"
#include "../Event/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/KeyboardControlComponent.h"

class KeyboardControlSystem : public System {
public:
	KeyboardControlSystem() {
		RequireComponent<KeyboardControlComponent>();
		RequireComponent<AnimationComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& pEvent) {

		for (auto entity : GetSystemEntities()) {
			auto keyboard = entity.GetComponent<KeyboardControlComponent>();
			auto& animation = entity.GetComponent<AnimationComponent>();
			auto& rigidbody = entity.GetComponent<RigidBodyComponent>();

			switch (pEvent.mSymbol)
			{
			case SDLK_UP:
				rigidbody.velocity = VEC2_UP * keyboard.velocityObject;
				animation.currentTimeAnimation = animation.currentAnimation = 0 ? animation.currentTimeAnimation : 0;
				animation.currentAnimation = 0;
				break;
			case SDLK_RIGHT:
				rigidbody.velocity = VEC2_RIGHT * keyboard.velocityObject;
				animation.currentTimeAnimation = animation.currentAnimation = 1 ? animation.currentTimeAnimation : 0;
				animation.currentAnimation = 1;
				break;
			case SDLK_DOWN:
				rigidbody.velocity = VEC2_DOWN * keyboard.velocityObject;
				animation.currentTimeAnimation = animation.currentAnimation = 2 ? animation.currentTimeAnimation : 0;
				animation.currentAnimation = 2;
				break;
			case SDLK_LEFT:
				rigidbody.velocity = VEC2_LEFT * keyboard.velocityObject;
				animation.currentTimeAnimation = animation.currentAnimation = 3 ? animation.currentTimeAnimation : 0;
				animation.currentAnimation = 3;
				break;
			}
		}

		/*std::string keyCode = std::to_string(pEvent.mSymbol);
		std::string keySymbol(1, pEvent.mSymbol);
		LOG_INFO("Key pressed event emitted: [" + keyCode + "] " + keySymbol);*/
	}
};

#endif // !KEYBOARDCONTROLSYSTEM_ECHO2D_H
