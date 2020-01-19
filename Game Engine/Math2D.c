/* Start Header -------------------------------------------------------
Copyright (C) 20xx DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Math2d.c
Purpose: used for colision detection and refelection
Language: C++
Platform: Visual studio 2015 and plus
Project: CS529_Arnold.George_2
Author: Arnold George, arnold.george,  60001018 <provide your name, student login, and student id>
Creation date: 10/5/2018
- End Header --------------------------------------------------------*/

#include "Math2D.h"
#include "stdio.h"
//#include "main.h"

////////////////////
// From Project 1 //
////////////////////


/*
This function checks if the point P is colliding with the circle whose
center is "Center" and radius is "Radius"
*/
int StaticPointToStaticCircle(Vector2D *pP, Vector2D *pCenter, float Radius)
{
	if ((pP->x - pCenter->x)*(pP->x - pCenter->x) + (pP->y - pCenter->y)*(pP->y - pCenter->y) < Radius*Radius)
	{
		return 1;
	}
	else
	{
		return 0;
	}


}


/*
This function checks if the point Pos is colliding with the rectangle
whose center is Rect, width is "Width" and height is Height
*/
int StaticPointToStaticRect(Vector2D *pPos, Vector2D *pRect, float Width, float Height)
{
	if ((pPos->x >= (pRect->x - Width / 2)) &&
		(pPos->x <= (pRect->x + Width / 2)) &&
		(pPos->y >= (pRect->y - Height / 2)) &&
		(pPos->y <= (pRect->y + Height / 2)))
	{
		return 1;
	}
	else
	{

		return 0;
	}


}

/*
This function checks for collision between 2 circles.
Circle0: Center is Center0, radius is "Radius0"
Circle1: Center is Center1, radius is "Radius1"
*/
int StaticCircleToStaticCircle(Vector2D *pCenter0, float Radius0, Vector2D *pCenter1, float Radius1)
{
	if ((pCenter0->x - pCenter1->x)*(pCenter0->x - pCenter1->x) + (pCenter0->y - pCenter1->y)*(pCenter0->y - pCenter1->y) <= (Radius0 + Radius1)*(Radius0 + Radius1))
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

/*
This functions checks if 2 rectangles are colliding
Rectangle0: Center is pRect0, width is "Width0" and height is "Height0"
Rectangle1: Center is pRect1, width is "Width1" and height is "Height1"
*/
int StaticRectToStaticRect(Vector2D *pRect0, float Width0, float Height0, Vector2D *pRect1, float Width1, float Height1)
{
	float rect_1_x_low = pRect0->x - Width0 / 2,
		rect_1_x_high = pRect0->x + Width0 / 2;
	float rect_1_y_low = pRect0->y - Height0 / 2,
		rect_1_y_high = pRect0->y + Height0 / 2;

	float rect_2_x_low = pRect1->x - Width1 / 2,
		rect_2_x_high = pRect1->x + Width1 / 2;
	float rect_2_y_low = pRect1->y - Height1 / 2,
		rect_2_y_high = pRect1->y + Height1 / 2;

	if ((rect_1_x_low > rect_2_x_low) && (rect_1_x_low < rect_2_x_high) && (rect_1_y_low > rect_2_y_low) && (rect_1_y_low < rect_2_y_high))
	{
		return 1;
	}
	else if ((rect_1_x_low > rect_2_x_low) && (rect_1_x_low < rect_2_x_high) && (rect_1_y_high > rect_2_y_low) && (rect_1_y_high < rect_2_y_high))
	{
		return 1;
	}
	else if ((rect_1_x_high > rect_2_x_low) && (rect_1_x_high < rect_2_x_high) && (rect_1_y_low > rect_2_y_low) && (rect_1_y_low < rect_2_y_high))
	{
		return 1;
	}
	else if ((rect_1_x_high > rect_2_x_low) && (rect_1_x_high < rect_2_x_high) && (rect_1_y_high > rect_2_y_low) && (rect_1_y_high < rect_2_y_high))
	{
		return 1;
	}
	else if ((pRect0->x - pRect1->x)*(pRect0->x - pRect1->x) + (pRect0->y - pRect1->y)*(pRect0->y - pRect1->y) <= (Width0 + Width1)*(Width0 + Width1))
	{
		return 1;
	}
	else if ((pRect0->x - pRect1->x)*(pRect0->x - pRect1->x) + (pRect0->y - pRect1->y)*(pRect0->y - pRect1->y) <= (Height0 + Height1)*(Height0 + Height1))
	{
		return 1;
	}
	else
	{
		return 0;
	}



}


//////////////////////
// New to project 2 //
//////////////////////


/*
This function determines the distance separating a point from a line

 - Parameters
	- P:		The point whose location should be determined
	- LS:		The line segment

 - Returned value: The distance. Note that the returned value should be:
	- Negative if the point is in the line's inside half plane
	- Positive if the point is in the line's outside half plane
	- Zero if the point is on the line
*/
float StaticPointToStaticLineSegment(Vector2D *P, LineSegment2D *LS)
{
	float temp = Vector2DDotProduct(&LS->mN, P) - Vector2DDotProduct(&LS->mN, &LS->mP0);

	
	return temp;
}


/*
This function checks whether an animated point is colliding with a line segment

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi)
{
	Vector2D velocity,vel_1,vel_2, intersection_Point, temp_1, temp_2;
	float time;
	Vector2DSet(&velocity,Pe->x-Ps->x,Pe->y-Ps->y);
	Vector2DSet(&vel_1, LS->mP1.x - LS->mP0.x, LS->mP1.y - LS->mP0.y);
	Vector2DSet(&vel_2, LS->mP0.x - LS->mP1.x, LS->mP0.y - LS->mP1.y);
	time = (Vector2DDotProduct(&LS->mN, &LS->mP0)-Vector2DDotProduct(&LS->mN, Ps)) / Vector2DDotProduct(&LS->mN, &velocity);
	Vector2DScaleAdd(&intersection_Point, &velocity, Ps, time);
	
	Vector2DSub(&temp_1,&intersection_Point,&LS->mP0);
	Vector2DSub(&temp_2, &intersection_Point, &LS->mP1);
	Vector2DSet(Pi, intersection_Point.x, intersection_Point.y);
	
	if (Vector2DDotProduct(&LS->mN, Ps) < Vector2DDotProduct(&LS->mN, &LS->mP0) && Vector2DDotProduct(&LS->mN, Pe) < Vector2DDotProduct(&LS->mN, &LS->mP0))
	{
		
		return -1.0f;
	}
	else if (Vector2DDotProduct(&LS->mN, Ps) > Vector2DDotProduct(&LS->mN, &LS->mP0) && Vector2DDotProduct(&LS->mN, Pe) > Vector2DDotProduct(&LS->mN, &LS->mP0))
	{
		
		return -1.0f;
	}
	else if (Vector2DDotProduct(&LS->mN, &velocity)==0)
	{
		
		return -1.0f;
	}
	else if (Vector2DDotProduct(&temp_1, &vel_1) < 0)
	{
		
		return -1.0f;
	}
	else if (Vector2DDotProduct(&temp_2, &vel_2) < 0)
	{
		
		return -1.0f;
	}
	else
	{
		
		
		return time;
	}
	
	

	
}


/*
This function checks whether an animated circle is colliding with a line segment

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi)
{
	Vector2D velocity, vel_1, vel_2, intersection_Point, temp_1, temp_2;
	float time, radius_neg_pos, circle_radius;
	
	radius_neg_pos = StaticPointToStaticLineSegment(Ps, LS);
	
	if (radius_neg_pos <0)
	{
		circle_radius = -1 * Radius;
	}
	else if(radius_neg_pos >0)
	{
		circle_radius =  Radius;
	}


	Vector2DSet(&velocity, Pe->x - Ps->x, Pe->y - Ps->y);
	Vector2DSet(&vel_1, LS->mP1.x - LS->mP0.x, LS->mP1.y - LS->mP0.y);
	Vector2DSet(&vel_2, LS->mP0.x - LS->mP1.x, LS->mP0.y - LS->mP1.y);
	time = (Vector2DDotProduct(&LS->mN, &LS->mP0) - Vector2DDotProduct(&LS->mN, Ps)+circle_radius) / Vector2DDotProduct(&LS->mN, &velocity);
	Vector2DScaleAdd(&intersection_Point, &velocity, Ps, time);

	Vector2DSub(&temp_1, &intersection_Point, &LS->mP0);
	Vector2DSub(&temp_2, &intersection_Point, &LS->mP1);
	Vector2DSet(Pi, intersection_Point.x, intersection_Point.y);
	

	if (Vector2DDotProduct(&LS->mN, Ps) - Vector2DDotProduct(&LS->mN, &LS->mP0)<-Radius && Vector2DDotProduct(&LS->mN, Pe) - Vector2DDotProduct(&LS->mN, &LS->mP0)<-Radius)
	{

		return -1.0f;
	}
	else if (Vector2DDotProduct(&LS->mN, Ps) - Vector2DDotProduct(&LS->mN, &LS->mP0)>Radius && Vector2DDotProduct(&LS->mN, Pe) - Vector2DDotProduct(&LS->mN, &LS->mP0)>Radius)
	{

		return -1.0f;
	}
	else if (Vector2DDotProduct(&temp_2, &vel_2) < 0)
	{

		return -1.0f;
	}
	else if (Vector2DDotProduct(&temp_1, &vel_1) < 0)
	{

		return -1.0f;
	}
	else if (Vector2DDotProduct(&LS->mN, &velocity) == 0)
	{

		return -1.0f;
	}

	
	else
	{


		return time;
	}
}


/*
This function reflects an animated point on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	Vector2D vec_i, vec_s;
	float time;
	
	time = AnimatedPointToStaticLineSegment(Ps, Pe, LS, Pi);

	if (time < 0)
	{
		return -1.0f;
	}
	else
	{
		
		Vector2DSub(&vec_i, Pe, Pi);

		Vector2DSet(&vec_s, LS->mN.x*Vector2DDotProduct(&vec_i, &LS->mN) * 2, LS->mN.y*Vector2DDotProduct(&vec_i, &LS->mN) * 2);
		Vector2DSub(R, &vec_i, &vec_s);
		return time;
	}
	
	
}


/*
This function reflects an animated circle on a line segment.
It should first make sure that the animated point is intersecting with the line 

 - Parameters
	- Ps:		The center's starting location
	- Pe:		The center's ending location
	- Radius:	The circle's radius
	- LS:		The line segment
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:				If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticLineSegment(Vector2D *Ps, Vector2D *Pe, float Radius, LineSegment2D *LS, Vector2D *Pi, Vector2D *R)
{
	Vector2D vec_i, vec_s;
	float time;

	time = AnimatedCircleToStaticLineSegment(Ps, Pe,Radius, LS, Pi);

	if (time < 0)
	{
		return -1.0f;
	}
	else
	{

		Vector2DSub(&vec_i, Pe, Pi);

		Vector2DSet(&vec_s, LS->mN.x*Vector2DDotProduct(&vec_i, &LS->mN) * 2, LS->mN.y*Vector2DDotProduct(&vec_i, &LS->mN) * 2);
		Vector2DSub(R, &vec_i, &vec_s);
		return time;
	}
}


/*
This function checks whether an animated point is colliding with a static circle

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedPointToStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi)
{
	float a, b, c, m, n, intersection_check, time, time_1, time_2;
	Vector2D velocity, BsC, intersection_Point, velocity_normalise;
	Vector2DSet(&velocity, Pe->x - Ps->x, Pe->y - Ps->y);
	Vector2DSet(&BsC, Center->x - Ps->x, Center->y - Ps->y);

	a = Vector2DDotProduct(&velocity, &velocity);
	b = Vector2DDotProduct(&BsC, &velocity)*(-2);
	c = Vector2DDotProduct(&BsC, &BsC) - Radius * Radius;


	Vector2DNormalize(&velocity_normalise, &velocity);
	m = Vector2DDotProduct(&BsC, &velocity_normalise);
	n = ((Center->x - Ps->x)*(Center->x - Ps->x) + (Center->y - Ps->y)*(Center->y - Ps->y)) - m * m;

	if (m < 0)
	{

		return -1.0f;
	}
	else if (n > Radius*Radius)
	{

		return -1.0f;
	}
	else
	{
		intersection_check = (b * b) - (4 * a*c);

		if (intersection_check == 0)
		{

			time = -b / (2 * a);
			Vector2DScaleAdd(&intersection_Point, &velocity, Ps, time);


			Vector2DSet(Pi, intersection_Point.x, intersection_Point.y);
			return time;
		}
		else if (intersection_check > 0)
		{

			time_1 = (float)(-b + sqrt(intersection_check)) / (2 * a);
			time_2 = (float)(-b - sqrt(intersection_check)) / (2 * a);
			if (time_1 > time_2)
			{
				time = time_2;
			}
			else
			{
				time = time_1;
			}


			Vector2DScaleAdd(&intersection_Point, &velocity, Ps, time);


			Vector2DSet(Pi, intersection_Point.x, intersection_Point.y);

			
			return time;

		}
		else
		{
			return -1;
		}

		
	}

	
	
	
}



/*
This function reflects an animated point on a static circle.
It should first make sure that the animated point is intersecting with the circle 

 - Parameters
	- Ps:		The point's starting location
	- Pe:		The point's ending location
	- Center:	The circle's center
	- Radius:	The circle's radius
	- Pi:		This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:		Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedPointOnStaticCircle(Vector2D *Ps, Vector2D *Pe, Vector2D *Center, float Radius, Vector2D *Pi, Vector2D *R)
{
	Vector2D n, m, temp, normalize_n, normalize_r, temp_norm_R, velosity;
	float time, velosity_length;
	Vector2DSet(&velosity, Pe->x - Ps->x, Pe->y - Ps->y);
	time =  AnimatedPointToStaticCircle(Ps, Pe, Center, Radius, Pi);


	if(time>=0&&time<=1)
	{
		
		
		velosity_length = Vector2DLength(&velosity);
		Vector2DSet(&n, Pi->x- Center->x  , Pi->y - Center->y );
		Vector2DSet(&m, Ps->x - Pi->x, Ps->y - Pi->y);
		 
		Vector2DNormalize(&normalize_n, &n);
	
		Vector2DScale(&temp, &normalize_n, Vector2DDotProduct(&m, &normalize_n) * 2);
		Vector2DSub(R, &temp, &m);
		Vector2DNormalize(&normalize_r, R);
		
		Vector2DScale(R, &normalize_r, velosity_length*(1 - time));
		//Vector2DAdd(Pe, Pi, &temp_norm_R);
		return time;
	}
	
	
}


/*
This function checks whether an animated circle is colliding with a static circle

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float AnimatedCircleToStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi)
{

	float a, b, c, m, n, intersection_check, time, time_1, time_2;
	Vector2D velocity, BsC, intersection_Point, velocity_normalise;
	Vector2DSet(&velocity, Center0e->x - Center0s->x, Center0e->y - Center0s->y);
	Vector2DSet(&BsC, Center1->x - Center0s->x, Center1->y - Center0s->y);

	a = Vector2DDotProduct(&velocity, &velocity);
	b = Vector2DDotProduct(&BsC, &velocity)*(-2);
	c = Vector2DDotProduct(&BsC, &BsC) - (Radius1+Radius0) * (Radius1 + Radius0);


	Vector2DNormalize(&velocity_normalise, &velocity);
	m = Vector2DDotProduct(&BsC, &velocity_normalise);
	n = ((Center1->x - Center0s->x)*(Center1->x - Center0s->x) + (Center1->y - Center0s->y)*(Center1->y - Center0s->y)) - m * m;

	if (m < 0)
	{

		return -1.0f;
	}
	else if (n > (Radius1 + Radius0) * (Radius1 + Radius0))
	{

		return -1.0f;
	}
	else
	{
		intersection_check = (b * b) - (4 * a*c);

		if (intersection_check == 0)
		{

			time = -b / (2 * a);
			Vector2DScaleAdd(&intersection_Point, &velocity, Center0s, time);


			Vector2DSet(Pi, intersection_Point.x, intersection_Point.y);
			return time;
		}
		else if (intersection_check > 0)
		{

			time_1 = (float)(-b + sqrt(intersection_check)) / (2 * a);
			time_2 = (float)(-b - sqrt(intersection_check)) / (2 * a);
			if (time_1 > time_2)
			{
				time = time_2;
			}
			else
			{
				time = time_1;
			}


			Vector2DScaleAdd(&intersection_Point, &velocity, Center0s, time);


			Vector2DSet(Pi, intersection_Point.x, intersection_Point.y);


			return time;

		}
		else
		{
			return -1;
		}


	}
	
}


/*
This function reflects an animated circle on a static circle.
It should first make sure that the animated circle is intersecting with the static one 

 - Parameters
	- Center0s:		The starting position of the animated circle's center 
	- Center0e:		The ending position of the animated circle's center 
	- Radius0:		The animated circle's radius
	- Center1:		The static circle's center
	- Radius1:		The static circle's radius
	- Pi:			This will be used to store the intersection point's coordinates (In case there's an intersection)
	- R:			Reflected vector R

 - Returned value: Intersection time t
	- -1.0f:		If there's no intersection
	- Intersection time:	If there's an intersection
*/
float ReflectAnimatedCircleOnStaticCircle(Vector2D *Center0s, Vector2D *Center0e, float Radius0, Vector2D *Center1, float Radius1, Vector2D *Pi, Vector2D *R)
{
	Vector2D n, m, temp, normalize_n, normalize_r, temp_norm_R, velosity;
	float time, velosity_length;
	Vector2DSet(&velosity, Center0e->x - Center0s->x, Center0e->y - Center0s->y);
	time = AnimatedCircleToStaticCircle(Center0s, Center0e, Radius0, Center1, Radius1, Pi);
	

	if (time >= 0 && time <= 1)
	{


		velosity_length = Vector2DLength(&velosity);
		Vector2DSet(&n, Pi->x - Center1->x, Pi->y - Center1->y);
		Vector2DSet(&m, Center0s->x - Pi->x, Center0s->y - Pi->y);

		Vector2DNormalize(&normalize_n, &n);

		Vector2DScale(&temp, &normalize_n, Vector2DDotProduct(&m, &normalize_n) * 2);
		Vector2DSub(R, &temp, &m);
		Vector2DNormalize(&normalize_r, R);

		Vector2DScale(R, &normalize_r, velosity_length*(1 - time));

		return time;
	}

}
