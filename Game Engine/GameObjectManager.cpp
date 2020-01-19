#include "GameObjectManager.h"
#include<vector>

GameObjectManager::GameObjectManager()
{
	//mGameObjects.reserve(200000);

}

GameObjectManager::~GameObjectManager() {
	for (auto go : mGameObjects) {
		delete go;
		
		//go = nullptr;

	}
	//mGameObjects.swap(mGameObjects);
	
	//mGameObjects.clear();

	
	
}

void GameObjectManager::Clear_GameObjects()
{
	mGameObjects.clear();
}

