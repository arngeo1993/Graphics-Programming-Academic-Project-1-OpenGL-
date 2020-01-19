#include "Controller.h"
#include "InputManager.h"
#include "GameObject.h"
#include "SDL_Scancode.h"
#include "Transform.h"
#include "Body.h"
#include "EventManager.h"
#include "PhysicManager.h"
#include "ObjectName.h"
#include "Vector2D.h"
#include "Matrix2D.h"
#include "FrameRateController.h"
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "ObjectFactory.h"
#include "GameObjectManager.h"

extern GameObjectManager* gpGoManager;
extern ObjectFactory* gpObjectFactory;
extern InputManager* gpInputManager;
extern EventManager *gpEventManager;
extern FrameRateController *pFrameRateController;
#define PI							22/7
#define SHIP_ACCEL_FORWARD			150.0f				
#define SHIP_ACCEL_BACKWARD			-150.0f	
#define SHIP_ROT_SPEED	             (2.0f * PI)	
#define BULLET_SPEED				1000.0f		
#define HOMING_MISSILE_ROT_SPEED	(PI / 2.0f)
#define HOMING_BULLET_SPEED			100.0f

Controller::Controller() : Component(CONTROLLER) {
	size = 0;
}

Controller::~Controller() {}

//PlayerHitEvent::PlayerHitEvent() : Event(PLAYER_HIT)
//{
//
//}

float normalise(const float value, const float start, const float end)
{
	const float width = end - start;   // 
	const float offsetValue = value - start;   // value relative to 0

	return (offsetValue - (floor(offsetValue / width) * width)) + start;
	// + start to reset back to start of original range
}
void Controller::Update() {
	if (mpOwner != nullptr && gpInputManager != nullptr)
	{
		ObjectName* pName = static_cast<ObjectName*>(mpOwner->GetComponent(NAME));

		
			Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
			if (pBody != nullptr) 
			{


				if (gpInputManager->isPressed(KEYBOARD_KEYS::W)) {





					Vector2D added;

					Vector2DSet(&added, cosf(pBody->mAngle), sinf(pBody->mAngle));


					added.x *= SHIP_ACCEL_FORWARD;
					added.y *= SHIP_ACCEL_FORWARD;
					pBody->mAcc = added;





				}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::S)) {




					Vector2D added;

					Vector2DSet(&added, cosf(pBody->mAngle), sinf(pBody->mAngle));


					added.x *= SHIP_ACCEL_BACKWARD;
					added.y *= SHIP_ACCEL_BACKWARD;
					pBody->mAcc = added;




				}
				//if (gpInputManager->isPressed(SDL_SCANCODE_DOWN)) {
				//	pBody->mPosY += 1;
				//}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::A)) {

					pBody->mAngle -= SHIP_ROT_SPEED * (float)(pFrameRateController->GetFrameTime());

					pBody->mAngle = normalise(pBody->mAngle, -PI, PI);

				}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::D)) {
					//pBody->mPosX += 11;
					pBody->mAngle += SHIP_ROT_SPEED * (float)(pFrameRateController->GetFrameTime());
					pBody->mAngle = normalise(pBody->mAngle, -PI, PI);
				}


				if (gpInputManager->isPressed(KEYBOARD_KEYS::UP)) {
					




					Vector2D added;
					
					Vector2DSet(&added, cosf(pBody->mAngle), sinf(pBody->mAngle));
					
					
					added.x *= SHIP_ACCEL_FORWARD;
					added.y *= SHIP_ACCEL_FORWARD;
					pBody->mAcc = added;
				

					


				}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::DOWN)) {




					Vector2D added;

					Vector2DSet(&added, cosf(pBody->mAngle), sinf(pBody->mAngle));


					added.x *= SHIP_ACCEL_BACKWARD;
					added.y *= SHIP_ACCEL_BACKWARD;
					pBody->mAcc = added;




				}
				//if (gpInputManager->isPressed(SDL_SCANCODE_DOWN)) {
				//	pBody->mPosY += 1;
				//}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::Q)) {

					pBody->mAngle -= SHIP_ROT_SPEED * (float)(pFrameRateController->GetFrameTime());

					pBody->mAngle = normalise(pBody->mAngle, -PI, PI);

				}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::E)) {
					//pBody->mPosX += 11;
					pBody->mAngle += SHIP_ROT_SPEED * (float)(pFrameRateController->GetFrameTime());
					pBody->mAngle = normalise(pBody->mAngle, -PI, PI);
				}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::LEFT)) {
					
					pBody->mAngle -= SHIP_ROT_SPEED * (float)(pFrameRateController->GetFrameTime());
					
					pBody->mAngle = normalise(pBody->mAngle, -PI, PI);

				}
				if (gpInputManager->isPressed(KEYBOARD_KEYS::RIGHT)) {
					//pBody->mPosX += 11;
					pBody->mAngle += SHIP_ROT_SPEED * (float)(pFrameRateController->GetFrameTime());
					pBody->mAngle = normalise(pBody->mAngle, -PI, PI);
				}
				if (gpInputManager->isTriggered(KEYBOARD_KEYS::SPACE)) 
				{
						GameObject *pGO_Bullet = gpObjectFactory->LoadObject("Bullet.txt");
							Body* pBody_Bullet = static_cast<Body *>(pGO_Bullet->GetComponent(BODY));
							if (nullptr != pBody_Bullet)
							{
								Vector2DSet(&pBody_Bullet->mPos, pBody->mPos.x, pBody->mPos.y);
						
								Vector2DSet(&pBody_Bullet->mVel, cosf(pBody->mAngle)*BULLET_SPEED, sinf(pBody->mAngle)*BULLET_SPEED);
								//gpGoManager->mGameObjects.resize(gpGoManager->mGameObjects.size()+1);
								//gpGoManager->mGameObjects[gpGoManager->mGameObjects.size() - 1] = pGO_Bullet;
								//gpGoManager->mGameObjects.push_back(pGO_Bullet);
							
								//gpGoManager->new_GameObjects.push_back(pGO_Bullet);
								gpGoManager->new_GameObjects.resize(gpGoManager->new_GameObjects.size()+1);
								gpGoManager->new_GameObjects[gpGoManager->new_GameObjects.size() - 1] = pGO_Bullet;
							}
					
				}
				if (gpInputManager->isTriggered(KEYBOARD_KEYS::M))
				{
					GameObject *pGO_Bullet = gpObjectFactory->LoadObject("Homing Missile.txt");
					Body* pBody_Bullet = static_cast<Body *>(pGO_Bullet->GetComponent(BODY));
					if (nullptr != pBody_Bullet)
					{
						Vector2DSet(&pBody_Bullet->mPos, pBody->mPos.x, pBody->mPos.y);
						Vector2DSet(&pBody_Bullet->mVel, cosf(pBody->mAngle)*HOMING_BULLET_SPEED, sinf(pBody->mAngle)*HOMING_BULLET_SPEED);
						gpGoManager->new_GameObjects.resize(gpGoManager->new_GameObjects.size() + 1);
						gpGoManager->new_GameObjects[gpGoManager->new_GameObjects.size() - 1] = pGO_Bullet;
					}

				}
			}
		
	
		
	}
}



