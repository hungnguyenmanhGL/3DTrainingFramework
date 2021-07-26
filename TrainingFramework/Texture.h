#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
#include <vector>
#include <string>
class Texture
{
private:
	void ConfigTexture();
public:
	GLuint mTextureId;
	char wrapMode[20];
	char filterMin[20];
	char filterMag[20];
	char* mTgaFilePath;
	void Init();
	Texture(const char* tgaFilePath);
	Texture();
	~Texture();
	void cubeInit(std::vector<char*> faces);
};

