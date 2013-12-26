//
//  decasteljau.h
//  Assignment7
//
//  Created by Ridho Laksono on 26/12/2013.
//
//

#ifndef Assignment7_decasteljau_h
#define Assignment7_decasteljau_h

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

/**
 *
 */
class Point
{
public:
    Point() : x(0.0), y(0.0), w(1.0) {};
    Point(float x, float y, float w) : x(x), y(y), w(w) {};
    float x;
    float y;
    float w;
};

/**
 *
 * class Decasteljau. class that contains points, lines and the curve
 *
 **/
class Decasteljau{

public :
    Decasteljau(){
    }
    
    void MouseClick(int x, int y){
    }
    
    // reset all the points
    void RightMouseClick(){
    }
    
    // methods to call all draw colors
    void Draw(){
        straightLines();
        glFlush();
    }
    
private:
    Point _points[100];
    const int _interpolateStep = 0.2;
    ///
    /// draw line from color 1 to color 2
    ///
    void straightLines(){
        glColor3f( 0, 0, 0);
        glBegin(GL_LINES);
        
        glVertex2f(0, 0);
        glVertex2f(100, 100);
        
        glEnd();
    }
    
    ///
    /// interpolates step by step
    ///
    float interpolate(float startValue, float endValue, float lastStepNumber, float stepNumber)
    {
        float t = (float)lastStepNumber / stepNumber;
        return  (startValue + (endValue - startValue) * (float)t);
    }
};



#endif