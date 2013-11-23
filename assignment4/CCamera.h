#pragma once

#include "vec3.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

private:
	Vec3f *_eyePosition;
	Vec3f *_lookAt;
};

