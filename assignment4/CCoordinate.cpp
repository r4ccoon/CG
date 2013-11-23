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

#include "CCoordinate.h"

CCoordinate::CCoordinate(float length)
{
	_length = length;
	_size = 0.1;
	colorX = Vec3f(1, 0, 0);
	colorY = Vec3f(0, 1, 0); 
	colorZ = Vec3f(0, 0, 1);
}

void CCoordinate::Draw(){
	glLineWidth(1.5);
		glPushMatrix();
		//////////////
		/// X
		glColor3f(colorX.x, colorX.y, colorX.z);
		glBegin(GL_LINES);	
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(_length, 0, 0);  
		glEnd();
	 
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-_length, 0, 0);
		glEnd();
		// X Cone
		glPushMatrix();
		glTranslatef(_length - 0.5, 0, 0);
		glRotatef(90, 0, 1, 0);
		glutSolidCone(_size, 0.5, 32, 32);
		glPopMatrix();
	 
		/////////////
		/// Y
		glColor3f(colorY.x, colorY.y, colorY.z);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, _length, 0);
		glEnd();
	
		glColor3f(colorY.x, colorY.y, colorY.z);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, -_length, 0);
		glEnd();
		// Y Cone
		glPushMatrix();
		glTranslatef(0, _length - 0.5, 0);
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(_size, 0.5, 32, 32);
		glPopMatrix();
	 
		/////////////
		/// Z
		glColor3f(colorZ.x, colorZ.y, colorZ.z);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 0, _length);
		glEnd();

		glColor3f(colorZ.x, colorZ.y, colorZ.z);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 0, -_length);
		glEnd(); 
		// Z Cone
		glPushMatrix();
		glTranslatef(0, 0, _length - 0.5);
		glutSolidCone(_size, 0.5, 32, 32);
		glPopMatrix();

	glPopMatrix();
}

CCoordinate::~CCoordinate()
{
}
