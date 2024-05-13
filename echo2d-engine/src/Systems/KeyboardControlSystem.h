
#ifndef KEYBOARDCONTROLSYSTEM_ECHO2D_H
#define KEYBOARDCONTROLSYSTEM_ECHO2D_H

#include "../Core/Core.h"
#include "../Event/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"

class KeyboardControlSystem : public System {
public:
	KeyboardControlSystem() {
		RequireComponent<SpriteComponent>();
		RequireComponent<RigidBodyComponent>();
	}

	void SubscribeToEvents(std::unique_ptr<EventBus>& eventBus) {
		eventBus->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyPressed);
	}

	void OnKeyPressed(KeyPressedEvent& pEvent) {
		std::string keyCode = std::to_string(pEvent.mSymbol);
		std::string keySymbol(1, pEvent.mSymbol);
		LOG_INFO("Key pressed event emitted: [" + keyCode + "] " + keySymbol);
	}

	void Update() {

	}
};

#endif // !KEYBOARDCONTROLSYSTEM_ECHO2D_H
