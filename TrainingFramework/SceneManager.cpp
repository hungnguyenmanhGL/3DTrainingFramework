#include "stdafx.h"
#include "SceneManager.h"
#include "stdafx.h"
#include "SceneManager.h"
#include "ResourcesManager.h"
#include <iostream>
//SceneManager* SceneManager::s_Instance = NULL;
SceneManager::SceneManager(char* filePath)
{
	sceneManagerFile = filePath;
}

//SceneManager* SceneManager::GetInstance(char* file)
//{
//	if (!s_Instance)
//		s_Instance = new SceneManager(file);
//	return s_Instance;
//}

void SceneManager::InitSceneManager()
{
	int numberOfCam;
	FILE* file = fopen(sceneManagerFile, "r");
	if (file == NULL)
	{
		std::cout << "No file found for SceneManager" << std::endl;
		return;
	}
	else std::cout << "File opened for SceneManager" << std::endl;
	//Camera
	fscanf(file, "#Cameras: %d\n", &numberOfCam);
	for (int i = 0; i < numberOfCam; i++)
	{
		Camera cam = Camera();
		fscanf(file, "ID %d\n", &cam.id);
		fscanf(file, "POSITION %f %f %f\n", &cam.cameraPos.x, &cam.cameraPos.y, &cam.cameraPos.z);
		fscanf(file, "TARGET %f %f %f\n", &cam.cameraTarget.x, &cam.cameraTarget.y, &cam.cameraTarget.z);
		fscanf(file, "UP %f %f %f\n", &cam.up.x, &cam.up.y, &cam.up.z);
		fscanf(file, "FOVY %f\n", &cam.mFOV);
		fscanf(file, "NEAR %f\n", &cam.mNear);
		fscanf(file, "FAR %f\n", &cam.mFar);
		fscanf(file, "MOVE_SPEED %f\n", &cam.cameraSpeed);
		fscanf(file, "ROTATE_SPEED %f\n", &cam.rotationSpeed);
		camera = cam;
	}
	fscanf(file, "\n");

	//Object
	ResourcesManager resource =  ResourcesManager("../Resources/RM1.txt");
	resource.Init();
	//std::cout << resource.modelList.back().mModelFilePath << std::endl;
	//std::cout << resource.shaderList.back().fileFS << std::endl;

	fscanf(file, "#Objects: %d\n", &numberOfObject);

	for (int i = 0; i < numberOfObject; i++)
	{
		Object *ob = new Object();
		int modelId, textureId, shaderId, cubeTextureId;
		int light;
		fscanf(file, "ID %d\n", &ob->id);
		//cout << ob->id << endl;
		fscanf(file, "MODEL %d\n", &modelId);
		//cout << modelId << endl;
		ob->oModel = resource.modelList.at(modelId);
		//std::cout << resource.modelList.at(modelId).mModelFilePath << std::endl;

		fscanf(file, "TEXTURES %d\n", &ob->numberOfTexture);
		for (int j = 0; j < ob->numberOfTexture; j++)
		{
			fscanf(file, "TEXTURE %d\n", &textureId);
			ob->oTexture.push_back(resource.textureList.at(textureId));
		}
		fscanf(file, "CUBETEXTURES %d\n", &cubeTextureId);

		fscanf(file, "SHADER %d\n", &shaderId);
		ob->oShaders = resource.shaderList.at(shaderId);
		fscanf(file, "LIGHTS %d\n", &light);
		fscanf(file, "POSITION %f %f %f\n", &ob->oPos.x, &ob->oPos.y, &ob->oPos.z);
		fscanf(file, "ROTATION %f %f %f\n", &ob->oRotation.x, &ob->oRotation.y, &ob->oRotation.z);
		fscanf(file, "SCALE %f %f %f\n", &ob->oScale.x, &ob->oScale.y, &ob->oScale.z);
		fscanf(file, "\n");
		objectList.push_back(ob);

		delete ob;
	}
	fclose(file);
	/*for (int i = 0; i < numberOfObject; i++) {
		std::cout << objectList.at(i).oPos.x << " " << objectList.at(i).oPos.y << " " << objectList.at(i).oPos.z << std::endl;
		cout << objectList.at(i).oShaders.fileVS << " " << objectList.at(i).oShaders.fileFS << endl;
	}*/
}

void SceneManager::Init()
{
	InitSceneManager();
	//Init Object
	for (int i = 0; i < numberOfObject; i++)
	{
		objectList.at(i).InitObject();
		objectList.at(i).oModel.Init();
		for (int j = 0; j < objectList.at(i).oTexture.size(); j++)
		{
			objectList.at(i).oTexture.at(j).Init();
		}
		objectList.at(i).oShaders.Init(objectList.at(i).oShaders.fileVS, objectList.at(i).oShaders.fileFS);
	}
	//Init camera
	camera.Init();
}

void SceneManager::Draw(Shaders myShaders)
{
	glUniformMatrix4fv(myShaders.u_Projection, 1, GL_FALSE, *camera.GetPerspective().m);
	glUniformMatrix4fv(myShaders.u_View, 1, GL_FALSE, *camera.GetViewMatrix().m);

	for (int i = 0; i < objectList.size(); i++) {
		objectList.at(i).Draw(myShaders);
	}

}
