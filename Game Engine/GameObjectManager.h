#pragma once
#include<vector>
class GameObject;

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();
	void Clear_GameObjects();

public:
	std::vector<GameObject*> mGameObjects, new_GameObjects, delete_GameObjects;
};