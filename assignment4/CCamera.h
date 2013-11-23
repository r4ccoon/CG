#pragma once

#include "vec3.h"

class CCamera
{
public:
	CCamera();
	~CCamera();

	void Look(float width, float height);
	void SetPosition(Vec3f);
	void SetTarget(Vec3f);

	void Reset();

private:
	Vec3f *_eyePosition;
	Vec3f *_lookAt;
};

