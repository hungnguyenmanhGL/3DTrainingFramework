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

}

//Camera::Camera(MVP mvp)
//{
//	camMVP = mvp;
//}

void Camera::camWorld()
{
	Matrix mx = GetWorldMatrix() * GetViewMatrix() * GetPerspective();
	std::cout << "World Cam Matrix: " << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << mx.m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Camera::caseW()
{
	Vector3 deltaMove = -(cameraPos - cameraTarget).Normalize() * 0.2f * cameraSpeed;
	cameraPos += deltaMove;
	cameraTarget += deltaMove;
	std::cout << "W";
}

void Camera::caseS()
{
	Vector3 deltaMove = -(cameraPos - cameraTarget).Normalize() * 0.2f * cameraSpeed;
	cameraPos -= deltaMove;
	cameraTarget -= deltaMove;
	std::cout << "S";
}

void Camera::caseA()
{
	Vector3 zaxis = (cameraPos - cameraTarget).Normalize();
	Vector3 deltaMove = -(up.Cross(zaxis)).Normalize() * 0.2f * cameraSpeed;
	cameraPos -= deltaMove;
	cameraTarget -= deltaMove;
}

void Camera::caseD()
{
	Vector3 zaxis = (cameraPos - cameraTarget).Normalize();
	Vector3 deltaMove = -(up.Cross(zaxis)).Normalize() * 0.2f * cameraSpeed;
	cameraPos += deltaMove;
	cameraTarget += deltaMove;
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

	return mPerspectiveMatrix;
}

Matrix Camera::GetViewMatrix()
{
	Matrix mViewMatrix;
	Vector3 xaxis, yaxis, zaxis;
	zaxis = (cameraPos - cameraTarget).Normalize();//cameraDirect
	xaxis = (up.Cross(zaxis)).Normalize();//cameraRight
	yaxis = (zaxis.Cross(xaxis)).Normalize();

	mViewMatrix.m[0][0] = xaxis.x;
	mViewMatrix.m[0][1] = yaxis.x;
	mViewMatrix.m[0][2] = zaxis.x;
	mViewMatrix.m[0][3] = 0;

	mViewMatrix.m[1][0] = xaxis.y;
	mViewMatrix.m[1][1] = yaxis.y;
	mViewMatrix.m[1][2] = zaxis.y;
	mViewMatrix.m[1][3] = 0;

	mViewMatrix.m[2][0] = xaxis.z;
	mViewMatrix.m[2][1] = yaxis.z;
	mViewMatrix.m[2][2] = zaxis.z;
	mViewMatrix.m[2][3] = 0;

	mViewMatrix.m[3][0] = -cameraPos.Dot(xaxis);
	mViewMatrix.m[3][1] = -cameraPos.Dot(yaxis);
	mViewMatrix.m[3][2] = -cameraPos.Dot(zaxis);
	mViewMatrix.m[3][3] = 1;

	/*for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << mViewMatrix.m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	return mViewMatrix;
}

Matrix Camera::GetWorldMatrix()
{
	Matrix mWorldMatrix;
	mWorldMatrix = mWorldMatrix.Invert(GetViewMatrix());
	
	/*Matrix ma = mWorldMatrix * GetViewMatrix();
	std::cout << "Check validity: " << std::endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			std::cout << ma.m[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;*/

	return mWorldMatrix;
}


