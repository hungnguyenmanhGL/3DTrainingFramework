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

Shaders skyShader;
Texture skyBox;
Model skyBoxModel = Model("../Resources/Models/SkyBox.nfg");
Object o; 

MVP mvp = MVP();
Camera camera = Camera();
vector <char*> faces;

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	//Init resources
	rm.Init();
	//sm.InitSceneManager();
	//sm.Init();

	skyBoxModel = Model("../Resources/Models/SkyBox.nfg");
	//skyBoxModel.Init();
	//glBindBuffer(GL_ARRAY_BUFFER, skyBoxModel.mVBO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBoxModel.mIBO);

	o.oModel = skyBoxModel;
	o.oModel.Init();
	o.oModel.Bind();

	faces.push_back("../Resources/Skybox Textures/back.tga");
	faces.push_back("../Resources/Skybox Textures/bottom.tga");
	faces.push_back("../Resources/Skybox Textures/front.tga");
	faces.push_back("../Resources/Skybox Textures/left.tga");
	faces.push_back("../Resources/Skybox Textures/right.tga");
	faces.push_back("../Resources/Skybox Textures/top.tga");
	//skyBox.cubeInit(faces);

	o.oTexture.push_back(skyBox);
	o.oTexture.at(0).cubeInit(faces);
	glBindTexture(GL_TEXTURE_CUBE_MAP, o.oTexture.at(0).mTextureId);//skyBox



	skyShader.Init("../Resources/Shaders/CubeShaderVS.vs", "../Resources/Shaders/CubeShaderFS.fs");
	
	glEnable(GL_DEPTH_TEST);
	
	//return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");
}

void Draw(ESContext* esContext)
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glUseProgram(skyShader.program);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, skyBox.mTextureId);
	//glBindBuffer(GL_ARRAY_BUFFER, skyBoxModel.mVBO);

	////sm.Draw(myShaders);

	//if (skyShader.positionAttribute != -1)
	//{
	//	glEnableVertexAttribArray(skyShader.positionAttribute);
	//	glVertexAttribPointer(skyShader.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//}
	//if (skyShader.colorAttribute != -1)
	//{
	//	glEnableVertexAttribArray(skyShader.colorAttribute);
	//	glVertexAttribPointer(skyShader.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Vector3));
	//}

	//if (skyShader.uvAttribute != -1)
	//{
	//	glUniform1i(skyShader.textureUniform, 0);
	//	glEnableVertexAttribArray(skyShader.uvAttribute);
	//	glVertexAttribPointer(skyShader.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2 * sizeof(Vector3)));
	//}
	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyBoxModel. mIBO);
	o.DrawCube(skyShader);

	mvp = MVP(skyShader);
	mvp.ScaleModel(200.0f);
	mvp.RotateModel(0.0, 0.0, 0.0);
	mvp.TranslateModel(0.0, 0.0, 0.0);
	mvp.transform(camera.GetViewMatrix(), camera.GetPerspective());

	//glDrawElements(GL_TRIANGLES, skyBoxModel.mNumberOfIndices, GL_UNSIGNED_INT, 0);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/*glUniformMatrix4fv(skyShader.u_Projection, 1, GL_FALSE, *sm.camera.GetPerspective().m);
	glUniformMatrix4fv(skyShader.u_View, 1, GL_FALSE, *sm.camera.GetViewMatrix().m);*/
	
	/*for (int i = 0; i < sm.objectList.size(); i++) {

		
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
		camera.caseW(deltaTime);
	}

	if (keyPressed & MOVE_BACKWARD) {
		camera.caseS(deltaTime);
	}

	if (keyPressed & MOVE_LEFT) {
		camera.caseA(deltaTime);
	}

	if (keyPressed & MOVE_RIGHT) {
		camera.caseD(deltaTime);
	}

	if (keyPressed & ROTATE_X_UP) {
		camera.RotateAroundX(deltaTime);
	}

	if (keyPressed & ROTATE_X_DOWN) {
		camera.RotateAroundX(-deltaTime);
	}

	if (keyPressed & ROTATE_Y_LEFT) {
		camera.RotateAroundY(deltaTime);
	}

	if (keyPressed & ROTATE_Y_RIGHT) {
		camera.RotateAroundY(-deltaTime);
	}

	if (keyPressed & ROTATE_Z) {
		camera.RotateAroundZ(deltaTime);
	}
	camera.Update();
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
	skyBox.~Texture();
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



