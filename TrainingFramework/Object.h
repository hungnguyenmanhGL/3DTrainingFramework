#pragma once
#include "../Utilities/utilities.h"
#include <vector>
#include "Model.h"
#include "Texture.h"
#include "Shaders.h"
using namespace std;
class Object
{
public:
	int id;
	Model oModel;
	int numberOfTexture;
	vector<Texture> oTexture;
	Shaders oShaders;
	Vector3 oPos, oRotation, oScale;
	Matrix Rx, Ry, Rz;
	Matrix Scale, Rotation, Translation;
	Matrix WorldMatrix, MVP;

	Object(Model model, vector<Texture> texture, Shaders shaders, int id = 0);
	Object();
	Object(Object *o);

	void InitObject();
	void BindTexture();
	void Draw(Shaders shader);

	Matrix SetRotation();
	Matrix SetWorldMatrix();
};