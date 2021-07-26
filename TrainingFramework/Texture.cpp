#include "stdafx.h"
#include "Texture.h"
#include <iostream>
#include <vector>
#include <string>

void Texture::ConfigTexture()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);
}
void Texture::Init()
{
	int iWidth;
	int iHeight;
	int iBpp;
	const char* imageData = LoadTGA(mTgaFilePath, &iWidth, &iHeight, &iBpp);

	GLenum format = (iBpp == 24 ? GL_RGB : GL_RGBA);

	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_2D, mTextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
	if (imageData)
	{
		std::cout << "Load texture success" << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, format, iWidth, iHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Fail to load texture!" << std::endl;
	}
	ConfigTexture();
	glBindTexture(GL_TEXTURE_2D, 0);
	delete imageData;
}
Texture::Texture(const char* tgaFilePath)
{
	mTgaFilePath = strdup(tgaFilePath);
}
Texture::Texture()
{

}

Texture::~Texture()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glDeleteTextures(1, &mTextureId);
}

void Texture::cubeInit(std::vector <char*> faces)
{
	int iWidth;
	int iHeight;
	int iBpp;

	
	glGenTextures(1, &mTextureId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTextureId);
	for (int i = 0; i < 6; i++) {
		const char* imageData = LoadTGA(faces.at(i), &iWidth, &iHeight, &iBpp);

		if (imageData) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
			//std::cout << faces.at(i) << std::endl;
		}
		else {
			std::cout << "Fail to load " << faces.at(i) << std::endl;
		}
		delete imageData;
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}