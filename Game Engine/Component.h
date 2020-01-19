#pragma once
#include <stdio.h>
enum COMPONENT_TYPE
{
	NAME,
	TRANSFORM,
	SPRITE,
	CONTROLLER,
	UPDOWN,
	BODY
};

class GameObject;
class Event;
class Component {
public:
	Component(unsigned int Type);
	virtual ~Component();

	virtual void Update() = 0; // abstract function
	unsigned int GetType() { return mType; }

	virtual void Serialize(FILE **fpp) {  }
	virtual void HandleEvent(Event * pEvent) {};

public:
	GameObject *mpOwner;

private:
	unsigned int mType;
};