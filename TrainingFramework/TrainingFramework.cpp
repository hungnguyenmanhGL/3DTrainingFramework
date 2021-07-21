// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "MVP.h"
#include "Math.h"
#include <conio.h>
#include <iostream>
#include <GLES2/gl2.h>


#define MOVE_FORWARD 1
#define MOVE_BACKWARD 1 << 1
#define MOVE_LEFT 1 << 2
#define MOVE_RIGHT 1 << 3
#define ROTATE_X_UP 1 << 4
#define ROTATE_Y_LEFT 1 << 5
#define ROTATE_Z 1 << 6
#define ROTATE_X_DOWN 1 << 7
#define ROTATE_Y_RIGHT 1 << 8

int keyPressed = 0;

GLuint vboId, iboId;
Shaders myShaders;
Texture* textureWoman;
Model* modelWoman;
MVP *mvp = new MVP(myShaders);
Camera cam = Camera();


int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ARRAY_BUFFER, iboId);
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
	
	//cam.GetViewMatrix();
	//cam.GetWorldMatrix();
	//creation of shaders and program 
	
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw(ESContext* esContext)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUseProgram(myShaders.program);
	glBindTexture(GL_TEXTURE_2D, textureWoman->mTextureId);
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
	mvp->transform(cam.GetViewMatrix(), cam.GetPerspective());//CameraWorld Transform
	delete mvp;
	glDrawElements(GL_TRIANGLES, modelWoman->mNumberOfIndices, GL_UNSIGNED_INT, 0);
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	if (keyPressed & MOVE_FORWARD) {
		cam.caseW(deltaTime);
	}

	if (keyPressed & MOVE_BACKWARD) {
		cam.caseS(deltaTime);
	}

	if (keyPressed & MOVE_LEFT) {
		cam.caseA(deltaTime);
	}

	if (keyPressed & MOVE_RIGHT) {
		cam.caseD(deltaTime);
	}

	if (keyPressed & ROTATE_X_UP) {
		cam.RotateAroundX(deltaTime);
	}

	if (keyPressed & ROTATE_X_DOWN) {
		cam.RotateAroundX(-deltaTime);
	}

	if (keyPressed & ROTATE_Y_LEFT) {
		cam.RotateAroundY(deltaTime);
	}

	if (keyPressed & ROTATE_Y_RIGHT) {
		cam.RotateAroundY(-deltaTime);
	}

	if (keyPressed & ROTATE_Z) {
		cam.RotateAroundZ(deltaTime);
	}
	cam.Update();
}

void Key(ESContext* esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		if (key == 'W') {
			keyPressed = keyPressed | MOVE_FORWARD;
			return;
		}

		if (key == 'S') {
			keyPressed = keyPressed | MOVE_BACKWARD;
			return;
		}

		if (key == 'A') {
			keyPressed = keyPressed | MOVE_LEFT;
			return;
		}
		if (key == 'D') {
			keyPressed = keyPressed | MOVE_RIGHT;
			return;
		}
		if (key == VK_UP) {
			keyPressed = keyPressed | ROTATE_X_UP;
			return;
		}
		if (key == VK_DOWN) {
			keyPressed = keyPressed | ROTATE_X_DOWN;
		}

		if (key == VK_LEFT) {
			keyPressed = keyPressed | ROTATE_Y_LEFT;
			return;
		}
		if (key == VK_RIGHT) {
			keyPressed = keyPressed | ROTATE_Y_RIGHT;
			return;
		}

		if (key == 'z' || key == 'Z') {
			keyPressed = keyPressed | ROTATE_Z;
			return;
		}
	}
	else {
		if (key == 'W') {
			keyPressed = keyPressed ^ MOVE_FORWARD;
			return;
		}

		if (key == 'S') {
			keyPressed = keyPressed ^ MOVE_BACKWARD;
			return;
		}

		if (key == 'A') {
			keyPressed = keyPressed ^ MOVE_LEFT;
			return;
		}
		if (key == 'D') {
			keyPressed = keyPressed ^ MOVE_RIGHT;
			return;
		}
		if (key == VK_UP ) {
			keyPressed = keyPressed ^ ROTATE_X_UP;
			return;
		}
		if (key == VK_DOWN) {
			keyPressed = keyPressed ^ ROTATE_X_DOWN;
		}
		if (key == VK_LEFT) {
			keyPressed = keyPressed ^ ROTATE_Y_LEFT;
			return;
		}
		if (key == VK_RIGHT) {
			keyPressed = keyPressed ^ ROTATE_Y_RIGHT;
			return;
		}
		if (key == 'z' || key == 'Z') {
			keyPressed = keyPressed ^ ROTATE_Z;
			return;
		}
	}
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



