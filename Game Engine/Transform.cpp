#include "Transform.h"
#include<iostream>
#include <glm/glm.hpp>
#include "Vector2D.h"
#include "Matrix2D.h"
extern float SCR_WIDTH;
extern float SCR_HEIGHT;
Transform::Transform() : Component(TRANSFORM) {
	mPosX = mPosY = 0.0;
}
Transform::~Transform() {}

void Transform::Update()
{
	

	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(mPosX, mPosY, 0.0f));

	glm::mat4 scale;
	
	scale = glm::scale(scale, glm::vec3(mScaleX, mScaleY, 0.0f));

	glm::mat4 rotate;
	rotate = glm::rotate(rotate, mAngle, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 intermediate;
	intermediate = scale * rotate;

	mpTransform = trans * intermediate;
	mpTransform_bounding_box = trans * scale;
}


void Transform::Serialize(FILE **fpp)
{
	
	fscanf_s(*fpp, "%f %f %i\n  ", &mPosX, &mPosY,&backBround_Val);
	fscanf_s(*fpp, "%f %f\n  ", &mScaleX, &mScaleY);
	if (backBround_Val == 1)
	{
		
		mPosX =  SCR_WIDTH/2;
		mPosY =  SCR_HEIGHT/2;
		mScaleX = SCR_WIDTH;
		mScaleY = SCR_HEIGHT;
	}
	
	
	fscanf_s(*fpp, "%f\n  ", &mAngle);
	
}
