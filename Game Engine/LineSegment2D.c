/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LineSegment2D
Purpose: used for building the line segment
Language: C++
Platform: Visual studio 2015 and plus
Project: CS529_Arnold.George_2
Author: Arnold George, arnold.george,  60001018 <provide your name, student login, and student id>
Creation date: 10/5/2018
- End Header --------------------------------------------------------*/
#include "LineSegment2D.h"
//#include "main.h"

int BuildLineSegment2D(LineSegment2D *LS, Vector2D *Point0, Vector2D *Point1)
{
	Vector2DSet(&LS->mP0, Point0->x, Point0->y);
	Vector2DSet(&LS->mP1, Point1->x, Point1->y);
	Vector2D normal,temp;
	Vector2DSet(&temp, Point1->x - Point0->x, Point1->y- Point0->y);
	normal.x = temp.x*cos(-90 * 0.0174533) - temp.y*sin(-90 * 0.0174533);
	normal.y = temp.x*sin(-90 * 0.0174533) + temp.y * cos(-90 * 0.0174533);

	Vector2DNormalize(&normal, &normal);

	Vector2DSet(&LS->mN, normal.x, normal.y);
	
	LS->mNdotP0 = Vector2DDotProduct(&LS->mN , Point0);
	

	return 1;
}