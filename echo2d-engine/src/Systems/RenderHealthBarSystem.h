#ifndef RENDERHEALTHBARSYSTEM_ECHO2D_H
#define RENDERHEALTHBARSYSTEM_ECHO2D_H
#include "../Core/Core.h"
#include "../Components/SpriteComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../AssetStore/AssetStore.h"

class RenderHealthBarSystem : public System {
public:
	RenderHealthBarSystem() {
		RequireComponent<TransformComponent>();
		RequireComponent<SpriteComponent>();
		RequireComponent<HealthComponent>();
	}

	void Update(SDL_Renderer* pRenderer, std::unique_ptr<AssetStore>& pAssetStore, SDL_Rect& pCamera) {
		// Pr�-calcular a fonte uma vez para reutiliza��o
		TTF_Font* font = pAssetStore->GetFont("pico8-font-10");

		// Criar uma SDL_Surface tempor�ria para a renderiza��o do texto fora do loop
		SDL_Surface* surface = nullptr;
		// Criar uma SDL_Texture tempor�ria para a renderiza��o do texto fora do loop
		SDL_Texture* texture = nullptr;

		for (auto entity : GetSystemEntities()) {

			const auto transform = entity.GetComponent<TransformComponent>();
			const auto sprite = entity.GetComponent<SpriteComponent>();
			const auto health = entity.GetComponent<HealthComponent>();

			SDL_Color currentColor = GetHealthColor(health.healthPercentage);

			int rectPositionX = transform.position.x - pCamera.x;
			int rectPositionY = transform.position.y - 7 - pCamera.y;
			int rectWidth = sprite.srcRect.w * transform.scale.x;
			int rectHeight = 5;

			SDL_Rect rect = {
				rectPositionX,
				rectPositionY,
				rectWidth * (health.healthPercentage / 100.0),
				rectHeight
			};

			SDL_SetRenderDrawColor(pRenderer, currentColor.r, currentColor.g, currentColor.b, currentColor.a);
			SDL_RenderFillRect(pRenderer, &rect);

			std::string healthText = std::to_string(health.healthPercentage);

			surface = TTF_RenderText_Blended(font, healthText.c_str(), currentColor);
			texture = SDL_CreateTextureFromSurface(pRenderer, surface);


			int labelWidth = 0;
			int labelHeight = 0;

			SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

			SDL_Rect dstRect = {
				rectPositionX,
				rectPositionY - 14,
				labelWidth,
				labelHeight
			};

			SDL_RenderCopy(pRenderer, texture, NULL, &dstRect);

		}
		if (surface)
			SDL_FreeSurface(surface);
		if (texture)
			SDL_DestroyTexture(texture);
	}
private:



	SDL_Color GetHealthColor(int healthPercentage) {
		if (healthPercentage > 70) {
			return SDL_COLOR_GREEN; // Verde
		}
		else if (healthPercentage > 30) {
			return SDL_COLOR_YELLOW; // Amarelo
		}
		else {
			return SDL_COLOR_RED; // Vermelho
		}
	}
};

#endif