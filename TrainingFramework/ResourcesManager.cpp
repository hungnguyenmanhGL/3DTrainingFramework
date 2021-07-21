#include "stdafx.h"
#include "ResourcesManager.h"
#include "Shaders.h"
#include "Globals.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "MVP.h"
#include "Math.h"
#include <vector>
#include <iostream>
using namespace std;

void ResourcesManager::LoadResourcesCount(FILE *file) 
{
	vector <Model> modelList;
	vector <Texture> textureList;
	vector <Shaders> shaderList;
	vector <char*> vsList;
	vector <char*> fsList;

	fscanf(file, "#Models: %d\n", &numModel);
	for (int i = 0; i < numModel; i++)
	{
		int id;
		char fileName[30];
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", &fileName);
		Model model = Model(fileName);
		modelList.push_back(model);
		cout << "Model file path: ";
		
		
	}

	fscanf(file, "#2D TEXTURE: %d\n", &numTexture);
	for (int i = 0; i < numTexture; i++)
	{
		int id;
		char fileName[30];
		char wrap[10], filter1[15], filter2[15];

		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", &fileName);
		Texture temp = Texture(fileName);
		fscanf(file, "WRAP %s\n", &wrap);
		
		if (strcmp(wrap, "REPEAT") == 0) temp.wrapMode = GL_REPEAT;
		fscanf(file, "FILTER %s %s\n", &filter1, &filter2);
		if (strcmp(filter1, "LINEAR") == 0); temp.filterMode = GL_LINEAR;
		if (strcmp(filter2, "LINEAR") == 0); temp.wrapMode = GL_LINEAR;
		textureList.push_back(temp);
	}

	fscanf(file, "#Shaders: %d\n", &numShader);
	for (int i = 0; i < numShader; i++)
	{
		char* vsName;
		char* fsName;
		int id, state;
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "VS %s\n", &vsName);
		fscanf(file, "FS %s\n", &fsName);

		vsList.push_back(vsName);
		fsList.push_back(fsName);
	}
}

void ResourcesManager::Init()
{
	FILE* file = fopen(mFilePath, "r");
	if (file != NULL)
	{
		LoadResourcesCount(file);
	}
	else std::cout << "Fail to load resource file!" << std::endl;
}
