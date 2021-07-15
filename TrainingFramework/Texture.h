#pragma once
#include "../Utilities/utilities.h"
#include <cstdio>
class Texture
{
private:
	char* mTgaFilePath;
	void ConfigTexture();
public:
	GLuint mTextureId;
	void Init();
	Texture(const char* tgaFilePath);
	~Texture();
};

