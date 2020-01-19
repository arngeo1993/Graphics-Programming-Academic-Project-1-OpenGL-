#include "ObjectName.h"
#include <stdio.h>
#include <string>
#include "EventManager.h"
#include "Body.h"
#include "GameObjectManager.h"
#include "GameObject.h"
extern EventManager *gpEventManager;
extern GameObjectManager* gpGoManager;

extern float SCR_WIDTH;
extern float SCR_HEIGHT;
ObjectName::ObjectName() : Component(NAME)
{
	
}

ObjectName::~ObjectName()
{
}

void ObjectName::Serialize(FILE ** fpp)
{
	char object_Name[256] = { 0 };

	fscanf_s(*fpp, "%255s\n", object_Name, sizeof(object_Name));

	std::string stringObjecttName = object_Name;

	if (stringObjecttName == "Ship")
	{
		
		mType_Name = SHIP;
		gpEventManager->Subscribe(SHIP_HIT, this->mpOwner);
	}
	else if (stringObjecttName == "Asteroid")
	{
		
		mType_Name = ASTEROID;
		gpEventManager->Subscribe(ASTEROID_HIT, this->mpOwner);
	}
	else if (stringObjecttName == "EnemyShip")
	{
		
		mType_Name = ENEMY_SHIP;
		gpEventManager->Subscribe(ENEMY_HIT, this->mpOwner);
	}
	else if (stringObjecttName == "EnemyShipBullet")
	{

		mType_Name = ENEMY_SHIP_BULLET;

		gpEventManager->Subscribe(ENEMY_BULLET_HIT, this->mpOwner);
	}
	else if (stringObjecttName == "EnemyShipHomingMissile")
	{

		mType_Name = ENEMY_SHIP_HOMING_MISSILE;
		gpEventManager->Subscribe(ENEMY_HOMING_MISSILE_HIT, this->mpOwner);
	}
	else if (stringObjecttName == "Bullet")
	{
		
		mType_Name = BULLET;
		gpEventManager->Subscribe(BULLET_HIT, this->mpOwner);
	}
	else if (stringObjecttName == "HomingMissile")
	{
		
		mType_Name = HOMING_MISSILE;

		gpEventManager->Subscribe(HOMING_MISSILE_HIT, this->mpOwner);
	}
	else if (stringObjecttName == "Background1")
	{

		mType_Name = BACKGROUND_1;
		
	}
	else if (stringObjecttName == "Menu")
	{

		mType_Name = MENU;

	}
	else if (stringObjecttName == "GameOver")
	{

		mType_Name = GAME_OVER;

	}
	else if (stringObjecttName == "Controls")
	{

		mType_Name = Controls;

	}
	else if (stringObjecttName == "MenuArrow")
	{

		mType_Name = MENU_ARROW;

	}
	else if (stringObjecttName == "Levelimg")
	{

		mType_Name = LEVEL;

	}
	else if (stringObjecttName == "LevelArrow")
	{
		
		mType_Name = LEVEL_ARROW;

	}
	else
	{
		printf("Name Error\n");
	}

}

void ObjectName::Update()
{
}
