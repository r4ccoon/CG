//
//  main.cpp
//  Assignment6
//
//  Created by Ridho, Rohan, Zeeshan
//
//  please ctrl+f HS2RGB to find the required implementatsion of the assignment
//  class square to handle interpolation and color picker

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

#include <math.h>
#include <cstdio>
using namespace std;

#include "decasteljau.h"

int width = 640;
int height = 480;

Decasteljau decasteljau;

void init(void){
    glClearColor(1.0, 1.0 , 1.0, 1.0);
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2 , -1.0f, 1.0f);
}

void reshape(int w, int h){
    width = w;
    height = h;
    
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-width/2, width/2, -height/2, height/2 , -1.0f, 1.0f);
}

// method to be passed to glutdisplayfunc to draw the triangle lines and colors
void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    decasteljau.Draw();
    
    glFlush();
}

void mouseMap(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
            decasteljau.MouseClick(x, y);
        }
	}
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
            decasteljau.RightMouseClick();
    }
    
    glutPostRedisplay();
}


int main( int argc, char* argv[] )
{
	glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(width, height);
    glutCreateWindow("Assignment 7, task 1");
    
    init();
    
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
	glutMouseFunc(mouseMap);
    
    glutMainLoop();
	return 0;
}

