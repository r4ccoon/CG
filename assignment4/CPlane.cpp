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

CPlane::CPlane(float length, float lineLength)
{
	_length = length;
    
    U = 0.1;
    V = 0.1;
    W = 0.4;
    
    _lineLength = lineLength; 
}

void CPlane::Draw(){
	// plane
	glColor4f(0.5, 0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	 
    glVertex3f(-_length, -_length, W);
    glVertex3f(_length, -_length, W);
    glVertex3f(_length, _length, W);
    glVertex3f(-_length, _length, W);
    
	glEnd(); 

	// projection line
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
    glVertex3f( _lineLength * U, _lineLength * V, _lineLength );
    glVertex3f( -_lineLength * U, -_lineLength * V, -_lineLength );
	glEnd();
	
	// The intersection vertice with the plane
	// the vertice (x, y, w) of the w = 1 plane.
    glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
    glTranslatef(U * W, V * W, W);
    glutSolidSphere(0.02, 16, 16);
	glPopMatrix();
}

void CPlane::Key(unsigned char key){
    
	switch (key)
	{
		case 'q':
            U += 0.1;
            break;
        case 'a':
            U -= 0.1;
            break;
            
        case 'w':
            W += 0.1;
            break;
        case 's':
            W -= 0.1;
            break;
            
        case 'e':
            V += 0.1;
            break;
        case 'd':
            V -= 0.1;
            break;
    }
}

void CPlane::Reset(){
    U = 0.1;
    V = 0.1;
    W = 0.4;
}

CPlane::~CPlane()
{
}
