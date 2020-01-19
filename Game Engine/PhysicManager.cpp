#include "PhysicManager.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "CollisionManager.h"
#include "Body.h"
#include "ObjectName.h"

extern GameObjectManager* gpGoManager;
extern CollisionManager* gpCollisionManger ;
PhysicManager::PhysicManager()
{
}

PhysicManager::~PhysicManager()
{
}

void PhysicManager::Update(float FrameTime)
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

	

		Body *pBody = static_cast<Body *>(go->GetComponent(BODY));

		if (nullptr != pBody)
		{
			
			pBody->Integrate(100.0f, FrameTime );
		}
		else
		{
			continue;
		}
	}

	


	gpCollisionManger->Reset();
	
	auto pObj1 =gpGoManager->mGameObjects.begin();
	auto pObjLast = gpGoManager->mGameObjects.end();

	for (; pObj1 != pObjLast; ++pObj1)
	{
		
		Body *pBody1 = static_cast<Body *>((*pObj1)->GetComponent(BODY));

		if (pBody1 == nullptr)
			continue;
			ObjectName* pObj_Name_1 = static_cast<ObjectName *>(pBody1->mpOwner->GetComponent(NAME));

			if (pObj_Name_1->mType_Name != BACKGROUND_1)
			{
				if (nullptr == pBody1)
				{

					continue;
				}

				for (auto pobj2 = pObj1 + 1; pobj2 != pObjLast; ++pobj2)
				{

					Body *pBody2 = static_cast<Body *>((*pobj2)->GetComponent(BODY));
					if (nullptr == pBody2)
					{

						continue;
					}
					ObjectName* pObj_Name_2 = static_cast<ObjectName *>(pBody2->mpOwner->GetComponent(NAME));
					if (pObj_Name_2->mType_Name != BACKGROUND_1)
					{
						if (nullptr == pBody2)
						{

							continue;
						}

						gpCollisionManger->CheckCollisionAndGenerateContact(pBody1->mpShape, pBody1->mPos.x, pBody1->mPos.y,
							pBody2->mpShape, pBody2->mPos.x, pBody2->mPos.y);
					}

				}
			}


		
	}


	for (auto c : gpCollisionManger->mContacts)
	{
		ObjectName* pObj_Name_1 = static_cast<ObjectName *>(c->mBodies[0]->mpOwner->GetComponent(NAME));
		ObjectName* pObj_Name_2 = static_cast<ObjectName *>(c->mBodies[1]->mpOwner->GetComponent(NAME));
		if (pObj_Name_1 == nullptr)
			continue;
		if (pObj_Name_2 == nullptr)
			continue;
		if (pObj_Name_1->mType_Name == SHIP)
		{
			ShipCollideEvent ce1;

			if (pObj_Name_2->mType_Name == SHIP)
			{

				ShipCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
				
			}
			else if (pObj_Name_2->mType_Name == ASTEROID)
			{
				AsteroidCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
				
			}
			else if (pObj_Name_2->mType_Name == ENEMY_SHIP)
			{
				EnemyCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else if (pObj_Name_2->mType_Name == BULLET)
			{
				BulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else if (pObj_Name_2->mType_Name == HOMING_MISSILE)
			{
				HomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_BULLET)
			{
				EnemyBulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
			{
				EnemyHomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}


			
			




		}
		 else if  (pObj_Name_1->mType_Name == ASTEROID)
		{
			AsteroidCollideEvent ce1;


			 if  (pObj_Name_2->mType_Name == SHIP)
			{

				ShipCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ASTEROID)
			{
				AsteroidCollideEvent ce2;
				c->mBodies[0]->collide_Type = 1;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 1;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP)
			{
				EnemyCollideEvent ce2;
				c->mBodies[0]->collide_Type = 1;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == BULLET)
			{
				BulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == HOMING_MISSILE)
			{
				HomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_BULLET)
			{
				EnemyBulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
			{
				EnemyHomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
		}
		 else if  (pObj_Name_1->mType_Name == ENEMY_SHIP)
		{
			EnemyCollideEvent ce1;

			 if  (pObj_Name_2->mType_Name == SHIP)
			{

				ShipCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ASTEROID)
			{
				AsteroidCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 1;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP)
			{
				EnemyCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == BULLET)
			{
				BulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == HOMING_MISSILE)
			{
				HomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_BULLET)
			{
				EnemyBulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
			{
				EnemyHomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
		}
		 else if  (pObj_Name_1->mType_Name == BULLET)
		{
			BulletCollideEvent ce1;

			 if  (pObj_Name_2->mType_Name == SHIP)
			{

				ShipCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ASTEROID)
			{
				AsteroidCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP)
			{
				EnemyCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == BULLET)
			{
				BulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == HOMING_MISSILE)
			{
				HomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_BULLET)
			{
				EnemyBulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
			{
				EnemyHomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
		}
		 else if  (pObj_Name_1->mType_Name == HOMING_MISSILE)
		{
			HomingMissileCollideEvent ce1;

			if  (pObj_Name_2->mType_Name == SHIP)
			{

				ShipCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ASTEROID)
			{
				AsteroidCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP)
			{
				EnemyCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == BULLET)
			{
				BulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == HOMING_MISSILE)
			{
				HomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_BULLET)
			{
				EnemyBulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
			{
				EnemyHomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
		}
		 else if  (pObj_Name_1->mType_Name == ENEMY_SHIP_BULLET)
		{
			EnemyBulletCollideEvent ce1;

			 if  (pObj_Name_2->mType_Name == SHIP)
			{

				ShipCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ASTEROID)
			{
				AsteroidCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			 else if  (pObj_Name_2->mType_Name == ENEMY_SHIP)
			{
				EnemyCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			 else if  (pObj_Name_2->mType_Name == BULLET)
			{
				BulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else  if  (pObj_Name_2->mType_Name == HOMING_MISSILE)
			{
				HomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else  if  (pObj_Name_2->mType_Name == ENEMY_SHIP_BULLET)
			{
				EnemyBulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else  if  (pObj_Name_2->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
			{
				EnemyHomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
		}
		 else if  (pObj_Name_1->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
		{
			EnemyHomingMissileCollideEvent ce1;

			 if  (pObj_Name_2->mType_Name == SHIP)
			{

				ShipCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			else  if  (pObj_Name_2->mType_Name == ASTEROID)
			{
				AsteroidCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);

			}
			else  if  (pObj_Name_2->mType_Name == ENEMY_SHIP)
			{
				EnemyCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else if (pObj_Name_2->mType_Name == BULLET)
			{
				BulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else if (pObj_Name_2->mType_Name == HOMING_MISSILE)
			{
				HomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 2;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 2;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else if (pObj_Name_2->mType_Name == ENEMY_SHIP_BULLET)
			{
				EnemyBulletCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
			else if (pObj_Name_2->mType_Name == ENEMY_SHIP_HOMING_MISSILE)
			{
				EnemyHomingMissileCollideEvent ce2;
				c->mBodies[0]->collide_Type = 0;
				c->mBodies[0]->mpOwner->HandleEvent(&ce1);
				c->mBodies[1]->collide_Type = 0;
				c->mBodies[1]->mpOwner->HandleEvent(&ce2);
			}
		}



		

	}

}
