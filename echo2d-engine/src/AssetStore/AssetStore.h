#ifndef ASSETSTORE_ECHO2D_H
#define ASSETSTORE_ECHO2D_H
#include "../Core/Core.h"
class AssetStore
{
private:
	std::unordered_map<std::string, SDL_Texture*> mTexture;
	std::unordered_map<std::string, TTF_Font*> mFonts;
public:
	AssetStore();
	~AssetStore();

	void Clear();

	void AddFont(const std::string& pKeyAccess, const std::string& pFilePath, int pFontSize);
	TTF_Font* GetFont(const std::string& pKeyAccess);

	void AddTexture(SDL_Renderer* pRenderer, const std::string& pKeyAccess, const std::string& pFilePath);
	SDL_Texture* GetTexture(const std::string& pKeyAccess);
};

#endif // !ASSETSTORE_ECHO2D_H


