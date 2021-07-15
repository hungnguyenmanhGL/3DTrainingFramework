// TrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "Globals.h"
#include <conio.h>
#include <iostream>


GLuint vboId, iboId, textureId;
Shaders myShaders;

void Load3DModel(Vertex vertices[], int indices[])
{
	FILE* file;
	file = fopen("../Resources/Woman1.nfg", "r");
	int numVertices;
	fscanf(file, "NrVertices: %d\n", &numVertices);
	//std::cout << numVertices << std::endl;

	for (int i = 0; i < numVertices; i++) {
		float posX, posY, posZ;
		float normX, normY, normZ;
		float binormX, binormY, binormZ;
		float tgtX, tgtY, tgtZ;
		float uvX, uvY;

		int id;
		fscanf(file, "%d. ", &id);
		//std::cout << id << " ";
		fscanf(file, "pos:[%f, %f, %f]; ", &posX, &posY, &posZ);
		fscanf(file, "norm:[%f, %f, %f]; ", &normX, &normY, &normZ);
		fscanf(file, "binorm:[%f, %f, %f]; ", &binormX, &binormY, &binormZ);
		fscanf(file, "tgt:[%f, %f, %f]; ", &tgtX, &tgtY, &tgtZ);
		fscanf(file, "uv:[%f, %f];\n ", &uvX, &uvY);
		/*std::cout << "Pos: " << posX << "," << posY << "," << posZ << std::endl;
		std::cout << "Norm: " << normX << "," << normY << "," << normZ << std::endl;
		std::cout << "Binorm: " << binormX << "," << binormY << "," << binormZ << std::endl;
		std::cout << "Tangent: " << tgtX << "," << tgtY << "," << tgtZ << std::endl;
		std::cout << "uv: " << uvX << "," << uvY << "." <<  std::endl;*/

		vertices[id].pos.x = posX; vertices[id].pos.y = posY; vertices[id].pos.z = posZ;
		vertices[id].normal.x = normX; vertices[id].normal.y = normY; vertices[id].normal.z = normZ;
		vertices[id].binormal.x = binormX; vertices[id].binormal.y = binormY; vertices[id].binormal.z = binormZ;
		vertices[id].tangent.x = tgtX; vertices[id].tangent.y = tgtY; vertices[id].tangent.z = tgtZ;
		vertices[id].uv.x = uvX; vertices[id].uv.y = uvY;

		/*std::cout << "Pos: " << vertices[id].pos.x << "," << vertices[id].pos.y << "," << vertices[id].pos.z << std::endl;
		std::cout << "Norm: " << vertices[id].normal.x << "," << vertices[id].normal.y << "," << vertices[id].normal.z << std::endl;
		std::cout << "Binorm: " << vertices[id].binormal.x << "," << vertices[id].binormal.y << "," << vertices[id].binormal.z << std::endl;
		std::cout << "Tangent: " << vertices[id].tangent.x << "," << vertices[id].tangent.y << "," << vertices[id].tangent.z << std::endl;
		std::cout << "uv: " << vertices[id].uv.x << "," << vertices[id].uv.y << "." << std::endl;*/
	}

	int numIndices;
	fscanf(file, "NrIndices: %d\n", &numIndices);
	//std::cout << numIndices << std::endl;

	for (int i = 0; i < numIndices; i+=3) {
		int id;
		int iX, iY, iZ;
		fscanf(file, "%d. ", &id);
		fscanf(file, " %d, %d, %d\n", &iX, &iY, &iZ);

		//std::cout << "Indices" << id << ": " << iX << "," << iY << "," << iZ << std::endl;
		indices[i] = iX;
		indices[i + 1] = iY;
		indices[i + 2] = iZ;
		//std::cout << "Indices" << id << ": " << indices[i] << "," << indices[i+1] << "," << indices[i+2] << std::endl;
 	}
	fclose(file);
};

int Init(ESContext* esContext)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	//triangle data (heap)
	Vertex verticesData[3];
	Vertex vertices[512];
	int ind[2154];

	Load3DModel(vertices, ind);
	//for (int i = 0; i < 512; i++) { //debug
	//	std::cout << i <<". Pos: " << vertices[i].pos.x << ", " << vertices[i].pos.y << "," << vertices[i].pos.z << std::endl;
	//	std::cout << "Norm: " << vertices[i].normal.x << "," << vertices[i].normal.y << "," << vertices[i].normal.z << std::endl;
	//	std::cout << "Binorm: " << vertices[i].binormal.x << "," << vertices[i].binormal.y << "," << vertices[i].binormal.z << std::endl;
	//	std::cout << "Tangent: " << vertices[i].tangent.x << "," << vertices[i].tangent.y << "," << vertices[i].tangent.z << std::endl;
	//	std::cout << "uv: " << vertices[i].uv.x << "," << vertices[i].uv.y << "." << std::endl;
	//}
	//for (int i = 0; i < 2154; i+=3) {
	//	std::cout << ind[i] << "," << ind[i + 1] << "," << ind[i + 2] << std::endl;
	//}


	verticesData[0].pos.x = 0.0f;  verticesData[0].pos.y = 0.5f;  verticesData[0].pos.z = 0.0f;
	verticesData[1].pos.x = -0.5f;  verticesData[1].pos.y = -0.5f;  verticesData[1].pos.z = 0.0f;
	verticesData[2].pos.x = 0.5f;  verticesData[2].pos.y = -0.5f;  verticesData[2].pos.z = 0.0f;

	verticesData[0].color.x = 1.0f;  verticesData[0].color.y = 0.0f;  verticesData[0].color.z = 0.0f;
	verticesData[1].color.x = 0.0f;  verticesData[1].color.y = 1.0f;  verticesData[1].color.z = 0.0f;
	verticesData[2].color.x = 0.0f;  verticesData[2].color.y = 0.0f;  verticesData[2].color.z = 1.0f;

	verticesData[0].uv.x = 0.0f;  verticesData[0].uv.y = 0.0f;
	verticesData[1].uv.x = 1.0f;  verticesData[1].uv.y = 0.0f;
	verticesData[2].uv.x = 0.5f;  verticesData[2].uv.y = 1.0f;

	//int indices[] = { 0, 1, 2 };
	//buffer object
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ARRAY_BUFFER, iboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ind), ind, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Textures
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);

	//Load texture
	int iWidth = 0, iHeight = 0, iBpp = 0;
	char* imageData = LoadTGA("../Resources/Woman1.tga", &iWidth, &iHeight, &iBpp);
	GLenum format = (iBpp == 24 ? GL_RGB : GL_RGBA);
	if (imageData)
	{
		std::cout << "Load success" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Fail to load texture" << std::endl;
	}

	//Wraping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);
	//creation of shaders and program 
	return myShaders.Init("../Resources/Shaders/TriangleShaderVS.vs", "../Resources/Shaders/TriangleShaderFS.fs");

}

void Draw(ESContext* esContext)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(myShaders.program);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);

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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glDrawElements(GL_TRIANGLES, 2154, GL_UNSIGNED_INT, 0);

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



