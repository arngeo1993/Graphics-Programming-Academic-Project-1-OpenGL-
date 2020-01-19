#include "GameObject.h"
#include "Sprite.h"
#include "Transform.h"
#include "Controller.h"
#include "UpDown.h"
#include "Body.h"
#include "ObjectName.h"
#include "GameObjectManager.h"


extern GameObjectManager* gpGoManager;

GameObject::GameObject() {}


GameObject::~GameObject() {
	for (auto c : mComponents)
		delete c;
//	mComponents.clear();
	
	
}

void GameObject::Update() {

	
	for (auto c : mComponents)
		c->Update();
}

Component* GameObject::AddComponent(unsigned int Type) {
	Component* pNewComponent = nullptr;

	switch (Type) {

	case TRANSFORM:
		pNewComponent = new Transform();
		break;

	case NAME:
		pNewComponent = new ObjectName();
		break;

	case SPRITE:
		pNewComponent = new Sprite();
		break;

	case CONTROLLER:
		pNewComponent = new Controller();
		break;

	case UPDOWN:
		pNewComponent = new UpDown();
		break;
	case BODY:
		pNewComponent = new Body();
		break;
	}

	if (pNewComponent != nullptr) {
		mComponents.push_back(pNewComponent);
		
		pNewComponent->mpOwner = this;
	}

	return pNewComponent;
}

Component* GameObject::GetComponent(unsigned int Type) {
	for (auto c : mComponents) {

		if (c == nullptr)
			continue;
		if (c->GetType() == Type)
			return c;
	}
	return nullptr;
}


void GameObject::HandleEvent(Event * pEvent)
{
	for (auto c : mComponents)
	{
		c->HandleEvent(pEvent);
	}
}