// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Texture.h"
#include "Model.h"
#include "MVP.h"
#include "Math.h"
#include <conio.h>
#include <iostream>
#include <GLES2/gl2.h>

GLuint vboId, iboId;
Shaders myShaders;
Texture* textureWoman;
Model* modelWoman;
MVP* mvp;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(verticesData), verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ARRAY_BUFFER, iboId);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Textures
	textureWoman = new Texture("../Resources/Woman1.tga");
	textureWoman->Init();
	glBindTexture(GL_TEXTURE_2D, textureWoman->mTextureId);
	
	glEnable(GL_DEPTH_TEST);

	//task 4 load
	modelWoman = new Model("../Resources/Woman1.nfg");
	modelWoman->Init();
	glBindBuffer(GL_ARRAY_BUFFER, modelWoman->mVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelWoman->mIBO);


	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw(ESContext* esContext)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(myShaders.program);
	glBindTexture(GL_TEXTURE_2D, textureWoman->mTextureId);
	//glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, modelWoman->mVBO);

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
	
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelWoman->mIBO);
	mvp = new MVP(myShaders);
	mvp->RotateModel(0.0f,3.14f, 3.14f);
	mvp->ScaleModel(0.8f);
	//mvp->TranslateModel(1.0f, 1.0f, 0.0f);
	mvp->transform();
	glDrawElements(GL_TRIANGLES, modelWoman->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	delete mvp;
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{

}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{

}

void CleanUp()
{
	glDeleteBuffers(1, &vboId);
	glDeleteBuffers(1, &iboId);
	delete modelWoman;
	delete textureWoman;
}

int _tmain(int argc, TCHAR* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);

	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}



