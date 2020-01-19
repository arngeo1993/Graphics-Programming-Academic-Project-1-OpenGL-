#pragma once
#include "GameObject.h"

enum StateNames
{
	MENUSTATE,
	CONTROLLS,
	LEVEL_SELECT,
	LEVEL_1,
	LEVEL_2,
	LEVEL_3,
	LEVEL_4,
	Game_OVER

};

class StateManager
{
public :
	StateManager();
	~StateManager();
	void Update();

	int state_tracker;
	int menuArrow;
	int levelArrow;
	int shipLives;
	int enemy_count;
	int Change_Shader;
	int  win_lose;
	

};
