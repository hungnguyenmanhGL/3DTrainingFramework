#pragma once
#include <cstdio>
#include <GLES2/gl2.h>
#include "../Utilities/Math.h"
#include "../Utilities/utilities.h"
class Camera
{
	Vector3 cameraPos = Vector3(0.0, 0.0, 3.0);
	Vector3 cameraTarget = Vector3(0.0, 0.0, 0.0);
	Vector3 cameraDirection = (cameraPos - cameraTarget).Normalize();
};

