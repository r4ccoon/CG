/*****************************************************************************
 *
 * Culling Exercise
 * Lecture "Introduction to Computer Graphics", Prof. Re.Klein
 *
 * Functions to implement:
 * -----------------------
 *  - void RenderOctreeNode(..);
 *
 *  - void cullOctree(..);
 *
 * Keyboard controls:
 * ------------------
 *  'o' : Switch between observer mode (showing the scene from above in overview
 *        including visualization of viewing frustum) and camera view.
 *        (Default: observer mode)
 *  'a' : Toggle rendering of all teapots, where teapots with invisble flag set 
 *        are drawn in gray. (Useful for debugging.)
 *        (Default: off)
 *
 * (c)2005-2011 Institute of Computer Science II, University of Bonn
 *
 *****************************************************************************/

#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <ctime>
#include <cmath>    // for pow and sqrt

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

#include <vector>
#include <iostream>

#include "Trackball.h"

using namespace std;


//-----------------------------------------------------------------------------
//  Octree types
//-----------------------------------------------------------------------------

struct OctreeObject 
{
  double Color[3];
  double Translation[3];
  double Rotation[4];
  double Scale;  
  bool   visible; // this flag must be set by the culling!
};

struct OctreeNode
{
  OctreeNode* SubNodes[8];
  vector<unsigned int> AttachedObjects;
};

typedef unsigned int uint;


//-----------------------------------------------------------------------------
//  Global variables
//-----------------------------------------------------------------------------

// viewing frustum
float leftt = -1;
float rightt = 1;
float top = 1;
float bottom = -1;
float zNear = 1;
float zFar = 20;

// octree parameters
int    threshold = 5; // minimum number of elements in node to be subdivided
double minSize   = 2; // minimum edge length of an octree node
float initialCellSize = 100.f; // edge length of octree root node
float center[3] = {0.0, 0.0, 0.0}; // center coordinate of octree root node

OctreeNode root;

vector<OctreeObject> teapots;
const int nrOfTeapots = 400;

// user interface
SimpleTrackball trackBall;
bool observerMode = true;  // observer mode shows the whole scene and frustum
bool renderAll    = false; // render also 'inivisble' objects in gray?


//-----------------------------------------------------------------------------
 
void init(void)
{
  // clear screen
  glClearColor(0, 0, 0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();	     // load the identity matrix
  glFrustum(leftt, rightt, bottom, top, zNear, zFar);

  glShadeModel(GL_SMOOTH);	// set smooth shading 

  trackBall.setTranslateSpeed(10.0);

  // prepare Utah teapot geometry (as display list)
  glNewList(1, GL_COMPILE);
  glutSolidTeapot(1.0);
  glEndList();
}


// Returns inverse of current ModelView matrix in vm
void getInverseModelView(float vm[16])
{  
  float mv[16];
  glGetFloatv(GL_MODELVIEW_MATRIX, mv);

  // Invert the matrix mv (assuming that it only contains a 
  // rotation and a translation part)
  // for example:
  //
  //      (         |   )
  // mv = (    R    | T )
  //      (         |   )
  //      ( --------|---)
  //      ( 0  0  0 | 1 )
  //
  // the inverse is then:
  //      (         |        )
  // vm = (    R^t  | -R^t*T )
  //      (         |        )
  //      ( --------|--------)
  //      ( 0  0  0 | 1      )
  //
  
  assert(mv[3] == 0.0);
  assert(mv[7] == 0.0);
  assert(mv[11] == 0.0);
  assert(mv[15] == 1.0);

  vm[3] = vm[7] = vm[11] = 0.f;
  vm[15] = 1.0;

  for(uint i=0;i<3;i++){
    vm[12 + i] = 0;
    for(uint j=0;j<3;j++){
      vm[i*4 + j] = mv[j*4 + i];
      vm[12 +i] -= mv[12+j] * mv[4*i + j]; 
    }
  }
}


void RenderTeapot(OctreeObject *object)
{
  if(object->visible){
    glColor3f(object->Color[0], object->Color[1], object->Color[2]);
  }
  else{
	if (!renderAll)
		  return;
    glColor3f(.5f, .5f, .5f); // draw 'invisible' teapots in grey
  }
  glPushMatrix();    
  glTranslatef(object->Translation[0], object->Translation[1], object->Translation[2]);			
  glRotated(object->Rotation[0], object->Rotation[1], object->Rotation[2], object->Rotation[3]);    
  glCallList(1);    
  glPopMatrix();

  // reset invisible flag
  object->visible = false;
}


void initNode(OctreeNode* node)
{
  for(int i=0;i<8;i++){
    node->SubNodes[i] = 0;
  }
  node->AttachedObjects.clear();
}


void computeChildCenter(int i, float center[3], float size, float NewCenter[3])
{
  NewCenter[0] = center[0] + ((2*(i % 2)-1) * size / 4.0 );
  NewCenter[1] = center[1] + ((2*((i % 4) / 2)- 1) * size / 4.0);
  NewCenter[2] = center[2] + ((2*(i / 4)-1) * size / 4.0);	
}
 

void Subdivide(OctreeNode* currNode, vector<unsigned int> PassedObjects, float center[3], float size)
{	
  int n = static_cast<int>(PassedObjects.size());
  if (n < threshold || size < minSize){
	  
    currNode->AttachedObjects = PassedObjects; 
    return;
  }  
		
  vector<unsigned int> childObjects[8];
  for (int i=0; i < n; i++){
    // test the children 
    int Octant = 255;
    double s = 1.65 * teapots[PassedObjects[i]].Scale;
    double x = teapots[PassedObjects[i]].Translation[0];
      if (x - center[0] < -s)
		  Octant &= 85;  //only left cells
	if (x - center[0] > s)
		Octant &= 170;   //only right cells
    double y = teapots[PassedObjects[i]].Translation[1];
      if (y - center[1] < -s)
		  Octant &= 51;  //only cells below
	if (y - center[1] > s)
		Octant &= 204;   //only cells above
    double z = teapots[PassedObjects[i]].Translation[2];
      if (z - center[2] < -s)
		  Octant &= 15;  //only cells in front
	if (z - center[2] > s)
		Octant &= 240;   //only cells behind
      
	for (int j=0; j < 8; j++)
		if(Octant&1<<j)
			childObjects[j].push_back(PassedObjects[i]);			
  }			
		
  // recursively subdivide the nodes below
  for (int i=0; i < 8; i++){
    if (childObjects[i].size())
      {	
		// create new node
		OctreeNode* NewSubNode = new OctreeNode;
		initNode(NewSubNode);
				
		// add to the current parent node
		currNode->SubNodes[i] = NewSubNode;

		float NewCenter[3];
		computeChildCenter(i, center, size, NewCenter);
		Subdivide(NewSubNode, childObjects[i], NewCenter, size / 2.0);
      }
  } 
}

// user depth
float userDOV = 3;

// depth color
float color[3] = {0.0, 0.0, 0.0} ;
void setColor(float r, float g, float b){
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

/**
 * the recursive octree-traversal
 * and render the cells and objects!
 **/
void RenderOctreeNode(OctreeNode* currNode, float center[3], float size, int depth)
{
    if (currNode == NULL) return;
    
	if (depth <= userDOV)
	{
        setColor(1, 1, 1);
        
        switch(depth){
            case 1:
                // RED
                setColor(1, 0, 0);
                break;
            case 2:
                // Green
                setColor(0, 1, 0);
                break;
            case 3:
                // BLUE
                setColor(0, 0, 1);
                break;
            case 4:
                setColor(1, 1, 0);
                break;
            case 5:
                setColor(1, 0, 1);
                break;
        }
        
        // draw the edges
        glColor3f(color[0], color[1], color[2]);
        glPushMatrix();
        glTranslatef(center[0], center[1], center[2]);
        glutWireCube(size);
        glPopMatrix();

        if(currNode->SubNodes != NULL){
            for (int j = 0; j < 8; j++)
            {
                float childCenter[3];
                computeChildCenter(j, center, size, childCenter);
                RenderOctreeNode(currNode->SubNodes[j], childCenter, size / 2.0, depth + 1);
            }
        }
	}
    
    // reset color for camera's icon
    glColor3f(color[0], color[1], color[2]);

}


// Print a 4x4 matrix onto the console.
void printMatrix(float mat[16])
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) 
			cerr << mat[4*j+i] << " ";
		cerr << endl;
	}
}

// Returns the product of current Projection and ModelView matrix
void getModelViewProjectionMatrix(float mvp[16])
{
  float mv[16];
  glMatrixMode(GL_PROJECTION);
  glGetFloatv(GL_MODELVIEW_MATRIX, mv);
  
  glPushMatrix();
  glMultMatrixf(mv);
  glGetFloatv(GL_PROJECTION_MATRIX, mvp);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
}


void multMatrixVector(float m[16], float v[4], float res[4])
{
  for(uint i=0;i<4;i++){
    res[i] = 0.f;
    for(uint j=0;j<4;j++){
      res[i] += v[j] * m[4*j+i];
    }
  }
}

	
void cullOctree(OctreeNode* node, float center[3], float size, float mvp[16])
{
	 
} 


void drawFrustum()
{
  float c = zFar/zNear;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glBegin(GL_QUADS);
  
  glVertex3f(leftt, bottom, -zNear);
  glVertex3f(leftt, top, -zNear);
  glVertex3f(leftt*c, top*c, -zFar);
  glVertex3f(leftt*c, bottom*c, -zFar);

  glVertex3f(rightt, bottom, -zNear);
  glVertex3f(rightt, top, -zNear);
  glVertex3f(rightt*c, top*c, -zFar);
  glVertex3f(rightt*c, bottom*c, -zFar);
  
  glVertex3f(leftt * c, bottom * c, -zFar);
  glVertex3f(leftt * c , top * c, -zFar);
  glVertex3f(rightt * c, top * c, -zFar);
  glVertex3f(rightt * c, bottom * c, -zFar);

  glVertex3f(leftt, bottom, -zNear);
  glVertex3f(leftt, top, -zNear);
  glVertex3f(rightt, top, -zNear);
  glVertex3f(rightt, bottom, -zNear);
  glEnd();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void display(void) 
{	
  glClear(GL_COLOR_BUFFER_BIT);
  
  // set trackball camera
  glMatrixMode(GL_PROJECTION);  
  glLoadIdentity();	    
  glFrustum(leftt, rightt, bottom, top, zNear, zFar);

  glMatrixMode(GL_MODELVIEW);   
  glLoadIdentity();
  trackBall.multModelMatrix();

  // perform culling
  float mvp[16];
  getModelViewProjectionMatrix(mvp);
  cullOctree(&root, center, initialCellSize, mvp);

  
  if(observerMode){
    // save the inverse trackball modelview matrix to draw the frustum later
    float vm[16];
    getInverseModelView(vm);  

    // set observer camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1.5, initialCellSize*2.f);
    
    glMatrixMode(GL_MODELVIEW);   
    glLoadIdentity();	     // load the identity matrix
    
    glTranslatef(0,0,-initialCellSize);
    glRotatef(90, 1,0,0);
    
	float center[3] = { 0.0f, 0.0f, 0.0f };
	RenderOctreeNode(&root, center, 100.0f, 0);

    // draw teapots
	for (unsigned int i = 0; i < nrOfTeapots; i++) {
		RenderTeapot(&teapots[i]);
	}
    
    // draw the viewfrustum of ther trackball camera
    glMultMatrixf(vm);
    drawFrustum();
  }
  else{
    // draw teapots
	for (unsigned int i = 0; i < nrOfTeapots; i++)
		RenderTeapot(&teapots[i]);
  }

  // show the picture drawn
  glutSwapBuffers();
}



void mouseClick(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN){
    switch(button){
    case GLUT_LEFT_BUTTON:
      trackBall.startBall(x, y);
      break;
    case GLUT_MIDDLE_BUTTON:
      trackBall.startDolly(x, y);
      break;
    case GLUT_RIGHT_BUTTON:
      trackBall.startTranslate(x, y);
      break;
    default:
      break;			
    }
  }
  if (state == GLUT_UP){
    switch(button){
    case GLUT_LEFT_BUTTON:
      trackBall.stopBall(x, y);
      break;
    case GLUT_MIDDLE_BUTTON:
      trackBall.stopDolly(x, y);
      break;
    case GLUT_RIGHT_BUTTON:
      trackBall.stopTranslate(x, y);
      break;
    default:
      break;			
    }
  }	
	
  glutPostRedisplay();
}


void mouseDrag(int x, int y)
{
  trackBall.rollBall(x, y);
  glutPostRedisplay();
}


void key(unsigned char c, int x, int y)
{
  switch(c){
  case 'o':
    observerMode = !observerMode;
    break;
  
	case 'a': 
	renderAll = !renderAll; 
	break;
          
    case '-':
    userDOV -= 1;
    if(userDOV < 0)
        userDOV = 0;
    break;
          
    case '+':
    case '=':
    userDOV += 1;
    if(userDOV > threshold)
       userDOV = threshold;
    break;
  }

  glutPostRedisplay();
}


// produces an evenly distributed random number between 0 and 1
double RandNr()
{	
  return ((double)((double)(rand())) / RAND_MAX);
}


// produces nrOfTeapots teapots with random parameters
void InitTeapots(int nrOfTeapots, vector<OctreeObject>& TeapotList)
{	
  for (int i=0; i < nrOfTeapots; i++)
    {
      OctreeObject Teapot;
      for (int j=0; j < 3; j++)
	  {
	    Teapot.Color[j] = RandNr();
	    Teapot.Translation[j] = initialCellSize * (-0.5+RandNr());
	    Teapot.Rotation[j+1] = RandNr();
	  }
      Teapot.Translation[1] = Teapot.Translation[1] / 5.f;
      Teapot.Rotation[0] = RandNr() * 360.0;
      Teapot.Scale = 0.5;//RandNr();
	  Teapot.visible = false;
      TeapotList.push_back(Teapot);	
    }
}


int main(int argc, char *argv[]) 
{    
  // initialise GLUT and open a window
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
  glutInitWindowSize(800, 600);
  glutCreateWindow("Frustum Culling Assignment");
  
  // initialise the random number generator
  srand(2); // fixed seed for reproducibility, otherwise use: srand((unsigned)time(NULL) / 2)
  
  // generate teapots:
  InitTeapots(nrOfTeapots, teapots);
  cout << "Number of Teapots: " << teapots.size() << endl;

  // --- create octree ---
  vector<unsigned int> indices;
  for (unsigned int i = 0; i < teapots.size(); i++)
	  indices.push_back(i);
  // initialise octree
  initNode(&root);

  Subdivide(&root, indices, center, initialCellSize);
  // ----
 
  // initialise OpenGL
  init(); 
  glutMouseFunc(mouseClick);
  glutMotionFunc(mouseDrag);
  glutDisplayFunc(display);
  glutKeyboardFunc(key);
  
  glutMainLoop();
  
  return (0);
}
