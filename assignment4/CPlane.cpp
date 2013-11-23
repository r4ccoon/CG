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

#include "CPlane.h"

CPlane::CPlane(float length)
{
	_length = length;
}

void CPlane::Draw(){
	// plane
	glColor4f(0.5, 0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	
	/*
	glVertex3f(-_length, 0, -_length);
	glVertex3f(-_length, 0, _length);
	glVertex3f(_length, 0, _length);
	glVertex3f(_length, 0, -_length);
	*/

	glVertex2f(-_length, -_length);
	glVertex2f(-_length, _length);
	glVertex2f(_length, _length);
	glVertex2f(_length, -_length);

	glEnd(); 

	// projection line
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1, 1, 0);
	glEnd();
}

CPlane::~CPlane()
{
}
