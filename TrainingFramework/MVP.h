#pragma once
#include <cstdio>
#include <GLES2/gl2.h>
#include "Shaders.h"
#include "Camera.h"
#include "../Utilities/Math.h"
#include "../Utilities/utilities.h"
class MVP
{
public:

	//Vector3 mTranslationVec = Vector3(0.0f, 0.0f, 0.0f);
	Matrix rX;
	Matrix rY;
	Matrix rZ;


	Matrix mRotationMatrix = mRotationMatrix.SetIdentity();
	Matrix mTranslationMatrix = mTranslationMatrix.SetIdentity();
	Matrix mScalingMatrix = mScalingMatrix.SetIdentity(); //= mScalingMatrix.SetScale(mScale);

	Matrix mWorldMatrix; //= mScalingMatrix * mRotationMatrix * mTranslationMatrix;
	//Vector4 mTransformedVec = mModelMatrix * originalVec;
	Shaders s;
	//Vector4 vec = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

	MVP(Shaders s);
	MVP();

	void RotateModel(GLfloat aX, GLfloat aY, GLfloat aZ);
	void ScaleModel(Vector3 scaleVec);
	void ScaleModel(GLfloat scale);
	void TranslateModel(Vector3 translateVec);
	void TranslateModel(GLfloat x, GLfloat y, GLfloat z);

	void transform();
	void transform(Matrix m1, Matrix m2, Matrix m3);
	void transform(Matrix v, Matrix p);
};

