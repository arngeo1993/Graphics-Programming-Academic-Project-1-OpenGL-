#pragma once

#include "Component.h"
#include "EventManager.h"
#include <stdio.h>
class GameObject;


//class PlayerHitEvent :public Event
//{
//public:
//	PlayerHitEvent();
//	~PlayerHitEvent() {}
//};
class Controller : public Component {
public:
	Controller();
	~Controller();

	void Update();
	//void HandleEvent(Event* pEvent);
	int size;
	//void Serialize(FILE** fpp);
};