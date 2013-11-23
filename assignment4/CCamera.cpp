#ifdef _WIN32
#include <windows.h>
#endif
#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "CCamera.h"

CCamera::CCamera()
{
	_eyePosition = new Vec3f(2.0, 2.0, 5.0);
	_lookAt = new Vec3f(0.0, 0.0, 0.0);
}

void CCamera::Look(float width, float height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, width / height, 1.0, 10.0);

	float ke = width / 60;
	float he = height / 60;

	glOrtho(-ke, ke, -he, he, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(_eyePosition->x, _eyePosition->y, _eyePosition->z, _lookAt->x, _lookAt->y, _lookAt->z, 0.0, 1.0, 0.0);
	//gluLookAt(2.0, 2.0, 5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void CCamera::Reset(){

	_eyePosition->x = 2;
	_eyePosition->y = 2;
	_eyePosition->z = 5;
}

void CCamera::SetPosition(Vec3f newPosition)
{
	_eyePosition->x = newPosition.x;
	_eyePosition->y = newPosition.y;
	_eyePosition->z = newPosition.z;
}

void CCamera::SetTarget(Vec3f newPosition)
{
	_lookAt->x = newPosition.x;
	_lookAt->y = newPosition.y;
	_lookAt->z = newPosition.z;
}

CCamera::~CCamera()
{
}
