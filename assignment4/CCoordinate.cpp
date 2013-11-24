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
	_size = 0.05;
	colorX = Vec3f(1, 0, 0);
	colorY = Vec3f(0, 1, 0); 
	colorZ = Vec3f(0, 0, 1);
}

void CCoordinate::Draw(){
	glLineWidth(1.5);
    
    glBegin(GL_LINES);
    
		/// X
		glColor3f(colorX.x, colorX.y, colorX.z);
        glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(_length, 0, 0);
     
		/// Y
		glColor3f(colorY.x, colorY.y, colorY.z);
        glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, _length, 0);
     
		/// Z
		glColor3f(colorZ.x, colorZ.y, colorZ.z);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0, 0, _length);
    
    glEnd();
    
    // X Cone
    glColor3f(colorX.x, colorX.y, colorX.z);
    glPushMatrix();
    glTranslatef(_length - 0.05, 0, 0);
    glRotatef(90, 0, 1, 0);
    glutSolidCone(_size, 0.1, 10, 10);
    glPopMatrix();
    
    // Y Cone
    glColor3f(colorY.x, colorY.y, colorY.z);
    glPushMatrix();
    glTranslatef(0, _length - 0.05, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(_size, 0.1, 10, 10);
    glPopMatrix();
    
    // Z Cone
    glColor3f(colorZ.x, colorZ.y, colorZ.z);
    glPushMatrix();
    glTranslatef(0, 0, _length - 0.05);
    glutSolidCone(_size, 0.1, 10, 10);
    glPopMatrix();
 
}

CCoordinate::~CCoordinate()
{
}
