#include "UpDown.h"
#include "Transform.h"
#include "FrameRateController.h"
#include "GameObject.h"
#include <iostream>
#include "EventManager.h"
#include "Body.h"
extern FrameRateController *pFrameRateController;
extern EventManager *gpEventManager;
UpDown::UpDown(): Component(UPDOWN)
{
	mGoingUp = true;
	mTimer = 0;
	mTimerLimit = 1000;
}

UpDown::~UpDown()
{
}

void UpDown::Update()
{
	mTimer += pFrameRateController->GetFrameTime();
	
	if (mTimer < 0)
	{
		mTimerLimit = 1000;
		mTimer = 0;
	}
	
	if (mTimer > mTimerLimit)
	{
		
		mGoingUp = !mGoingUp;
		mTimer = 0;
	}
	
	Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));

	if (nullptr != pBody)
	{
		
		if (true==mGoingUp)
		{
			//pBody->mPosY += 1;
			
		}
		else
		{
			
			//pBody->mPosY -= 1;
		}
	}
	
}

void UpDown::Serialize(FILE **fpp)
{

	int goingUp, timerLimit, subscribe;
	//fscanf_s(*fpp, "%i %i\n", &goingUp, &timerLimit);
	fscanf_s(*fpp, "%i %i %i\n", &goingUp,&timerLimit,&subscribe);
	
	mGoingUp = (bool)goingUp;
	mTimerLimit = timerLimit;

	if (1 == subscribe)
	{
		
		//gpEventManager->Subscribe(PLAYER_HIT, this->mpOwner);
	}
	
}



//void UpDown :: HandleEvent(Event *pEvent)
//{
//	if (PLAYER_HIT == pEvent->mType)
//	{
//		
//		Body * pBody = static_cast<Body *>(mpOwner->GetComponent(BODY));
//			if (nullptr != pBody)
//			{
//				//pBody->mPosX += 100;
//			
//			}
//	}
//}
