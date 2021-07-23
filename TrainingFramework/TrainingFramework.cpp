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
#include "ResourcesManager.h"
#include "SceneManager.h"
#include "Object.h"
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

ResourcesManager rm = ResourcesManager("../Resources/RM1.txt");
SceneManager sm = SceneManager("../Resources/SM1.txt");

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	//Init resources
	rm.Init();
	sm.InitSceneManager();
	sm.Init();
	
	
	//Textures
	glEnable(GL_DEPTH_TEST);
	
	//return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	return myShaders.Init(rm.getShader(0).fileVS, rm.getShader(0).fileFS);
}

void Draw(ESContext* esContext)
{	
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	sm.Draw(myShaders);
	/*glUniformMatrix4fv(myShaders.u_Projection, 1, GL_FALSE, *cam.GetPerspective().m);
	glUniformMatrix4fv(myShaders.u_View, 1, GL_FALSE, *cam.GetViewMatrix().m);
	
	for (int i = 0; i < sm.objectList.size(); i++) {

		
		sm.objectList.at(i).Draw(myShaders);

	}*/


	//glBindTexture(GL_TEXTURE_2D, 0);
	/*glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*///Unbind()
	
	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext* esContext, float deltaTime)
{
	if (keyPressed & MOVE_FORWARD) {
		sm.camera.caseW(deltaTime);
	}

	if (keyPressed & MOVE_BACKWARD) {
		sm.camera.caseS(deltaTime);
	}

	if (keyPressed & MOVE_LEFT) {
		sm.camera.caseA(deltaTime);
	}

	if (keyPressed & MOVE_RIGHT) {
		sm.camera.caseD(deltaTime);
	}

	if (keyPressed & ROTATE_X_UP) {
		sm.camera.RotateAroundX(deltaTime);
	}

	if (keyPressed & ROTATE_X_DOWN) {
		sm.camera.RotateAroundX(-deltaTime);
	}

	if (keyPressed & ROTATE_Y_LEFT) {
		sm.camera.RotateAroundY(deltaTime);
	}

	if (keyPressed & ROTATE_Y_RIGHT) {
		sm.camera.RotateAroundY(-deltaTime);
	}

	if (keyPressed & ROTATE_Z) {
		sm.camera.RotateAroundZ(deltaTime);
	}
	sm.camera.Update();
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
	//delete textureWoman;
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



