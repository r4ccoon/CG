#ifndef TRACKBALL_H
#define TRACKBALL_H

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


typedef struct 
{
	int x;
	int y;
}	Point;



class Trackball
{
public:
	void start(Point point);
	void rollTo(Point point, GLfloat *r);
	void addToRotation(GLfloat *da, GLfloat *A);



protected:
	GLfloat _radius, _startPt[3], _endPt[3];
	Point _ctr;

	void rotation2Quat(GLfloat *A, GLfloat *q);
};



class SimpleTrackball : public Trackball {

 public:

  SimpleTrackball(){
  	_rotation[0] = _tbRot[0] = _trans[0] = _transTemp[0] = 0.0;
	_rotation[1] = _tbRot[1] = 1.0;
	_rotation[2] = _tbRot[2] = _trans[1] = _transTemp[1] = 0.0;
	_rotation[3] = _tbRot[3] = _trans[2] = _transTemp[2] = 0.0;
	_drag = false;
	_dolly = false;
	_translate = false;
  }

 
  // call in the glutMouseFunc, if state == GLUT_DOWN
  void startBall(int x, int y);  

  // call in the glutMouseFunc, if state == GLUT_UP
  void stopBall(int x, int y);

  // like startBall, but for the translation in the z direction
  void startDolly(int x, int y);
  void stopDolly(int x, int y);  

  // like startBall, but for the translation in the x and y direction
  void startTranslate(int x, int y);
  void stopTranslate(int x, int y);  
  
  // call in the glutMotionFunc
  void rollBall(int x, int y);

  // sets the speed of the translations 
  void setTranslateSpeed(GLfloat translateSpeed) { _translateSpeed = translateSpeed; }

  // multiplies the active matrix with the rotation of the trackball
  // (e.g. call in the display function)
  void multModelMatrix();


 private:
  void rotateBy(GLfloat *r);
  GLfloat _rotation[4], _tbRot[4], _trans[3],_transTemp[3];
  GLfloat _translateSpeed;
  bool _drag;
  bool _dolly;
  bool _translate;
};

#endif
