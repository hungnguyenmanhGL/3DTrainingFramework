#pragma once
#include <cstdio>
#include <GLES2/gl2.h>
#include "../Utilities/utilities.h"
class Model
{
public:
	char* mModelFilePath;
	void LoadNFGFile(FILE* file);
	GLuint mVBO;
	GLuint mIBO;
	int mNumberOfVertex;
	int mNumberOfIndices;
	void Init();
	void Draw();
	void Bind();
	void Unbind();
	Model(const char* modelFile);
	Model();
	~Model();
};


