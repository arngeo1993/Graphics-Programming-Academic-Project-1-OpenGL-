#include "CollisionManager.h"
#include "Math2D.h"



Shape::Shape(ShapeType TYPE)
{
	mType = TYPE;
	mpOwnerBody = nullptr;
}
ShapeAABB::ShapeAABB() : Shape(AABB)
{
	mTop= mBottom= mRight= mLeft=0;
}

ShapeAABB::~ShapeAABB()
{
}

bool ShapeAABB::TestPoint(float PointX, float PointY)
{
	return false;
}

ShapeCircle::ShapeCircle(): Shape(CIRCLE)
{
}

ShapeCircle::~ShapeCircle()
{
}

bool ShapeCircle::TestPoint(float PointX, float PointY)
{
	return false;
}









Contact::Contact()
{

	mBodies[0] = nullptr;
	mBodies[1] = nullptr;
}

bool CheckCollisionCircleCircle(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact *> &mContacts)
{

	
	ShapeCircle* pCirc1 = (ShapeCircle *)pShape1;
	ShapeCircle* pCirc2 = (ShapeCircle *)pShape2;

	bool CollisionResult;

	//Check for Circle to Circle Collision here

	

	

	

	if ((Pos1X - Pos2X)*(Pos1X - Pos2X) + (Pos1Y - Pos2Y)*(Pos1Y - Pos2Y) <= (pCirc1->mRadius + pCirc2->mRadius)*(pCirc1->mRadius + pCirc2->mRadius))
	{
		CollisionResult = true;
	}
	else
	{
		CollisionResult = false;
	}


	



	//If Collision,
	if (CollisionResult)
	{
		//Create Contact
		Contact* pC = new Contact();

		//Save the Body Owner
		pC->mBodies[0] = pShape1->mpOwnerBody;
		pC->mBodies[1] = pShape2->mpOwnerBody;

		//Add it to the list of Contacts
		mContacts.push_back(pC);


	}

	return CollisionResult;
	
}
bool CheckCollisionAABBAABB(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact *> &mContacts)
{
	

	ShapeAABB* pRect1 = (ShapeAABB *)pShape1;
	ShapeAABB* pRect2 = (ShapeAABB *)pShape2;

	bool CollisionResult;

	float leftA, leftB;
	float rightA, rightB;
	float topA, topB;
	float bottomA, bottomB;

	leftA = pRect1->mLeft;
	leftB = pRect2->mLeft;

	rightA = pRect1->mRight;
	rightB =pRect2->mRight;

	topA = pRect1->mTop;
	topB = pRect2->mTop;

	bottomA = pRect1->mBottom;
	bottomB = pRect2->mBottom;

	Vector2D rect_1, rect_2;
	rect_1.x = Pos1X;
	rect_1.y = Pos1Y;
	rect_2.x = Pos2X;
	rect_2.y = Pos2Y;
	//printf("rect 1=%f\n", rect_1.x);
	//printf("rect 2=%f\n", rect_2.x);

	if (StaticRectToStaticRect(&rect_1, rightA - leftA, bottomA - topA, &rect_2, rightB - leftB, bottomB - topB))
	{
		CollisionResult = true;
	}
	else
	{

		CollisionResult = false;
	}
	/*if (leftA > rightB || leftB > rightA || topA < bottomB || topB < bottomA)
		CollisionResult = false;
	else
		CollisionResult = true;*/
	
	
	//If Collision,

	if (CollisionResult)
	{
		

		//Create Contact
		Contact* pC = new Contact();

		//Save the Body Owner
		pC->mBodies[0] = pShape1->mpOwnerBody;
		pC->mBodies[1] = pShape2->mpOwnerBody;

		//Add it to the list of Contacts
		mContacts.push_back(pC);


	}

	return CollisionResult;
	
}

bool CheckCollisionCircleAABB(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact *> &mContacts)
{
	
	bool CollisionResult;

	//Check Collision Here
	ShapeAABB* pRect = (ShapeAABB *)pShape2;
	ShapeCircle* pCirc = (ShapeCircle *)pShape1;
	Vector2D cirlec_pos, rect_pos;
	Vector2DSet(&cirlec_pos, Pos1X, Pos1Y);
	Vector2DSet(&rect_pos, Pos2X, Pos2Y);

	
	CollisionResult = StaticPointToStaticRect(&cirlec_pos, &rect_pos, pRect->mRight - pRect->mLeft + pCirc->mRadius, pRect->mBottom - pRect->mTop + pCirc->mRadius);

	
	//If Collision,

	if (CollisionResult)
	{
		//Create Contact
		Contact* pC = new Contact();

		//Save the Body Owner
		pC->mBodies[0] = pShape2->mpOwnerBody;
		pC->mBodies[1] = pShape1->mpOwnerBody;

		//Add it to the list of Contacts
		mContacts.push_back(pC);
	}



	return CollisionResult;

	
}
bool CheckCollisionAABBCircle(Shape *pShape1, float Pos1X, float Pos1Y, Shape *pShape2, float Pos2X, float Pos2Y, std::list<Contact *> &mContacts)
{
	
	bool CollisionResult;

	//Check Collision Here
	ShapeAABB* pRect = (ShapeAABB *)pShape1;
	ShapeCircle* pCirc = (ShapeCircle *)pShape2;


	

	
	CollisionResult = CheckCollisionCircleAABB(pShape2, Pos2X, Pos2Y, pShape1, Pos1X,  Pos1Y, mContacts);
	//If Collision,

	if (CollisionResult)
	{
		//Create Contact
		Contact* pC = new Contact();

		//Save the Body Owner
		pC->mBodies[0] = pShape1->mpOwnerBody;
		pC->mBodies[1] = pShape2->mpOwnerBody;

		//Add it to the list of Contacts
		mContacts.push_back(pC);
	}



	return CollisionResult;

	
}
CollisionManager::CollisionManager()
{

	CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = CheckCollisionCircleCircle;
	CollisionFunctions[Shape::CIRCLE][Shape::AABB] = CheckCollisionCircleAABB;
	CollisionFunctions[Shape::AABB][Shape::AABB] = CheckCollisionAABBAABB;
	CollisionFunctions[Shape::AABB][Shape::CIRCLE] = CheckCollisionAABBCircle;
}

CollisionManager::~CollisionManager()
{
	Reset();
}

void CollisionManager::Reset()
{
	
	for (auto c : mContacts)
	{
		delete c;

	}
	mContacts.clear();

}

bool CollisionManager::CheckCollisionAndGenerateContact(Shape * pShape1, float Pos1X, float Pos1Y, Shape * pShape2, float Pos2X, float Pos2Y)
{

	
	
	return CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, Pos1X, Pos1Y, pShape2, Pos2X, Pos2Y, mContacts);
}




