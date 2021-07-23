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

	fscanf(file, "#Models: %d\n", &numModel);
	for (int i = 0; i < numModel; i++)
	{
		int id;
		float scale = 1, offset=0;
		char fileName[30];
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", &fileName);
		fscanf(file, "SCALE %f\n", &scale);
		fscanf(file, "OFFSET %f\n", &offset);
		Model model = Model(fileName);
		modelList.push_back(model);
		//cout << "Model file path: " << modelList.at(i).mModelFilePath << endl;
	}

	fscanf(file, "#2D Textures: %d\n", &numTexture);
	//cout << numTexture << endl;
	for (int i = 0; i < numTexture; i++)
	{
		int id;
		char fileName[50];
		char wrap[10], filter1[15], filter2[15];

		fscanf(file, "ID %d\n", &id);
		fscanf(file, "FILE %s\n", &fileName);
		Texture temp = Texture(fileName);
		fscanf(file, "WRAP %s\n", &temp.wrapMode);
		
		//if (strcmp(wrap, "REPEAT") == 0) temp.wrapMode = wrap;
		fscanf(file, "FILTER %s %s\n", &temp.filterMin, &temp.filterMag);
		
		textureList.push_back(temp);
	}

	/*for (int i = 0; i < numTexture; i++) {
		cout << "Texture file path " << i << ": " << textureList.at(i).mTgaFilePath 
			<< " " << textureList.at(i).wrapMode << " " << textureList.at(i).filterMin << " " << textureList.at(i).filterMag << endl;
	}*/

	fscanf(file, "#Cube Textures: %d\n", &numCubeTexture);
	//cout << numCubeTexture << endl;
	for (int i = 0; i < numCubeTexture; i++)
	{
		int cubeId;
		char cubeFilePath[30];
		char wrapMode[10];
		char filterMode[10];
		char filter2[10];
		
		fscanf(file, "ID %d\n", &cubeId);
		fscanf(file, "FILE %s\n", &cubeFilePath);
		fscanf(file, "WRAP %s\n", &wrapMode);
		fscanf(file, "FILTER %s %s\n", &filterMode, &filter2);

		//cout << cubeFilePath << " " << wrapMode << " " << filterMode << " " << filter2 << endl;
	}

	fscanf(file, "#Shaders: %d\n", &numShader);
	//cout << numShader << endl;
	for (int i = 0; i < numShader; i++)
	{
		Shaders temp = Shaders();
		char vsName[40];
		char fsName[40];
		int id, state;
		fscanf(file, "ID %d\n", &id);
		fscanf(file, "VS %s\n", &temp.fileVS);
		fscanf(file, "FS %s\n", &temp.fileFS);

		shaderList.push_back(temp);
		fscanf(file, "STATES %d\n", &state);
		
		if (state == 2) {
			int depthTest, cullFace;
			fscanf(file, "GL_DEPTH_TEST %d\n", &depthTest);
			fscanf(file, "GL_CULL_FACE %d\n", &cullFace);
		}
		if (state == 3) {
			int depthTest, cullFace, blend;
			char srcAlpha[50];
			fscanf(file, "GL_DEPTH_TEST %d\n", &depthTest);
			fscanf(file, "GL_CULL_FACE %d\n", &cullFace);
			fscanf(file, "GL_BLEND %d\n", &blend);
			fscanf(file, "GL_SRC_ALPHA %s\n", &srcAlpha);
		}
		//cout << vsList.at(i) << " " << fsList.at(i) << endl;
	}

	/*for (int i = 0; i < numShader; i++) {
		cout << shaderList.at(i).fileVS << " " << shaderList.at(i).fileFS << endl;
	}*/

	fclose(file);
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

Model ResourcesManager::getModel(int id)
{
	return modelList.at(id);
}

Texture ResourcesManager::getTexture(int id)
{
	return textureList.at(id);
}

Shaders ResourcesManager::getShader(int id)
{
	return shaderList.at(id);
}

ResourcesManager::ResourcesManager(char* filePath)
{
	mFilePath = filePath;
}

//void ResourcesManager::Check() {
//	cout << modelList.at(0).mModelFilePath << " " << textureList.at(0).mTgaFilePath << " " << shaderList.size() << endl;
//}
 