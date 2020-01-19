#ifndef  RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include<string>
#include<unordered_map>

struct SDL_Surface;
class ResourceManager
{
public :
	ResourceManager();
	~ResourceManager();

	SDL_Surface *LoadSurfaces(const char* pFilePath);

private:
	std::unordered_map<std::string, SDL_Surface *> mSurfaces;

};






#endif // ! RESOURCE_MANAGER_H

