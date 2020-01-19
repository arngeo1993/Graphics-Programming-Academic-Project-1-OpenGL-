#include "ObjectFactory.h"
#include "Transform.h"
#include <stdio.h>
#include <string>
#include "GameObjectManager.h"
#include "GameObject.h"

#include "Sprite.h"
#include "Component.h"
#include "Controller.h"
#include "Body.h"
#include <iostream>

extern GameObjectManager* gpGoManager;
ObjectFactory::ObjectFactory()
{

}
ObjectFactory::~ObjectFactory()
{
}
void ObjectFactory::LoadLevel(const char * mfileName)
{

	FILE *fp;
	std::string fullPath = "..\\Resource\\";
	fullPath += mfileName;
	fopen_s(&fp, fullPath.c_str(), "r");
	if (fp)
	{
		while (!feof(fp))
		{
			char objectFileName[256] = { 0 };

			fscanf_s(fp, "%255s\n", objectFileName, sizeof(objectFileName));

			std::string stringObjectFileName = objectFileName;
			
			GameObject *pGameObject = LoadObject(stringObjectFileName.c_str());
			
			//Transform* pTr = static_cast<Transform*>(pGameObject->GetComponent(TRANSFORM));
			//pTr->Serialize(&fp);
			Body* pBody = static_cast<Body *>(pGameObject->GetComponent(BODY));
			if (nullptr != pBody)
			{
				pBody->Initialize();
			}
			

		}
		fclose(fp);
	}
}

GameObject * ObjectFactory::LoadObject(const char * mfileName)
{
	GameObject *pNewGameObject = nullptr;

	FILE *fp;
	std::string fullPath = "..\\Resource\\";
	fullPath += mfileName;
	fopen_s(&fp, fullPath.c_str(), "r");

	if (fp)
	{
		
		pNewGameObject = new GameObject();
		while (!feof(fp))
		{
			char ComponentName[256] = { 0 };

			fscanf_s(fp, "%255s\n", ComponentName, sizeof(ComponentName));

			std::string stringComponentName = ComponentName;
			Component *pNewComponent = nullptr;
			if ("Transform" == stringComponentName)
			{

				pNewComponent = pNewGameObject->AddComponent(TRANSFORM);
			}
			else if ("Name" == stringComponentName)
			{
				
				pNewComponent = pNewGameObject->AddComponent(NAME);
			}
			else if ("Sprite" == stringComponentName)
			{

				pNewComponent = pNewGameObject->AddComponent(SPRITE);
			}
			else if ("Controller" == stringComponentName)
			{

				pNewComponent = pNewGameObject->AddComponent(CONTROLLER);
			}
			else if ("UpDown" == stringComponentName)
			{

				pNewComponent = pNewGameObject->AddComponent(UPDOWN);
			}
			else if ("Body" == stringComponentName)
			{

				pNewComponent = pNewGameObject->AddComponent(BODY);

				
			}
			if (nullptr != pNewComponent)
			{
				pNewComponent->Serialize(&fp);
			}
		}
		
		gpGoManager->mGameObjects.push_back(pNewGameObject);
		
		fclose(fp);
	}
	return pNewGameObject;
}
