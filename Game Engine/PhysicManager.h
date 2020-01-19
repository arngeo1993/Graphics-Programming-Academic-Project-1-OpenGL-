#pragma once
#include "EventManager.h"
//#include "CollisionManager.h"

class ShipCollideEvent :public Event
{
public:
	ShipCollideEvent(): Event(SHIP_HIT) {}
	~ShipCollideEvent() {}
};
class BulletCollideEvent :public Event
{
public:
	BulletCollideEvent() : Event(BULLET_HIT) {}
	~BulletCollideEvent() {}
};
class HomingMissileCollideEvent :public Event
{
public:
	HomingMissileCollideEvent() : Event(HOMING_MISSILE_HIT) {}
	~HomingMissileCollideEvent() {}
};
class AsteroidCollideEvent :public Event
{
public:
	AsteroidCollideEvent() : Event(ASTEROID_HIT) {}
	~AsteroidCollideEvent() {}
};
class EnemyCollideEvent :public Event
{
public:
	EnemyCollideEvent() : Event(ENEMY_HIT) {}
	~EnemyCollideEvent() {}
};

class EnemyBulletCollideEvent :public Event
{
public:
	EnemyBulletCollideEvent() : Event(ENEMY_BULLET_HIT) {}
	~EnemyBulletCollideEvent() {}
};
class EnemyHomingMissileCollideEvent :public Event
{
public:
	EnemyHomingMissileCollideEvent() : Event(ENEMY_HOMING_MISSILE_HIT) {}
	~EnemyHomingMissileCollideEvent() {}
};




class PhysicManager
{
public:
	PhysicManager();
	~PhysicManager();

	void Update(float FrameTime);

};
