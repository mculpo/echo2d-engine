#ifndef ASSETSTORE_ECHO2D_H
#define ASSETSTORE_ECHO2D_H
#include "../Core/Core.h"
class AssetStore
{
private:
	std::unordered_map<std::string, SDL_Texture*> mTexture;
public:
	AssetStore();
	~AssetStore();

	void Clear();
	void AddTexture(SDL_Renderer* pRenderer, const std::string& pKeyAccess, const std::string& pFilePath);
	SDL_Texture* GetTexture(const std::string& pKeyAccess);
};

#endif // !ASSETSTORE_ECHO2D_H


