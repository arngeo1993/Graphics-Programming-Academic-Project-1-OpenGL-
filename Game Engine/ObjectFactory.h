#pragma once
#include "Transform.h"
class GameObject;

class ObjectFactory
{
public :
	ObjectFactory();
	~ObjectFactory();

	void LoadLevel(const char* mfileName);
	GameObject *LoadObject(const char* mfileName);
};