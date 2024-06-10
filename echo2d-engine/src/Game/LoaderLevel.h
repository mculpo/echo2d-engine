#ifndef LOADLEVEL_H
#define LOADLEVEL_H
#include "../Core/Core.h"
#include "../AssetStore/AssetStore.h"
class LoaderLevel
{	
public:
	LoaderLevel();
	~LoaderLevel();
	void LoadLevel(
		sol::state& pLua,
		std::unique_ptr<Registry>& pRegister, 
		std::unique_ptr<AssetStore>& pAssetStore, 
		SDL_Renderer* pRenderer, 
		unsigned int pLevel);
private:
	unsigned int mCurrentLevel;
};

#endif

