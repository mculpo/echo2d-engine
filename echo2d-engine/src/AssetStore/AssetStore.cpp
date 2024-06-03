#include "AssetStore.h"

AssetStore::AssetStore()
{
	LOG_INFO("AssetStore created!");
}

AssetStore::~AssetStore()
{
	LOG_INFO("AssetStore removed!");
}

void AssetStore::Clear()
{
	for (auto texture : mTexture) {
		SDL_DestroyTexture(texture.second);
	}

	for (auto font : mFonts) {
		TTF_CloseFont(font.second);
	}

	mTexture.clear();
	mFonts.clear();
}

void AssetStore::AddFont(const std::string& pKeyAccess, const std::string& pFilePath, int pFontSize)
{
	mFonts.emplace(pKeyAccess, TTF_OpenFont(pFilePath.c_str(), pFontSize));
}

TTF_Font* AssetStore::GetFont(const std::string& pKeyAccess)
{
	return mFonts[pKeyAccess];
}

void AssetStore::AddTexture(SDL_Renderer* pRenderer, const std::string& pKeyAccess, const std::string& pFilePath)
{
	SDL_Surface* surface = IMG_Load(pFilePath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);

	mTexture.emplace(pKeyAccess, texture);
}

SDL_Texture* AssetStore::GetTexture(const std::string& pKeyAccess) 
{
	return mTexture[pKeyAccess];
}
