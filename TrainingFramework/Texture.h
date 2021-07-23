#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
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
};

