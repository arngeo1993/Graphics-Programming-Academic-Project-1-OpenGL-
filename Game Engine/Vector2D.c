#include "Vector2D.h"

#define EPSILON 0.0001

////////////////////
// From Project 2 //
////////////////////

// ---------------------------------------------------------------------------

void Vector2DZero(Vector2D *pResult)
{
	pResult->x = 0;
	pResult->y = 0;
}

// ---------------------------------------------------------------------------

void Vector2DSet(Vector2D *pResult, float x, float y)
{
	pResult->x = x;
	pResult->y = y;
}

// ---------------------------------------------------------------------------

void Vector2DNeg(Vector2D *pResult, Vector2D *pVec0)
{
	pResult->x = (-1)*pVec0->x;
	pResult->y = (-1)*pVec0->y;
}

// ---------------------------------------------------------------------------

void Vector2DAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x + pVec1->x;
	pResult->y = pVec0->y + pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1)
{
	pResult->x = pVec0->x - pVec1->x;
	pResult->y = pVec0->y - pVec1->y;
}

// ---------------------------------------------------------------------------

void Vector2DNormalize(Vector2D *pResult, Vector2D *pVec0)
{
	float temp = (float) sqrt((pVec0->x*pVec0->x) + (pVec0->y*pVec0->y));

	pResult->x = pVec0->x / temp;
	pResult->y = pVec0->y / temp;
}

// ---------------------------------------------------------------------------

void Vector2DScale(Vector2D *pResult, Vector2D *pVec0, float c)
{
	pResult->x = pVec0->x * c;
	pResult->y = pVec0->y * c;
}

// ---------------------------------------------------------------------------

void Vector2DScaleAdd(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = (pVec0->x* c + pVec1->x);
	pResult->y = (pVec0->y* c + pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DScaleSub(Vector2D *pResult, Vector2D *pVec0, Vector2D *pVec1, float c)
{
	pResult->x = (pVec0->x* c - pVec1->x);
	pResult->y = (pVec0->y* c - pVec1->y);
}

// ---------------------------------------------------------------------------

float Vector2DLength(Vector2D *pVec0)
{
	float temp = (float) sqrt(pVec0->x*pVec0->x + pVec0->y * pVec0->y);
	return temp;
}

// ---------------------------------------------------------------------------

float Vector2DSquareLength(Vector2D *pVec0)
{
	return pVec0->x*pVec0->x + pVec0->y * pVec0->y;
}

// ---------------------------------------------------------------------------

float Vector2DDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return (float) sqrt((pVec0->x - pVec1->x)*(pVec0->x - pVec1->x) + (pVec0->y - pVec1->y)*(pVec0->y - pVec1->y));
}

// ---------------------------------------------------------------------------

float Vector2DSquareDistance(Vector2D *pVec0, Vector2D *pVec1)
{
	return (pVec0->x - pVec1->x)*(pVec0->x - pVec1->x) + (pVec0->y - pVec1->y)*(pVec0->y - pVec1->y);
}

// ---------------------------------------------------------------------------

float Vector2DDotProduct(Vector2D *pVec0, Vector2D *pVec1)
{
	return (pVec0->x * pVec1->x) + (pVec0->y * pVec1->y);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleDeg(Vector2D *pResult, float angle)
{
	pResult->x =(float) cos(angle / 0.0174533);
	pResult->y = (float)sin(angle / 0.0174533);
}

// ---------------------------------------------------------------------------

void Vector2DFromAngleRad(Vector2D *pResult, float angle)
{
	pResult->x = (float)cos(angle);
	pResult->y = (float)sin(angle);
}

// ---------------------------------------------------------------------------
