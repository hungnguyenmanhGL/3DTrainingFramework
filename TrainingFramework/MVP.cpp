#include "stdafx.h"
#include <cstdio>
#include <GLES2/gl2.h>
#include "MVP.h"
#include "Shaders.h"
#include "../Utilities/Math.h"
#include "../Utilities/utilities.h"

MVP::MVP(Shaders mShader)
{
	s = mShader;
};

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
	GLint transLoc = glGetUniformLocation(s.program, "transform");
	glUniformMatrix4fv(transLoc, 1, GL_FALSE, *mWorldMatrix.m);
};
