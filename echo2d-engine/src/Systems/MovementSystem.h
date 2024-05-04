#ifndef MOVEMENTSYSTEM_ECHO2D_H
#define MOVEMENTSYSTEM_ECHO2D_H
#include "../Core/Core.h"

class MovementSystem : public System {
public:
	MovementSystem() {
		// TODO 
		// RequiredComponent<TransformComponent>();
		// RequiredComponent<...>();
	}
	~MovementSystem();
	void Update() {
		// TODO
		// Update entity position with you velocity
		// All logic to do frame by frame
	}
};

#endif // !MOVEMENTSYSTEM_ECHO2D_H
