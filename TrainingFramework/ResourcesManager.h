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
#include <GLES2/gl2.h>
class ResourcesManager
{
public:
	char* mFilePath;
	int numModel;
	int numTexture;
	int numCubeTexture;
	int numShader;

	void LoadResourcesCount(FILE* file);
	void Init();

	ResourcesManager(const char *filePath);
};

