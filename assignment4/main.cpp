//
//  main.cpp
//  GlutApp
//
//  Created by Asmat, Laksono, Malik on 2/11/2013.
// 
  
#ifdef _WIN32
    #include <windows.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
	#include <GL/glut.h> 
#elif __APPLE__
    #include <GLUT/glut.h>
#else 
	#include <GL/glut.h> 
#endif

GLfloat width = 800;
GLfloat height = 600;

void init(void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_FLAT);
    
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);
}
 
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
     
    
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
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (width / 2) / height, 1.0, 10.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//gluLookAt(0.0, 0.0, camera1_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keymap(unsigned char key, int x, int y)
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
    
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(width, height);
    
    glutCreateWindow("Assignment 4, task 1");

    init(); 
    
    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
    
    // keyboard handling
	glutKeyboardFunc(keymap);
    
	glutIdleFunc(animation);
    
    glutMainLoop();
    return 0;
}
