#include "Matrix2D.h"

////////////////////
// From project 2 //
////////////////////

/*
This function sets the matrix Result to the identity matrix
*/
void Matrix2DIdentity(Matrix2D *pResult)
{
	memset(pResult, 0, 9 * sizeof(float));

	pResult->m[0][0] = 1;
	pResult->m[1][1] = 1;
	pResult->m[2][2] = 1;

}

// ---------------------------------------------------------------------------

/*
This functions calculated the transpose matrix of Mtx and saves it in Result
*/
void Matrix2DTranspose(Matrix2D *pResult, Matrix2D *pMtx)
{

	float temp[3][3];

	for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			temp[j][i] = pMtx->m[i][j];
		}
	}
	pResult->m[0][0] = temp[0][0];
	pResult->m[0][1] = temp[0][1];
	pResult->m[0][2] = temp[0][2];

	pResult->m[1][0] = temp[1][0];
	pResult->m[1][1] = temp[1][1];
	pResult->m[1][2] = temp[1][2];

	pResult->m[2][0] = temp[2][0];
	pResult->m[2][1] = temp[2][1];
	pResult->m[2][2] = temp[2][2];








}

// ---------------------------------------------------------------------------

/*
This function multiplies Mtx0 with Mtx1 and saves the result in Result
Result = Mtx0*Mtx1
*/
void Matrix2DConcat(Matrix2D *pResult, Matrix2D *pMtx0, Matrix2D *pMtx1)
{

	float temp[3][3];


	temp[0][0] = pMtx0->m[0][0] * pMtx1->m[0][0] + pMtx0->m[0][1] * pMtx1->m[1][0] + pMtx0->m[0][2] * pMtx1->m[2][0];
	temp[0][1] = pMtx0->m[0][0] * pMtx1->m[0][1] + pMtx0->m[0][1] * pMtx1->m[1][1] + pMtx0->m[0][2] * pMtx1->m[2][1];
	temp[0][2] = pMtx0->m[0][0] * pMtx1->m[0][2] + pMtx0->m[0][1] * pMtx1->m[1][2] + pMtx0->m[0][2] * pMtx1->m[2][2];

	temp[1][0] = pMtx0->m[1][0] * pMtx1->m[0][0] + pMtx0->m[1][1] * pMtx1->m[1][0] + pMtx0->m[1][2] * pMtx1->m[2][0];
	temp[1][1] = pMtx0->m[1][0] * pMtx1->m[0][1] + pMtx0->m[1][1] * pMtx1->m[1][1] + pMtx0->m[1][2] * pMtx1->m[2][1];
	temp[1][2] = pMtx0->m[1][0] * pMtx1->m[0][2] + pMtx0->m[1][1] * pMtx1->m[1][2] + pMtx0->m[1][2] * pMtx1->m[2][2];

	temp[2][0] = pMtx0->m[2][0] * pMtx1->m[0][0] + pMtx0->m[2][1] * pMtx1->m[1][0] + pMtx0->m[2][2] * pMtx1->m[2][0];
	temp[2][1] = pMtx0->m[2][0] * pMtx1->m[0][1] + pMtx0->m[2][1] * pMtx1->m[1][1] + pMtx0->m[2][2] * pMtx1->m[2][1];
	temp[2][2] = pMtx0->m[2][0] * pMtx1->m[0][2] + pMtx0->m[2][1] * pMtx1->m[1][2] + pMtx0->m[2][2] * pMtx1->m[2][2];

	pResult->m[0][0] = temp[0][0];
	pResult->m[0][1] = temp[0][1];
	pResult->m[0][2] = temp[0][2];

	pResult->m[1][0] = temp[1][0];
	pResult->m[1][1] = temp[1][1];
	pResult->m[1][2] = temp[1][2];

	pResult->m[2][0] = temp[2][0];
	pResult->m[2][1] = temp[2][1];
	pResult->m[2][2] = temp[2][2];



}

// ---------------------------------------------------------------------------

/*
This function creates a translation matrix from x & y and saves it in Result
*/
void Matrix2DTranslate(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);

	pResult->m[0][2] = x;
	pResult->m[1][2] = y;




}

// ---------------------------------------------------------------------------

/*
This function creates a scaling matrix from x & y and saves it in Result
*/
void Matrix2DScale(Matrix2D *pResult, float x, float y)
{
	Matrix2DIdentity(pResult);

	pResult->m[0][0] = x;
	pResult->m[1][1] = y;



}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in degree.
Save the resultant matrix in Result
*/
void Matrix2DRotDeg(Matrix2D *pResult, float Angle)
{

	Matrix2DIdentity(pResult);


	pResult->m[0][0] = (float)cos(Angle / 0.0174533);
	pResult->m[1][0] = (float)sin(Angle / 0.0174533);
	pResult->m[0][1] = (float)-sin(Angle / 0.0174533);
	pResult->m[1][1] = (float)cos(Angle / 0.0174533);




}

// ---------------------------------------------------------------------------

/*
This matrix creates a rotation matrix from "Angle" whose value is in radian.
Save the resultant matrix in Result
*/
void Matrix2DRotRad(Matrix2D *pResult, float Angle)
{

	Matrix2DIdentity(pResult);

	pResult->m[0][0] = (float)cos(Angle);
	pResult->m[1][0] = (float)sin(Angle);
	pResult->m[0][1] = (float)-sin(Angle);
	pResult->m[1][1] = (float)cos(Angle);




}

// ---------------------------------------------------------------------------

/*
This function multiplies the matrix Mtx with the vector Vec and saves the result in Result
Result = Mtx * Vec
*/
void Matrix2DMultVec(Vector2D *pResult, Matrix2D *pMtx, Vector2D *pVec)
{

	float temp_x = pVec->x, temp_y = pVec->y;

	pResult->x = (pMtx->m[0][0] * temp_x) + (pMtx->m[0][1] * temp_y) + (pMtx->m[0][2] * 1);

	pResult->y = (pMtx->m[1][0] * temp_x) + (pMtx->m[1][1] * temp_y) + (pMtx->m[1][2] * 1);





}


// ---------------------------------------------------------------------------
