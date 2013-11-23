#include "CCamera.h"


CCamera::CCamera()
{
	_eyePosition = new Vec3f(0, 0, 0);
	_lookAt = new Vec3f(0, 0, 5);
}


CCamera::~CCamera()
{
}
