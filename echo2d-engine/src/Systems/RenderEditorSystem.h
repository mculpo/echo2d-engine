#ifdef _DEBUG
#ifndef RENDEREDITORSYSTEM_H
#define RENDEREDITORSYSTEM_H

#include "../Core/Core.h"
#include "../AssetStore/AssetStore.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/ProjectileEmmiterComponent.h"

class RenderEditorSystem : public System {
public:
	RenderEditorSystem() {
		lastUpdateTime = SDL_GetTicks();
	};
	void Update(SDL_Renderer* pRenderer, std::unique_ptr<AssetStore>& pAssetStore, SDL_Rect& pCamera, std::unique_ptr<Registry>& pRegistry) {
		ImGui_ImplSDLRenderer2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		//// Display a window to customize and create new enemies
		//if (ImGui::Begin("Spawn enemies")) {
		//    // Static variables to hold input values
		//    static int posX = 0;
		//    static int posY = 0;
		//    static int scaleX = 1;
		//    static int scaleY = 1;
		//    static int velX = 0;
		//    static int velY = 0;
		//    static int health = 100;
		//    static float rotation = 0.0;
		//    static float projAngle = 0.0;
		//    static float projSpeed = 100.0;
		//    static int projRepeat = 10;
		//    static int projDuration = 10;
		//    const char* sprites[] = { "tank-image", "truck-image" };
		//    static int selectedSpriteIndex = 0;

		//    // Section to input enemy sprite texture id 
		//    if (ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_DefaultOpen)) {
		//        ImGui::Combo("texture id", &selectedSpriteIndex, sprites, IM_ARRAYSIZE(sprites));
		//    }
		//    ImGui::Spacing();

		//    // Section to input enemy transform values
		//    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {
		//        ImGui::InputInt("position x", &posX);
		//        ImGui::InputInt("position y", &posY);
		//        ImGui::SliderInt("scale x", &scaleX, 1, 10);
		//        ImGui::SliderInt("scale y", &scaleY, 1, 10);
		//        ImGui::SliderAngle("rotation (deg)", &rotation, 0, 360);
		//    }
		//    ImGui::Spacing();

		//    // Section to input enemy rigid body values
		//    if (ImGui::CollapsingHeader("Rigid body", ImGuiTreeNodeFlags_DefaultOpen)) {
		//        ImGui::InputInt("velocity x", &velX);
		//        ImGui::InputInt("velocity y", &velY);
		//    }
		//    ImGui::Spacing();

		//    // Section to input enemy projectile emitter values
		//    if (ImGui::CollapsingHeader("Projectile emitter", ImGuiTreeNodeFlags_DefaultOpen)) {
		//        ImGui::SliderAngle("angle (deg)", &projAngle, 0, 360);
		//        ImGui::SliderFloat("speed (px/sec)", &projSpeed, 10, 500);
		//        ImGui::InputInt("repeat (sec)", &projRepeat);
		//        ImGui::InputInt("duration (sec)", &projDuration);
		//    }
		//    ImGui::Spacing();

		//    // Section to input enemy health values
		//    if (ImGui::CollapsingHeader("Health", ImGuiTreeNodeFlags_DefaultOpen)) {
		//        ImGui::SliderInt("%", &health, 0, 100);
		//    }

		//    ImGui::Spacing();
		//    ImGui::Separator();
		//    ImGui::Spacing();

		//    // Enemy creation button
		//    if (ImGui::Button("Spawn new enemy")) {
		//        Entity enemy = pRegistry->CreateEntity();
		//        enemy.Group("enemies");
		//        enemy.AddComponent<TransformComponent>(glm::vec2(posX, posY), glm::vec2(scaleX, scaleY), glm::degrees(rotation));
		//        enemy.AddComponent<RigidBodyComponent>(glm::vec2(velX, velY));
		//        enemy.AddComponent<SpriteComponent>(sprites[selectedSpriteIndex], 32, 32, 2);
		//        enemy.AddComponent<BoxColliderComponent>(32, 32, VEC2_ZERO);
		//        double projVelX = cos(projAngle) * projSpeed; // convert from angle-speed to x-value
		//        double projVelY = sin(projAngle) * projSpeed; // convert from angle-speed to y-value
		//        enemy.AddComponent<ProjectileEmmiterComponent>(glm::vec2(projVelX, projVelY), projRepeat * 1000, projDuration * 1000, 10, false);
		//        enemy.AddComponent<HealthComponent>(health);

		//        // Reset all input values after we create a new enemy
		//        posX = posY = rotation = projAngle = 0;
		//        scaleX = scaleY = 1;
		//        projRepeat = projDuration = 10;
		//        projSpeed = 100;
		//        health = 100;
		//    }
		//}

		//ImGui::End();
		Uint32 currentTime = SDL_GetTicks();
		if (ImGui::Begin("Profile Systems")) {
			static std::map<std::string, float> allDurations;

			if (currentTime - lastUpdateTime >= 200) {
				lastUpdateTime = currentTime;
				allDurations = TaskTime::getAllDurations();
			}

			// Iterando sobre o mapa e imprimindo os valores
			for (const auto& pair : allDurations) {
				// Exibindo o nome da tarefa e a duração formatada
				ImGui::Text("%s   %.2f fps   %.1f ms", pair.first.c_str(), pair.second == 0 ? 0 : 1000 / pair.second, pair.second);
				ImGui::Separator();
			}

		}
		ImGui::End();

		// Display a small overlay window to display the map position using the mouse
		/*ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoNav;
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Always, ImVec2(0, 0));
		ImGui::SetNextWindowBgAlpha(0.9f);
		if (ImGui::Begin("Map coordinates", NULL, windowFlags)) {
			ImGui::Text(
				"Map coordinates (x=%.1f, y=%.1f)",
				ImGui::GetIO().MousePos.x + pCamera.x,
				ImGui::GetIO().MousePos.y + pCamera.y
			);
		}
		ImGui::End();*/

		ImGui::Render();
		ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), pRenderer);
	}
private:
	Uint32 lastUpdateTime;
};

#endif
#endif