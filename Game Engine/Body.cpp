#include "Body.h"
#include "Transform.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include <iostream>
#include "ObjectName.h"
#include <iostream> 
#include <algorithm> 
#include "GameObjectManager.h"
#include <time.h>
#include <stdlib.h> 
#include "ObjectFactory.h"
#include "EventManager.h"
#include "StateManager.h"
#include "EventManager.h"

extern float SCR_WIDTH ;
extern float SCR_HEIGHT;
#define BULLET_SPEED								1000.0f
#define ENEMY_BULLET_SPEED							700.0f
#define HOMING_BULLET_SPEED							150.0f
#define ENEMY_SPEED_LEVEL_1							70.0f
#define ENEMY_SPEED_LEVEL_2							100.0f
#define ENEMY_SPEED_LEVEL_3							120.0f
#define ENEMY_SPEED_LEVEL_4							140.0f
#define ENEMY_HOMING_BULLET_SPEED_LEVEL_1			100.0f
#define ENEMY_HOMING_BULLET_SPEED_LEVEL_2			120.0f
#define ENEMY_HOMING_BULLET_SPEED_LEVEL_3			140.0f
#define ENEMY_HOMING_BULLET_SPEED_LEVEL_4			160.0f

extern EventManager *gpEventManager;
extern ObjectFactory* gpObjectFactory;
extern GameObjectManager* gpGoManager;
extern StateManager *gpStateManager;
Body::Body(): Component(BODY)
{
	
	Vector2DSet(&mPos, 0, 0);
	Vector2DSet(&mPrevPos, 0, 0);
	Vector2DSet(&mVel, 0, 0);
	Vector2DSet(&mAcc, 0, 0);
	Vector2DSet(&mTotalForce, 0, 0);
	
	mAngle = 0;

	mpShape = nullptr;

	 Homing_Missile_Target = nullptr;
	 homing_missile_Target_active = 0;
	 enemy_Target_active = 0;
	 Enemy_To_Player_Target = nullptr;
	 Enemy_Homing_Missile_Target = nullptr;
	 Enemy_homing_missile_Target_active = 0;
	 Enemy_Homing_Missile_Count = 0;
	 Enemy_Bullet_Count = 0;

	 enemyShoot = 0;
	 prev_enemyShoot = 0;
	 collide_Type = 0;

	 body_shape_type = 2;
}


float normalised(const float value, const float start, const float end)
{
	const float width = end - start;   // 
	const float offsetValue = value - start;   // value relative to 0

	return (offsetValue - (floor(offsetValue / width) * width)) + start;
	// + start to reset back to start of original range
}



Body::~Body()
{
}

void Body::Update()
{
	
}

void Body::Serialize(FILE ** fpp)
{
	fscanf_s(*fpp, "%f\n", &mMass);
	fscanf_s(*fpp, "%f %f\n", &mVel.x,&mVel.y);

	if (0.0f != mMass)
	{
		mInvMass = 1.0f / mMass;
	}
	else
	{
		mInvMass = 0.0;
	}

	char shapeType[256] = { 0 };
	fscanf_s(*fpp, "%255s\n", shapeType, sizeof(shapeType));

	if (0 == strcmp(shapeType, "Circle"))
	{
		
		mpShape = new ShapeCircle();
		mpShape->mpOwnerBody = this;
		ShapeCircle *pCircle = static_cast<ShapeCircle *>(mpShape);
		fscanf_s(*fpp, "%f\n", &pCircle->mRadius);
		body_shape_type = 0;
		
	}
	else if (0 == strcmp(shapeType, "AABB"))
	{
		mpShape = new ShapeAABB();
		mpShape->mpOwnerBody = this;
		ShapeAABB *pAABB = static_cast<ShapeAABB *>(mpShape);
		fscanf_s(*fpp, "%f %f %f %f\n", &pAABB->mLeft, &pAABB->mTop, &pAABB->mRight, &pAABB->mBottom);
		body_shape_type = 1;
	}


}

void Body::Initialize()
{
	Transform *ptr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));

	if (nullptr	!= ptr)
	{
		Vector2DSet(&mPos, ptr->mPosX, ptr->mPosY);
		Vector2DSet(&mPrevPos, ptr->mPosX, ptr->mPosY);
		/*mPrevPosX = mPosX = ptr-> mPosX;
		mPrevPosY = mPosY = ptr->mPosY;*/

	}
}

void Body::Integrate(float Gravity, float DeltaTime)
{
	ObjectName* pObj_Name = static_cast<ObjectName *>(mpOwner->GetComponent(NAME));
	
	
	if (pObj_Name->mType_Name == SHIP)
	{
		Vector2D newVel;
		Vector2DScaleAdd(&newVel,&mAcc,&mVel,DeltaTime);


		mVel = newVel;
		Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
		
		
		mVel.x *= 0.99;
		mVel.y *= 0.99;
		
		mPos.x = normalised(mPos.x, 0, SCR_WIDTH);
		mPos.y = normalised(mPos.y, 0, SCR_HEIGHT);

		Vector2DSet(&mAcc, 0, 0);
	}
	else if (pObj_Name->mType_Name == BULLET)
	{
		
		Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
		

		
		
	}
	else if (pObj_Name->mType_Name == ENEMY_SHIP_BULLET)
	{

		Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);




	}
	else if (pObj_Name->mType_Name == HOMING_MISSILE)
	{
		if (Homing_Missile_Target == nullptr)
		{
			
			homing_missile_Target_active = 0;
		}

		if (homing_missile_Target_active == 0)
		{
			std::vector<GameObject*>::iterator it = gpGoManager->mGameObjects.begin();
			int size = gpGoManager->mGameObjects.size();
			for (int i = 0; i<size; ++i)
			{
				auto go = gpGoManager->mGameObjects[i];
				if (go == nullptr)
				{
					continue;
				}
				ObjectName* pObj_Target = static_cast<ObjectName *>(go->GetComponent(NAME));
				if (pObj_Target == nullptr)
					continue;
				if (pObj_Target->mType_Name == ASTEROID)
				{
					
					Homing_Missile_Target = go;
					homing_missile_Target_active = 1;
					break;
				}
				else if(pObj_Target->mType_Name == ENEMY_SHIP)
				{
					Homing_Missile_Target = go;
					homing_missile_Target_active = 1;
					break;
				}
			}
		}
		else
		{
			
			Vector2D norm_Target_Vel, norm_HomMis_Vel, missile_To_Target, rot_90_HomMis_Vel;


			float  desicion_Angle;

			Body* pBody_Homing_Missile_Target = static_cast<Body *>(Homing_Missile_Target->GetComponent(BODY));
			if (pBody_Homing_Missile_Target != nullptr)
			{
				Vector2DSub(&missile_To_Target, &pBody_Homing_Missile_Target->mPos, &mPos);


				Vector2DNormalize(&norm_Target_Vel, &missile_To_Target);

				Vector2DSet(&rot_90_HomMis_Vel, -mVel.y, mVel.x);

				Vector2DNormalize(&norm_HomMis_Vel, &rot_90_HomMis_Vel);

				desicion_Angle = Vector2DDotProduct(&norm_HomMis_Vel, &norm_Target_Vel);


				if (desicion_Angle > 0)
				{

					mAngle += 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * 100, sinf(mAngle) * 100);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);

				}
				else if (desicion_Angle < 0)
				{

					mAngle -= 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * 100, sinf(mAngle) * 100);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);

				}
			}
			else
			{
				gpEventManager->UnSubcribe(HOMING_MISSILE_HIT, this->mpOwner);
				mpOwner->~GameObject();
			}
			
			
		}
		


		

	}
	else if (pObj_Name->mType_Name == ASTEROID)
	{

		mPos.x = normalised(mPos.x, 0, SCR_WIDTH);
		mPos.y = normalised(mPos.y, 0, SCR_HEIGHT);
		Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);

	
	}
	else if (pObj_Name->mType_Name == ENEMY_SHIP)
	{
		if (Enemy_To_Player_Target == nullptr)
		{

			enemy_Target_active = 0;
		}

		if (enemy_Target_active == 0)
		{
			std::vector<GameObject*>::iterator it = gpGoManager->mGameObjects.begin();
			int size = gpGoManager->mGameObjects.size();
			for (int i = 0; i<size; ++i)
			{
				auto go = gpGoManager->mGameObjects[i];
				if (go == nullptr)
				{
					continue;
				}
				ObjectName* pObj_Target = static_cast<ObjectName *>(go->GetComponent(NAME));
				if (pObj_Target == nullptr)
					continue;
				if (pObj_Target->mType_Name == SHIP)
				{

					Enemy_To_Player_Target = go;
					enemy_Target_active = 1;
					break;
				}
			}
		}
		else
		{

			Vector2D norm_Target_Vel, norm_HomMis_Vel, missile_To_Target, rot_90_HomMis_Vel;


			float  desicion_Angle;

			Body* pBody_Homing_Missile_Target = static_cast<Body *>(Enemy_To_Player_Target->GetComponent(BODY));

			Vector2DSub(&missile_To_Target, &pBody_Homing_Missile_Target->mPos, &mPos);


			Vector2DNormalize(&norm_Target_Vel, &missile_To_Target);

			Vector2DSet(&rot_90_HomMis_Vel, -mVel.y, mVel.x);

			Vector2DNormalize(&norm_HomMis_Vel, &rot_90_HomMis_Vel);

			desicion_Angle = Vector2DDotProduct(&norm_HomMis_Vel, &norm_Target_Vel);


			if (desicion_Angle > 0)
			{
				if (gpStateManager->state_tracker == 3)
				{
					mAngle += 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_1, sinf(mAngle) * ENEMY_SPEED_LEVEL_1);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}
				else if (gpStateManager->state_tracker == 4)
				{
					mAngle += 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_2, sinf(mAngle) * ENEMY_SPEED_LEVEL_2);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}
				else if (gpStateManager->state_tracker == 5)
				{
					mAngle += 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_3, sinf(mAngle) * ENEMY_SPEED_LEVEL_3);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}
				else if (gpStateManager->state_tracker == 6)
				{
					mAngle += 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_4, sinf(mAngle) * ENEMY_SPEED_LEVEL_4);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}
				

			}
			else if (desicion_Angle < 0)
			{

				if (gpStateManager->state_tracker == 3)
				{
					mAngle -= 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_1, sinf(mAngle) * ENEMY_SPEED_LEVEL_1);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}
				else if (gpStateManager->state_tracker == 4)
				{
					mAngle -= 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_2, sinf(mAngle) * ENEMY_SPEED_LEVEL_2);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}
				else if (gpStateManager->state_tracker == 5)
				{
					mAngle -= 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_3, sinf(mAngle) * ENEMY_SPEED_LEVEL_3);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}
				else if (gpStateManager->state_tracker == 6)
				{
					mAngle -= 0.05f;
					Vector2DSet(&mVel, cosf(mAngle) * ENEMY_SPEED_LEVEL_4, sinf(mAngle) * ENEMY_SPEED_LEVEL_4);
					Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
				}

			}
			srand(time(NULL));
			enemyShoot = (rand() % (100 - 1 + 1)) + 1;
			
			if (enemyShoot % 5 == 0)
			{
				if (Enemy_Bullet_Count < 1)
				{
					GameObject *pGO_Bullet = gpObjectFactory->LoadObject("Enemy_Ship_Bullet.txt");
					Body* pBody_Bullet = static_cast<Body *>(pGO_Bullet->GetComponent(BODY));
					if (nullptr != pBody_Bullet)
					{
						
						Vector2DSet(&pBody_Bullet->mPos, mPos.x, mPos.y);
						Vector2DSet(&pBody_Bullet->mVel, cosf(mAngle)*ENEMY_BULLET_SPEED, sinf(mAngle)*ENEMY_BULLET_SPEED);
						gpGoManager->new_GameObjects.resize(gpGoManager->new_GameObjects.size() + 1);
						gpGoManager->new_GameObjects[gpGoManager->new_GameObjects.size() - 1] = pGO_Bullet;
					}
					Enemy_Bullet_Count += 1;
				}
				
				prev_enemyShoot = enemyShoot;
			}
			if (enemyShoot % 20 == 0)
			{
				if(Enemy_Homing_Missile_Count !=enemyShoot)
				{
					GameObject *pGO_Bullet = gpObjectFactory->LoadObject("EnemyHomingMissile.txt");
					Body* pBody_Bullet = static_cast<Body *>(pGO_Bullet->GetComponent(BODY));
					if (nullptr != pBody_Bullet)
					{
						

						if (gpStateManager->state_tracker == 3)
						{
							
							Vector2DSet(&pBody_Bullet->mPos, mPos.x, mPos.y);
							Vector2DSet(&pBody_Bullet->mVel, cosf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_1, sinf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_1);
							gpGoManager->new_GameObjects.resize(gpGoManager->new_GameObjects.size() + 1);
							gpGoManager->new_GameObjects[gpGoManager->new_GameObjects.size() - 1] = pGO_Bullet;
						}
						else if (gpStateManager->state_tracker == 4)
						{
							Vector2DSet(&pBody_Bullet->mPos, mPos.x, mPos.y);
							Vector2DSet(&pBody_Bullet->mVel, cosf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_2, sinf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_2);
							gpGoManager->new_GameObjects.resize(gpGoManager->new_GameObjects.size() + 1);
							gpGoManager->new_GameObjects[gpGoManager->new_GameObjects.size() - 1] = pGO_Bullet;
						}
						else if (gpStateManager->state_tracker == 5)
						{
							Vector2DSet(&pBody_Bullet->mPos, mPos.x, mPos.y);
							Vector2DSet(&pBody_Bullet->mVel, cosf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_3, sinf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_3);
							gpGoManager->new_GameObjects.resize(gpGoManager->new_GameObjects.size() + 1);
							gpGoManager->new_GameObjects[gpGoManager->new_GameObjects.size() - 1] = pGO_Bullet;
						}
						else if (gpStateManager->state_tracker == 6)
						{
							Vector2DSet(&pBody_Bullet->mPos, mPos.x, mPos.y);
							Vector2DSet(&pBody_Bullet->mVel, cosf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_4, sinf(mAngle)*ENEMY_HOMING_BULLET_SPEED_LEVEL_4);
							gpGoManager->new_GameObjects.resize(gpGoManager->new_GameObjects.size() + 1);
							gpGoManager->new_GameObjects[gpGoManager->new_GameObjects.size() - 1] = pGO_Bullet;
						}
					}
					Enemy_Homing_Missile_Count = enemyShoot;
				}
				
			}
			if (prev_enemyShoot != enemyShoot)
			{
				Enemy_Bullet_Count =0;
			}

		}
	
	}
	else if (pObj_Name->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
	{
		if (Enemy_Homing_Missile_Target == nullptr)
		{

			Enemy_homing_missile_Target_active = 0;
		}

		if (Enemy_homing_missile_Target_active == 0)
		{
			std::vector<GameObject*>::iterator it = gpGoManager->mGameObjects.begin();
			int size = gpGoManager->mGameObjects.size();
			for (int i = 0; i<size; ++i)
			{
				auto go = gpGoManager->mGameObjects[i];
				if (go == nullptr)
				{
					continue;
				}
				ObjectName* pObj_Target = static_cast<ObjectName *>(go->GetComponent(NAME));
				if (pObj_Target == nullptr)
					continue;
				if (pObj_Target->mType_Name == SHIP)
				{

					Enemy_Homing_Missile_Target = go;
					Enemy_homing_missile_Target_active = 1;
					break;
				}
			}
		}
		else
		{

			Vector2D norm_Target_Vel, norm_HomMis_Vel, missile_To_Target, rot_90_HomMis_Vel;


			float  desicion_Angle;

			Body* pBody_Homing_Missile_Target = static_cast<Body *>(Enemy_Homing_Missile_Target->GetComponent(BODY));

			Vector2DSub(&missile_To_Target, &pBody_Homing_Missile_Target->mPos, &mPos);


			Vector2DNormalize(&norm_Target_Vel, &missile_To_Target);

			Vector2DSet(&rot_90_HomMis_Vel, -mVel.y, mVel.x);

			Vector2DNormalize(&norm_HomMis_Vel, &rot_90_HomMis_Vel);

			desicion_Angle = Vector2DDotProduct(&norm_HomMis_Vel, &norm_Target_Vel);


			if (desicion_Angle > 0)
			{

				mAngle += 0.05f;
				Vector2DSet(&mVel, cosf(mAngle) * 100, sinf(mAngle) * 100);
				Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);

			}
			else if (desicion_Angle < 0)
			{

				mAngle -= 0.05f;
				Vector2DSet(&mVel, cosf(mAngle) * 100, sinf(mAngle) * 100);
				Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);

			}

		}





	}
	else if (pObj_Name->mType_Name == BACKGROUND_1)
	{
	
		Transform *ptr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));
		ptr->mScaleX =SCR_WIDTH;
		ptr->mScaleY = SCR_HEIGHT;
		Body *Ship_Body =nullptr;
		/*for (auto go : gpGoManager->mGameObjects)
		{
			ObjectName* pObj_Name = static_cast<ObjectName *>(go->GetComponent(NAME));
			if (pObj_Name == nullptr)
				continue;
			if (pObj_Name->mType_Name == SHIP)
			{
				Ship_Body = static_cast<Body *>(go->GetComponent(BODY));
			}

		}*/
		
		
	
		Vector2DScaleAdd(&mPos, &mVel, &mPos, DeltaTime);
	}
	

	Transform *ptr = static_cast<Transform *>(mpOwner->GetComponent(TRANSFORM));


	
	if (nullptr != ptr)
	{
		ptr->mPosX = mPos.x ;
		ptr->mPosY = mPos.y ;
		ptr->mAngle = mAngle;
		
	}
}

void Body::HandleEvent(Event * pEvent)
{
	
	if (SHIP_HIT == pEvent->mType)
	{
		
		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		if (nullptr != pBody)
		{
			if (pBody->collide_Type == 2)
			{
				pBody->mPos.x = 910.0;
				pBody->mPos.y = 490.0;
				pBody->mVel.x = 0;
				pBody->mVel.y = 0;
				gpStateManager->shipLives -= 1;
			}
			
			
		}
	}
	if (ASTEROID_HIT == pEvent->mType)
	{
		
		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		if (nullptr != pBody)
		{
			
			if (pBody->collide_Type == 2)
			{
				gpEventManager->UnSubcribe(ASTEROID_HIT, this->mpOwner);
			
				
				
				gpGoManager->delete_GameObjects.resize(gpGoManager->delete_GameObjects.size() + 1);
				gpGoManager->delete_GameObjects[gpGoManager->delete_GameObjects.size() - 1] = mpOwner;
			
				
			}
			else if (pBody->collide_Type == 1)
			{
				pBody->mVel.x = -pBody->mVel.x-50;
				pBody->mVel.y = -pBody->mVel.y-50;
				gpEventManager->UnSubcribe(ASTEROID_HIT, this->mpOwner);

			}
			
			
		}
	}
	if (ENEMY_HIT == pEvent->mType)
	{
		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		if (nullptr != pBody)
		{


			if (pBody->collide_Type == 2)
			{
				
				gpEventManager->UnSubcribe(ENEMY_HIT, this->mpOwner);
				gpGoManager->delete_GameObjects.resize(gpGoManager->delete_GameObjects.size() + 1);
				gpGoManager->delete_GameObjects[gpGoManager->delete_GameObjects.size() - 1] = mpOwner;
				
			}

			
		}
		
		
		
		
	}
	 if (ENEMY_BULLET_HIT == pEvent->mType)
	{
		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		if (nullptr != pBody)
		{


			if (pBody->collide_Type == 2)
			{
				gpEventManager->UnSubcribe(ENEMY_BULLET_HIT, this->mpOwner);
				gpGoManager->delete_GameObjects.resize(gpGoManager->delete_GameObjects.size() + 1);
				gpGoManager->delete_GameObjects[gpGoManager->delete_GameObjects.size() - 1] = mpOwner;
			}
		}
	}
	 if (ENEMY_HOMING_MISSILE_HIT == pEvent->mType)
	{
		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		if (nullptr != pBody)
		{


			if (pBody->collide_Type == 2)
			{
				gpEventManager->UnSubcribe(ENEMY_HOMING_MISSILE_HIT, this->mpOwner);
				gpGoManager->delete_GameObjects.resize(gpGoManager->delete_GameObjects.size() + 1);
				gpGoManager->delete_GameObjects[gpGoManager->delete_GameObjects.size() - 1] = mpOwner;
			}
		}
	}
	 if (BULLET_HIT == pEvent->mType)
	{
		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		if (nullptr != pBody)
		{


			if (pBody->collide_Type == 2)
			{
				gpEventManager->UnSubcribe(BULLET_HIT, this->mpOwner);
				gpGoManager->delete_GameObjects.resize(gpGoManager->delete_GameObjects.size() + 1);
				gpGoManager->delete_GameObjects[gpGoManager->delete_GameObjects.size() - 1] = mpOwner;
			}
		}
	}
	 if (HOMING_MISSILE_HIT == pEvent->mType)
	{
	
		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
		if (nullptr != pBody)
		{


			if (pBody->collide_Type == 2)
			{
				gpEventManager->UnSubcribe(HOMING_MISSILE_HIT, this->mpOwner);
				gpGoManager->delete_GameObjects.resize(gpGoManager->delete_GameObjects.size() + 1);
				gpGoManager->delete_GameObjects[gpGoManager->delete_GameObjects.size() - 1] = mpOwner;
			}
		}
	}
}




