#pragma once
#include <cstdio>
#include <GLES2/gl2.h>
#include "MVP.h"
#include "../Utilities/Math.h"
#include "../Utilities/utilities.h"
class Camera
{
public:
	//MVP camMVP;
	float cameraSpeed = 1.0f;
	


	Vector3 cameraPos = Vector3(0.0f, 0.0f, 5.0f);
	Vector3 cameraTarget = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
	//Vector3 cameraDirection = (cameraPos - cameraTarget).Normalize();
	//Vector3 cameraRight = (up.Cross(cameraDirection)).Normalize();
	Matrix cameraView;

	Vector3 cameraFront = Vector3(0.0f, 0.0f, -1.0f);
	Vector3 cameraUp = Vector3(0.0f, 1.0f, 0.0f);
	//void SetCameraView();

	float mFOV = 1.0f;
	float mNear = 0.1f;
	float mFar = 1000.0f;

	void caseW();
	void caseA();
	void caseS();
	void caseD();
	Matrix GetPerspective();
	Matrix GetViewMatrix();
	Matrix GetWorldMatrix();
	void camWorld();

	//Camera(MVP mvp);
	Camera();
};

