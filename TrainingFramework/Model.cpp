#include "stdafx.h"
#include "Model.h"
#include "Vertex.h"
#include <iostream>

void Model::LoadNFGFile(FILE *file)
{
	int numVertices;
	fscanf(file, "NrVertices: %d\n", &numVertices);
	Vertex *vertices = new Vertex[numVertices];

	//std::cout << numVertices << std::endl;

	for (int i = 0; i < numVertices; ++i) {
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

		(vertices + i)->pos.x = posX; (vertices + i)->pos.y = posY - 1; (vertices + i)->pos.z = posZ;
		(vertices + i)->uv.x = uvX; (vertices + i)->uv.y = uvY;
		/*std::cout << "Pos: " << posX << "," << posY << "," << posZ << std::endl;
		std::cout << "Norm: " << normX << "," << normY << "," << normZ << std::endl;
		std::cout << "Binorm: " << binormX << "," << binormY << "," << binormZ << std::endl;
		std::cout << "Tangent: " << tgtX << "," << tgtY << "," << tgtZ << std::endl;
		std::cout << "uv: " << uvX << "," << uvY << "." <<  std::endl;*/

		/*vertices[id].pos.x = posX; vertices[id].pos.y = posY - 1; vertices[id].pos.z = posZ;
		vertices[id].normal.x = normX; vertices[id].normal.y = normY; vertices[id].normal.z = normZ;
		vertices[id].binormal.x = binormX; vertices[id].binormal.y = binormY; vertices[id].binormal.z = binormZ;
		vertices[id].tangent.x = tgtX; vertices[id].tangent.y = tgtY; vertices[id].tangent.z = tgtZ;
		vertices[id].uv.x = uvX; vertices[id].uv.y = uvY;*/

		/*std::cout << "Pos: " << vertices[id].pos.x << "," << vertices[id].pos.y << "," << vertices[id].pos.z << std::endl;
		std::cout << "Norm: " << vertices[id].normal.x << "," << vertices[id].normal.y << "," << vertices[id].normal.z << std::endl;
		std::cout << "Binorm: " << vertices[id].binormal.x << "," << vertices[id].binormal.y << "," << vertices[id].binormal.z << std::endl;
		std::cout << "Tangent: " << vertices[id].tangent.x << "," << vertices[id].tangent.y << "," << vertices[id].tangent.z << std::endl;
		std::cout << "uv: " << vertices[id].uv.x << "," << vertices[id].uv.y << "." << std::endl;*/
	}
	glGenBuffers(1, &this->mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, this->mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * numVertices, vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	int numIndices;
	fscanf(file, "NrIndices: %d\n", &numIndices);
	//std::cout << numIndices << std::endl;
	int* indices = new int[numIndices];
	for (int i = 0; i < numIndices; i += 3) {
		int id;
		int iX, iY, iZ;
		fscanf(file, "%d. ", &id);
		fscanf(file, " %d, %d, %d\n", &iX, &iY, &iZ);
		*(indices + i) = iX; *(indices + i + 1) = iY; *(indices + i + 2) = iZ;
		//std::cout << "Indices" << id << ": " << indices[i] << "," << indices[i+1] << "," << indices[i+2] << std::endl;
	}
	glGenBuffers(1, &this->mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * numIndices, indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	this->mNumberOfIndices = numIndices;
	fclose(file);
	delete vertices;
	delete indices;
};

Model::Model(const char* modelFilePath)
{
	mModelFilePath = strdup(modelFilePath);
}
Model::~Model()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mIBO);
}
void Model::Init()
{
	FILE* file = fopen(mModelFilePath, "rb");
	if (file != NULL)
	{
		LoadNFGFile(file);
	}
	else std::cout << "Fail to load NFG file!" << std::endl;
}