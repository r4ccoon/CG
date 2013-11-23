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
#include "Trackball.h"

using namespace std;

GLfloat width = 800;
GLfloat height = 600;

CCamera* camera;
vector<CDrawableObject*> *allObjects;
SimpleTrackball *trackBall;

void init(void){ 
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
}

void initObjects(){
	camera = new CCamera();
	trackBall = new SimpleTrackball();
	allObjects = new vector<CDrawableObject*>();
	// the cartesion coordinate lines
	allObjects->push_back(new CCoordinate(5));
}
 
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	//for (vector<CDrawableObject*>::iterator it = allObjects->begin(); it != allObjects->end(); it++) {
	for (int i = 0; i < allObjects->size(); i++)
	{
		CDrawableObject* obj = allObjects->at(i);
		obj->Draw();
	}

	// test draw sphere
	if (true == false)
	{
		static GLUquadric *qsphere = 0;
		qsphere = gluNewQuadric();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		gluSphere(qsphere, 1, 32, 32);
	}

	camera->Look(width, height);
	trackBall->multModelMatrix();

    glutSwapBuffers();
}

void animation(){
    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    
    // animation code here
    
    glutPostRedisplay();
}

void reshape(int w, int h){
    // set for display method got the correct display
    width = w;
    height = h;
    
    // viewport set
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
}

void keyMap(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'd':
        case 'D': 
			break;
        
        case 's':
        case 'S': 
			break;
            
		case 'a':
        case 'A': 
			break;
	}
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
}

void mouseDrag(int x, int y)
{
	trackBall->rollBall(x, y);
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

	// animate
	glutIdleFunc(animation);
    
    glutMainLoop();
    return 0;
}
