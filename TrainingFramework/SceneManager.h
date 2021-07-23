#pragma once
#include "../Utilities/utilities.h"
#include "Object.h"
#include "Camera.h"
class SceneManager
{
public:
	Camera camera;
	char* sceneManagerFile;
	int numberOfObject;

	vector <Object> objectList;
	SceneManager(char* file);
	void Init();
	void InitSceneManager();
	void Draw(Shaders myShaders);

	//static SceneManager* s_Instance;
	//static SceneManager* GetInstance(char* file);
};
