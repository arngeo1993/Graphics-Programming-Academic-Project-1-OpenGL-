#pragma once
#include "Vector2D.h"
#include "Matrix2D.h"
#include "Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transform : public Component {
public:
	Transform();
	~Transform();

	void Update();
	
	void Serialize(FILE **fpp);
public:
	float mPosX;
	float mPosY;
	
	float mScaleX, mScaleY;
	float mAngle;

	int backBround_Val;
	glm::mat4 mpTransform;
	glm::mat4 mpTransform_bounding_box;

};