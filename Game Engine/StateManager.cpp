#include "StateManager.h"
#include "InputManager.h"
#include "ObjectName.h"
#include "Body.h"
#include "GameObjectManager.h"
#include<iostream>
extern GameObjectManager* gpGoManager;

extern InputManager* gpInputManager;
StateManager::StateManager()
{
	state_tracker = 0;
	menuArrow = 0;
	levelArrow = 0;
	Change_Shader = 0;
	
	enemy_count = 0;
	shipLives = 0;
	win_lose = 0;

}

StateManager::~StateManager()
{
}

void StateManager::Update()
{
	//if()
	if (gpInputManager->isTriggered(KEYBOARD_KEYS::V))
	{
		if (Change_Shader == 0)
		{
			Change_Shader = 1;
		}
		else if (Change_Shader == 1)
		{
			Change_Shader = 0;
		}
	}

	if (gpInputManager->isTriggered(KEYBOARD_KEYS::UP))
	{
		if (state_tracker == 0)
		{
			if (menuArrow == 1)
			{

				menuArrow = 0;
				for (auto currentObject : gpGoManager->mGameObjects)
				{

					
					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == MENU_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.y = 554;
						pBody->mPos.x = 561;
						
					}
				}
			}
			
		}
		else if (state_tracker == 2)
		{
			if (levelArrow != 0)
			{
				levelArrow -= 1;
			}
			if (levelArrow == 0)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 281;

					}
				}
			}
			else if (levelArrow == 1)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 426;

					}
				}
			}
			else if (levelArrow == 2)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 571;

					}
				}
			}
			else if (levelArrow == 3)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 716;

					}
				}
			}

		}

	}
	else if (gpInputManager->isTriggered(KEYBOARD_KEYS::DOWN))
	{
		if (state_tracker == 0)
		{
			
			if (menuArrow == 0)
			{
				
				menuArrow = 1;
				for (auto currentObject : gpGoManager->mGameObjects)
				{

					
					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == MENU_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.y = 703;
						pBody->mPos.x = 629;
						
						
					}
				}
			}

		}
		else if (state_tracker == 2)
		{
			if (levelArrow != 3)
			{
				levelArrow += 1;
			}
			if (levelArrow == 0)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 281;

					}
				}
			}
			else if (levelArrow == 1)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 426;

					}
				}
			}
			else if (levelArrow == 2)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 571;

					}
				}
			}
			else if (levelArrow == 3)
			{
				for (auto currentObject : gpGoManager->mGameObjects)
				{


					ObjectName* pObj_Name = static_cast<ObjectName *>(currentObject->GetComponent(NAME));
					if (pObj_Name == nullptr)
						continue;
					if (pObj_Name->mType_Name == LEVEL_ARROW)
					{
						Body* pBody = static_cast<Body *>(currentObject->GetComponent(BODY));
						pBody->mPos.x = 650;
						pBody->mPos.y = 716;

					}
				}
			}

		}
	}

	else if (gpInputManager->isTriggered(KEYBOARD_KEYS::ENTER))
	{
	
		if (state_tracker == 0 && menuArrow == 0)
		{
			
			for (int i = 0; i < gpGoManager->mGameObjects.size(); i++) 
			{
				
				gpGoManager->mGameObjects[i]->~GameObject();
				
				
			}
			//gpGoManager->~GameObjectManager();
			gpGoManager->Clear_GameObjects();
	
		
			levelArrow = -1;
			state_tracker = 2;
			
		}
		if (state_tracker == 0 && menuArrow == 1)
		{

			for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
			{

				gpGoManager->mGameObjects[i]->~GameObject();


			}

			gpGoManager->Clear_GameObjects();
			//gpGoManager->~GameObjectManager();

			
			state_tracker = 1;

		}
		else if (state_tracker == 2 && levelArrow == 0)
		{
			for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
			{
				
				gpGoManager->mGameObjects[i]->~GameObject();
				

			}
			//gpGoManager->~GameObjectManager();
			gpGoManager->Clear_GameObjects();
			state_tracker = 3;
			shipLives = 8;
			enemy_count = 70;
		}
		else if (state_tracker == 2 && levelArrow == 1)
		{
			for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
			{
			
				gpGoManager->mGameObjects[i]->~GameObject();
				
			}
			gpGoManager->Clear_GameObjects();
			//gpGoManager->~GameObjectManager();
			state_tracker = 4;
			shipLives = 8;
			enemy_count = 7;
		}
		else if (state_tracker == 2 && levelArrow == 2)
		{
			for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
			{
				
				gpGoManager->mGameObjects[i]->~GameObject();
				

			}
			gpGoManager->Clear_GameObjects();
			//gpGoManager->~GameObjectManager();
			state_tracker = 5;
			shipLives = 8;
			enemy_count = 70;
		}
		else if (state_tracker == 2 && levelArrow == 3)
		{
			for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
			{
				
				gpGoManager->mGameObjects[i]->~GameObject();
				

			}
			gpGoManager->Clear_GameObjects();
			//gpGoManager->~GameObjectManager();
			state_tracker = 6;
			shipLives = 8;
			enemy_count = 70;
		}
	}
	else if (gpInputManager->isTriggered(KEYBOARD_KEYS::ESC))
	{
		if (state_tracker != 0)
		{
			for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
			{
				
				gpGoManager->mGameObjects[i]->~GameObject();
				

			}
			gpGoManager->Clear_GameObjects();
		//	gpGoManager->~GameObjectManager();
			state_tracker = 0;
			menuArrow = 0;
		}
		
		
	}
	else if((state_tracker == 3|| state_tracker == 4|| state_tracker == 5|| state_tracker == 6)&& shipLives <= 0)
	{
		
			win_lose = 2;
		
		


		for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
		{

			gpGoManager->mGameObjects[i]->~GameObject();


		}
		gpGoManager->Clear_GameObjects();
	//	gpGoManager->~GameObjectManager();
		state_tracker = 7;
	}
	else if ((state_tracker == 3 || state_tracker == 4 || state_tracker == 5 || state_tracker == 6) && enemy_count <= 0)
	{

		win_lose = 1;
		

	


		for (int i = 0; i < gpGoManager->mGameObjects.size(); i++)
		{

			gpGoManager->mGameObjects[i]->~GameObject();


		}
		gpGoManager->Clear_GameObjects();
	//	gpGoManager->~GameObjectManager();
		state_tracker = 7;
	}

	
}
