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
	GLuint wrapMode;
	GLuint filterMode;

	void Init();
	Texture(const char* tgaFilePath);
	~Texture();
};

