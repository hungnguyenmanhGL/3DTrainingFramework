#pragma once
#include "../Utilities/Math.h"

struct Vertex 
{
	Vector3 pos;
	Vector3 color;
	Vector2 uv;

	Vector3 normal;
	Vector3 binormal;
	Vector3 tangent;
};