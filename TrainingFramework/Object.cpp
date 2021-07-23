#include "stdafx.h"
#include "Vertex.h"
#include "Object.h"
#include "stdafx.h"
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
#include "ResourcesManager.h"
#include "Camera.h"
#include "MVP.h"
#include <iostream>
#include "Object.h"
Matrix Object::SetRotation()
{
	Rx.SetRotationX(oRotation.x);
	Ry.SetRotationY(oRotation.y);
	Rz.SetRotationZ(oRotation.z);
	return Rz * Rx * Ry;
}
Matrix Object::SetWorldMatrix()
{
	return Scale * Rotation * Translation;
}
Object::Object(Model model, vector <Texture> texture, Shaders shaders, int id)
{
	oModel = model;
	oTexture = texture;
	oShaders = shaders;
	this->id = id;
}

void Object::InitObject()
{
	Translation.SetTranslation(oPos);
	Scale.SetScale(oScale);
	Rotation = SetRotation();
	WorldMatrix = SetWorldMatrix();
	for (int i = 0; i < oTexture.size(); i++)
	{
		oTexture.at(i).Init();
	}

}

Object::Object(Object *o)
{
	oModel = o->oModel;
	oTexture = o->oTexture;
	oShaders = o->oShaders;
	id = o->id;

	oPos = o->oPos;
	oRotation = o->oRotation;
	oScale = o->oScale;
	Scale = o->Scale;
	Rotation = o->Rotation;
	Translation = o->Translation;

	Rx = o->Rx;
	Ry = o->Ry;
	Rz = o->Rz;
	
	Translation.SetTranslation(o->oPos);
	Rotation = SetRotation();
	Scale.SetScale(o->oScale);
}

Object::Object()
{

}

void Object::Draw(Shaders myShaders)
{
	glUseProgram(myShaders.program);
	oModel.Bind();
	glBindTexture(GL_TEXTURE_2D, oTexture.at(0).mTextureId);

	if (myShaders.positionAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.positionAttribute);
		glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}
	if (myShaders.colorAttribute != -1)
	{
		glEnableVertexAttribArray(myShaders.colorAttribute);
		glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	}

	if (myShaders.uvAttribute != -1)
	{
		glUniform1i(myShaders.textureUniform, 0);
		glEnableVertexAttribArray(myShaders.uvAttribute);
		glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	}

	glUniformMatrix4fv(myShaders.u_Model, 1, GL_FALSE, *WorldMatrix.m);

	oModel.Draw();
	oModel.Unbind();
	glBindTexture(GL_TEXTURE_2D, 0);
}