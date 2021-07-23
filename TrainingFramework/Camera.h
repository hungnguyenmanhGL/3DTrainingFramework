#pragma once
#include <cstdio>
#include <GLES2/gl2.h>
#include "MVP.h"
#include "../Utilities/Math.h"
#include "../Utilities/utilities.h"
class Camera
{
public:

	float cameraSpeed = 0.1f;
	float rotationSpeed;
	float mFOV = 1.0f;
	float mNear = 0.1f;
	float mFar = 1000.0f;
	Vector3 xaxis, yaxis, zaxis;

	int id;
	Vector3 cameraPos = Vector3(0.0f, 0.0f, 3.0f);
	Vector3 cameraTarget = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	//Vector3 cameraDirection = (cameraPos - cameraTarget).Normalize();
	//Vector3 cameraRight = (up.Cross(cameraDirection)).Normalize();
	Matrix camViewMatrix;//V
	Matrix R;
	Matrix T;
	Matrix camPerspective;


	void caseW(float deltaTime);
	void caseA(float deltaTime);
	void caseS(float deltaTime);
	void caseD(float deltaTime);
	void RotateAroundX(float deltaTime);
	void RotateAroundY(float deltaTime);
	void RotateAroundZ(float deltaTime);
	void Update();
	void Init();

	Matrix GetPerspective();
	Matrix GetViewMatrix();
	Matrix GetWorldMatrix();

	Camera();
};

