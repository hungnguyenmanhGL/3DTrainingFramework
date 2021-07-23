#pragma once
#include "stdafx.h"
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
#include <vector>
#include <GLES2/gl2.h>
using namespace std;
class ResourcesManager
{
public:
	char* mFilePath;
	int numModel;
	int numTexture;
	int numCubeTexture;
	int numShader;

	vector<Model> modelList;
	vector<Texture> textureList;
	vector <Shaders> shaderList;

	void LoadResourcesCount(FILE* file);
	void Init();

	Model getModel(int id);
	Texture getTexture(int id);
	Shaders getShader(int id);

	ResourcesManager(char *filePath);
	void Check();
};

