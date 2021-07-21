#include "stdafx.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "MVP.h"
#include "Shaders.h"
#include "Camera.h"
#include "../Utilities/Math.h"
#include "../Utilities/utilities.h"

MVP::MVP(Shaders Shader)
{
	mShader = Shader;
	rX.SetIdentity();
	rY.SetIdentity();
	rZ.SetIdentity();
	mScalingMatrix.SetIdentity();
	mRotationMatrix.SetIdentity();
	mTranslationMatrix.SetIdentity();
};

MVP::MVP() {};

void MVP::ScaleModel(Vector3 scaleVec)
{
	mScalingMatrix.SetScale(scaleVec);
};

void MVP::ScaleModel(GLfloat scale)
{
	mScalingMatrix.SetScale(scale);
};

void MVP::RotateModel(GLfloat aX, GLfloat aY, GLfloat aZ) 
{
	rX.SetRotationX(aX);
	rY.SetRotationY(aY);
	rZ.SetRotationZ(aZ);
	mRotationMatrix = rZ * rX * rY;
};

void MVP::TranslateModel(Vector3 translatorVec)
{
	mTranslationMatrix.SetTranslation(translatorVec);
};

void MVP::TranslateModel(GLfloat x, GLfloat y, GLfloat z)
{
	mTranslationMatrix.SetTranslation(x, y, z);
}
;

void MVP::transform()
{
	mWorldMatrix = mScalingMatrix * mRotationMatrix * mTranslationMatrix;
	GLint transLoc = glGetUniformLocation(mShader.program, "transform");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, *mWorldMatrix.m);
};

void MVP::transform(Matrix w, Matrix v, Matrix p)
{
	mWorldMatrix = w*v*p;
	mWorldMatrix = mWorldMatrix.Invert(mWorldMatrix);
	GLint transLoc = glGetUniformLocation(mShader.program, "transform");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, *mWorldMatrix.m);
}

void MVP::transform(Matrix v, Matrix p)
{
	mWorldMatrix = mScalingMatrix * mRotationMatrix * mTranslationMatrix;
	glUniformMatrix4fv(mShader.u_Model, 1, GL_FALSE, *mWorldMatrix.m);
	glUniformMatrix4fv(mShader.u_View, 1, GL_FALSE, *v.m);
	glUniformMatrix4fv(mShader.u_Projection, 1, GL_FALSE, *p.m);
}

