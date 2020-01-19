#include "ResourceManager.h"
#include "SDL_surface.h"


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{

	for (auto &element : mSurfaces)
	{
		SDL_FreeSurface(element.second);
	}

	mSurfaces.clear();
	
}

SDL_Surface * ResourceManager::LoadSurfaces(const char * pFilePath)
{
	SDL_Surface *pSurface = mSurfaces[pFilePath];

	if (pSurface)
	{
		return pSurface;
	}

	pSurface = SDL_LoadBMP(pFilePath);\

		if (pSurface)
		{
			mSurfaces[pFilePath] = pSurface;
		}

	return pSurface;
}
