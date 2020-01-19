#pragma once
#include "Component.h"

class UpDown : public Component
{
public:
	UpDown();
	~UpDown();

	void Update();
	void Serialize(FILE **fpp);
//	void HandleEvent(Event *pEvent);
private:
	bool mGoingUp;
	int mTimer, mTimerLimit;

};
