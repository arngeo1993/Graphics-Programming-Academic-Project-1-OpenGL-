#include "EventManager.h"

#include "GameObjectManager.h"
#include "GameObject.h"

extern GameObjectManager* gpGoManager ;

Event::Event(EventType Type)
{

	mType = Type;
	mTimer = 0;
}

EventManager::EventManager()
{

	
}

EventManager::~EventManager()
{
}

void EventManager::BroadCastEvent(Event * pEvent)
{
	for (auto goc : gpGoManager->mGameObjects)
	{
		goc->HandleEvent(pEvent);
	}

}

void EventManager::BroadCastEventToSubscribers(Event * pEvent)
{
	auto &listOfSubscribers = mSubscriptions[pEvent->mType];

	for (auto pGO : listOfSubscribers)
	{
		pGO->HandleEvent(pEvent);
	}
}

void EventManager::AddTimedEvent(Event *pEvent)
{
	mTimedEvents.push_back(pEvent);
}

void EventManager::Update(float FrameTime)
{

	//:Loop through all timed events
	//Decrease Timer by FramedTime
	//<0?->Fire Event

	std::list<Event*>::iterator it;
	it = mTimedEvents.begin();

	while(it != mTimedEvents.end())
	{
		Event *pEvent = *it;
		
			pEvent->mTimer -= FrameTime;
		if (pEvent->mTimer < 0.0f)
		{
			//BroadCastEvent(pEvent);
			BroadCastEventToSubscribers(pEvent);
			delete pEvent;
			
			it = mTimedEvents.erase(it);
		
		}
		else
		{
			++it;
		}
	}

}

void EventManager::Subscribe(EventType Type, GameObject * pGampGameObjectNewSubscriberseObject)
{
	//std::list<GameObject*> &listOfSubscribers = mSubscriptions[Type];
		auto &listOfSubscribers = mSubscriptions[Type];

	for (auto pGO : listOfSubscribers)
	{
		if (pGO == pGampGameObjectNewSubscriberseObject)
		{
			return;
		}
	}

	listOfSubscribers.push_back(pGampGameObjectNewSubscriberseObject);
}

void EventManager::UnSubcribe(EventType Type, GameObject * pGampGameObjectNewSubscriberseObject)
{
	auto &listOfSubscribers = mSubscriptions[Type];
	auto it = std::find(listOfSubscribers.begin(), listOfSubscribers.end(), pGampGameObjectNewSubscriberseObject);
	if (it == listOfSubscribers.end())
	{
		return;
	}
	listOfSubscribers.erase(it);
}



