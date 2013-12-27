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
 * point struct
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
        float vy = -1*(y - 480);
        printf("x y = %d %f \n", x, vy );
        _points[iter] = new Point(x, vy, 0);
        iter++;
    }
    
    // reset all the points
    void RightMouseClick(){
        for(int i = 0; i <= iter;i++){
            if(_points[i] != NULL)
                // unset all point
                _points[i] = NULL;
        }
        // reset point counter
        iter = 0;
    }
    
    // methods to call all draw colors
    void Draw(){
        drawPoints();
        drawStraightLines();
        glFlush();
    }
    
private:
    int iter = 0;
    Point* _points[100];
    const int _interpolateStep = 0.2;
    
    ///
    /// draw line from color 1 to color 2
    ///
    void drawStraightLines(){
        glColor3f( 0, 0, 0);
        
        for(int i = 0; i <= iter;i++){
            glBegin(GL_LINES);
            if(i > 0){
                Point* point1 = _points[i - 1];
                if(point1 != NULL){
                    glVertex2f(point1->x, point1->y);
                }
            }
            
            Point* point2 = _points[i];
            if(point2 != NULL){
                glVertex2f(point2->x, point2->y);
            }
            glEnd();
        }
    }
    
    void drawBezier(){
        
    }
    
    ///
    ///
    ///
    void drawPoints(){
        glColor3f(1.0f, 0.0f, 0.0f);
        glPointSize(5);
        
        glBegin(GL_POINTS);
        for(int i = 0; i <= iter;i++){
            Point* point = _points[i];
            if(point != NULL){
                glVertex2f(point->x, point->y);
            }
        }
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