//
//  main.cpp
//  GlutApp
//
//  Created by Asmat, Laksono, Malik on 2/11/2013.
// 
  
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

#include <iostream>
#include <vector> 
#include "CCamera.h"
#include "CDrawableObject.h"
#include "CCoordinate.h"
#include "CPlane.h"
#include "Trackball.h"

using namespace std;

GLfloat width = 800;
GLfloat height = 600;

CCamera* camera;
vector<CDrawableObject*> *allObjects;
SimpleTrackball *trackBall;
CPlane *plane;
CCoordinate *coord;

void init(void){ 
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// enable z buffer depth test
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
}

void initObjects(){
	camera = new CCamera();
	trackBall = new SimpleTrackball();
    
	//allObjects = new vector<CDrawableObject*>();
	// the cartesion coordinate lines
	//allObjects->push_back(new CCoordinate(1));
    
    coord = new CCoordinate(1);
    plane = new CPlane(1);
    
	//allObjects->push_back();
}
 
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	coord->Draw();
    plane->Draw();
 
	camera->Look(width, height);
	trackBall->multModelMatrix();

    glutSwapBuffers();
}


void reshape(int w, int h){
    // set for display method got the correct display
    width = w;
    height = h;
    
    // viewport set
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
	camera->Look(width, height);
}

void keyMap(unsigned char key, int x, int y)
{
    plane->Key(key);
    
    if(key == 'r'){
        camera->Reset();
        plane->Reset();
        trackBall->Reset();
	}
    
    glutPostRedisplay();
}

void mouseMap(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			trackBall->startBall(x, y);
		}

		if (state == GLUT_UP)
		{
			trackBall->stopBall(x, y);
		}
	}
    
    glutPostRedisplay();
}

void mouseDrag(int x, int y)
{
	trackBall->rollBall(x, y);
    glutPostRedisplay();
}
    
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("Assignment 4, task 1");

	initObjects();
    init(); 
    
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    
    // control handling
	glutKeyboardFunc(keyMap);
	glutMouseFunc(mouseMap);
	glutMotionFunc(mouseDrag);
    
    glutMainLoop();
    return 0;
}
