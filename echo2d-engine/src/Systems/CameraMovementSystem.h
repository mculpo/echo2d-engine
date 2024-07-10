#ifndef CAMERAMOVEMENTSYSTEM_ECHO2D_H
#define CAMERAMOVEMENTSYSTEM_ECHO2D_H

#include "../Core/Core.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"

class CameraMovementSystem: public System
{
public:
	CameraMovementSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<CameraFollowComponent>();
	}
	~CameraMovementSystem() {}
	void Update(SDL_Rect& pCamera) {
		for (auto entity : GetSystemEntities()) {
			auto transform = entity.GetComponent<TransformComponent>();
			if (transform.position.x + (pCamera.w / 2) < EchoGame::mapWidth) {
				pCamera.x = transform.position.x - (EchoGame::logicalWindowWidth / 2);
			}
			if (transform.position.y + (pCamera.h / 2) < EchoGame::mapHeight) {
				pCamera.y = transform.position.y - (EchoGame::logicalWindowHeight / 2);
			}

			pCamera.x = pCamera.x < 0 ? 0 : pCamera.x;
			pCamera.y = pCamera.y < 0 ? 0 : pCamera.y;
			pCamera.x = pCamera.x > pCamera.w ? pCamera.w : pCamera.x;
			pCamera.y = pCamera.y > pCamera.h ? pCamera.h : pCamera.y;
		}
	}

};


#endif // !CAMERAMOVEMENTSYSTEM_ECHO2D_H

