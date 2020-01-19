#pragma once
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Obj_Name
{
	SHIP,
	ASTEROID,
	ENEMY_SHIP,
	BULLET,
	HOMING_MISSILE,
	ENEMY_SHIP_BULLET,
	ENEMY_SHIP_HOMING_MISSILE,
	BACKGROUND_1,
	MENU,
	MENU_ARROW,
	LEVEL,
	LEVEL_ARROW,
	GAME_OVER,
	Controls,

	num

};

class ObjectName : public Component {
public:
	ObjectName();
	~ObjectName();
	 void Serialize(FILE **fpp);
	 void Update();
	
public:
	Obj_Name mType_Name;


};
