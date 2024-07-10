#ifndef RENDERTEXTSYSTEM_H
#define RENDERTEXTSYSTEM_H

#include "../Core/Core.h"
#include "../Components/TextComponent.h"

class RenderTextSystem : public System {
public:
	RenderTextSystem() {
		RequireComponent<TextComponent>();
	}

	void Update(SDL_Renderer* pRenderer, std::unique_ptr<AssetStore>& pAssetStore, SDL_Rect& pCamera) {
		TaskTime::start("RenderTextSystem");
		for (auto entity : GetSystemEntities()) {
			const auto textLabel = entity.GetComponent<TextComponent>();

			SDL_Surface* surface = TTF_RenderText_Blended(
				pAssetStore->GetFont(textLabel.mKeyAccess),
				textLabel.mText.c_str(),
				textLabel.mColor
			);

			SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
			SDL_FreeSurface(surface);

			int labelWidth = 0;
			int labelHeight = 0;

			SDL_QueryTexture(texture, NULL, NULL, &labelWidth, &labelHeight);

			SDL_Rect dstRect = {
				static_cast<int> (textLabel.mPosition.x - (textLabel.mIsFixed ? 0 : pCamera.x)),
				static_cast<int> (textLabel.mPosition.y - (textLabel.mIsFixed ? 0 : pCamera.y)),
				labelWidth,
				labelHeight
			};

			SDL_RenderCopy(pRenderer, texture, NULL, &dstRect);
			SDL_DestroyTexture(texture);
		}
		TaskTime::stop("RenderTextSystem");
	}
};


#endif // !RENDERTEXTSYSTEM_H

