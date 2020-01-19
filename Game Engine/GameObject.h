#ifndef OBJECT_H
#define OBJECT_H

#include<vector>

class Component;

class Event;
class GameObject {
public:
	GameObject();
	~GameObject();

	void Update();
	Component* AddComponent(unsigned int Type);
	Component* GetComponent(unsigned int Type);

	void HandleEvent(Event * pEvent);

public:
	//Sprite *mpSprite;
	//Transform* mpTransform;
	//Controller* mpController;

	std::vector<Component*> mComponents;
};

#endif