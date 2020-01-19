#pragma once
#include <list>
#include <unordered_map>

enum EventType
{
	
	SHIP_HIT,
	BULLET_HIT,
	HOMING_MISSILE_HIT,
	ASTEROID_HIT,
	ENEMY_HIT,
	ENEMY_BULLET_HIT,
	ENEMY_HOMING_MISSILE_HIT,
	


	NUM
};

class Event
{
public:
	Event(EventType Type);
	virtual ~Event(){}

public:
	EventType mType;

	float mTimer;
};

class GameObject;
class EventManager
{
public:
	EventManager();
	~EventManager();
	void BroadCastEvent(Event *pEvent);
	void BroadCastEventToSubscribers(Event *pEvent);
	void AddTimedEvent(Event *pEvent);

	void Update(float FRamedTime);
	void Subscribe(EventType Type, GameObject *pGampGameObjectNewSubscriberseObject);
	void UnSubcribe(EventType Type, GameObject *pGampGameObjectNewSubscriberseObject);

public :
	std::list<Event *>mTimedEvents;

	std::unordered_map<EventType, std::list<GameObject *>> mSubscriptions;
};
