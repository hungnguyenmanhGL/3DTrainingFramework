#pragma once
#include "stdafx.h"
#include "Camera.h"
#include "Globals.h"
#include <cstdio>
#include <iostream>
#include <GLES2/gl2.h>
#include "MVP.h"
#include "../Utilities/Math.h"
#include "../Utilities/utilities.h"

Camera::Camera()
{
	float aspect = (float)Globals::screenWidth / Globals::screenHeight;
	
	camPerspective.SetPerspective(mFOV, aspect, mNear, mFar);
	Update();
}

void Camera::Init()
{
	zaxis = (cameraPos - cameraTarget).Normalize();
	xaxis = (up.Cross(zaxis)).Normalize();
	yaxis = (zaxis.Cross(xaxis)).Normalize();
	GetWorldMatrix();
	GetViewMatrix();
	GetPerspective();
}

void Camera::Update()
{
	zaxis = (cameraPos - cameraTarget).Normalize();//cameraDirect
	xaxis = (up.Cross(zaxis)).Normalize();//cameraRight
	yaxis = (zaxis.Cross(xaxis)).Normalize();
}

void Camera::caseW(float deltaTime)
{
	Vector3 deltaMove = -(cameraPos - cameraTarget).Normalize() * deltaTime*2 * cameraSpeed;
	cameraPos += deltaMove;
	cameraTarget += deltaMove;
	//std::cout << "W";
}

void Camera::caseS(float deltaTime)
{
	Vector3 deltaMove = -(cameraPos - cameraTarget).Normalize() * deltaTime*2 * cameraSpeed;
	cameraPos -= deltaMove;
	cameraTarget -= deltaMove;
	//std::cout << "S";
}

void Camera::caseA(float deltaTime)
{
	Vector3 zaxis = (cameraPos - cameraTarget).Normalize();
	Vector3 deltaMove = -(up.Cross(zaxis)).Normalize() * deltaTime*2 * cameraSpeed;
	cameraPos += deltaMove;
	cameraTarget += deltaMove;
}

void Camera::caseD(float deltaTime)
{
	Vector3 zaxis = (cameraPos - cameraTarget).Normalize();
	Vector3 deltaMove = -(up.Cross(zaxis)).Normalize() * deltaTime*2 * cameraSpeed;
	cameraPos -= deltaMove;
	cameraTarget -= deltaMove;
}

Matrix Camera::GetPerspective()
{
	float aspect = (float)Globals::screenWidth / Globals::screenHeight;
	Matrix mPerspectiveMatrix;
	mPerspectiveMatrix.SetPerspective(mFOV, aspect, mNear, mFar);
	/*std::cout << "Check perspective matrix: " << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << mPerspectiveMatrix.m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	return camPerspective;
}


Matrix Camera::GetViewMatrix()
{
	Matrix view;
	view.m[0][0] = xaxis.x; view.m[1][0] = xaxis.y; view.m[2][0] = xaxis.z; view.m[3][0] = -cameraPos.Dot(xaxis);
	view.m[0][1] = yaxis.x; view.m[1][1] = yaxis.y; view.m[2][1] = yaxis.z; view.m[3][1] = -cameraPos.Dot(yaxis);
	view.m[0][2] = zaxis.x; view.m[1][2] = zaxis.y; view.m[2][2] = zaxis.z; view.m[3][2] = -cameraPos.Dot(zaxis);
	view.m[0][3] = 0;	    view.m[1][3] = 0;		view.m[2][3] = 0;		view.m[3][3] = 1;
	
	/*std::cout << "Check view: " << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << view.m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/
	return view;
}

Matrix Camera::GetWorldMatrix()
{
	Matrix w;
	w = w.Invert(GetViewMatrix());
	Matrix ma = w * GetViewMatrix();
	
	return w;
}

void Camera::RotateAroundX(GLfloat deltaTime) {
	Vector4 rotationAxis = Vector4(1, 0, 0, 0) * GetViewMatrix();
	float angle = deltaTime * cameraSpeed;
	Matrix rotation;
	rotation.SetIdentity();
	rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	Vector4 localTarget = Vector4(0, 0, -(cameraPos - cameraTarget).Length(), 1);
	Vector4 localNewTarget = localTarget * rotation;
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	cameraTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::RotateAroundY(float deltaTime) {
	Vector4 rotationAxis = Vector4(0, 1, 0, 0) * GetViewMatrix();
	float angle = deltaTime * cameraSpeed;
	Matrix rotation;
	rotation.SetIdentity();
	rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	Vector4 localTarget = Vector4(0, 0, -(cameraPos - cameraTarget).Length(), 1);
	Vector4 localNewTarget = localTarget * rotation;
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	cameraTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}

void Camera::RotateAroundZ(float deltaTime) {
	Vector4 rotationAxis = Vector4(0, 0, 1, 0) * GetViewMatrix();
	float angle = deltaTime * cameraSpeed;
	Matrix rotation;
	rotation.SetIdentity();
	rotation.SetRotationAngleAxis(angle, rotationAxis.x, rotationAxis.y, rotationAxis.z);
	Vector4 localTarget = Vector4(0, 0, -(cameraPos - cameraTarget).Length(), 1);
	Vector4 localNewTarget = localTarget * rotation;
	Vector4 worldNewTarget = localNewTarget * GetWorldMatrix();
	cameraTarget = Vector3(worldNewTarget.x, worldNewTarget.y, worldNewTarget.z);
}


