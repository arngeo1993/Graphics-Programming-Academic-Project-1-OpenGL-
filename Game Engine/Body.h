#pragma once
#include "Component.h"
#include "CollisionManager.h"
#include <stdio.h>
#include "Vector2D.h"
#include "EventManager.h"
class Shape;
class GameObject;
class Body :public Component
{



public:
	Vector2D mPos;
	Vector2D mPrevPos;
	Vector2D mVel;
	Vector2D mAcc;
	Vector2D mTotalForce;
	
		float mMass, mInvMass;
		float mAngle;

		Shape* mpShape;
		GameObject* Homing_Missile_Target;
		int homing_missile_Target_active;

		GameObject* Enemy_To_Player_Target;
		int enemy_Target_active;

		int enemyShoot;
		GameObject* Enemy_Homing_Missile_Target;
		int Enemy_homing_missile_Target_active;
		int Enemy_Homing_Missile_Count;
		int Enemy_Bullet_Count;
		int prev_enemyShoot;

		int collide_Type;

		int body_shape_type;

		


public:
	Body();
	~Body();
	void Update();
	void Serialize(FILE **fpp);

	void Initialize();
	void Integrate(float Gravity, float DeltaTime);
	void HandleEvent(Event *pEvent);
};