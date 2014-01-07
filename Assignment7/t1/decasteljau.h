//
//  decasteljau.h
//  Assignment7
// 
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

	void reshape(int w, int h){
		_height = h;
		_width = w;
	}
    
    void MouseClick(int x, int y){
		// convert to our y coordinate
        float vy = -1 * (y - _height);

        printf("adding point x y = %d %f \n", x, vy );
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
		drawCasteljau();
        glFlush();
    }
    
private:    
	int _height = 480;
	int _width = 600;

	int iter = 0;
    Point* _points[100];
    const float _interpolateStep = 0.01;

	void drawCasteljau() {
		// dont do if points 0 is null
		if (_points[0] == NULL)
			return;

		glColor3f(0, 0, 0);

		glBegin(GL_LINE_STRIP); 
		for (double t = 0; t <= 1; t += _interpolateStep) {
			Point tmp = getCasteljauPoint(iter - 1 , 0, t); 
			 
			// draw the line 1 by 1
			glVertex2d(tmp.x, tmp.y);
		}
		glEnd();
	}


	Point getCasteljauPoint(int r, int i, double t) {
		// return if its only 1 points in the program yet
		if (r == 0) 
			return Point(_points[i]->x, _points[i]->y, 0);

		Point p1 = getCasteljauPoint(r - 1, i, t);
		Point p2 = getCasteljauPoint(r - 1, i + 1, t);

		return Point(
			(int)((1 - t) * p1.x + t * p2.x), 
			(int)((1 - t) * p1.y + t * p2.y), 
			0
		);
	}
    
    ///
    /// draw line from color 1 to color 2
    ///
    void drawStraightLines(){
        glColor3f( 1, 0, 0);

		glBegin(GL_LINE_STRIP);
        for(int i = 0; i <= iter;i++){
            Point* point2 = _points[i];
            if(point2 != NULL){
                glVertex2f(point2->x, point2->y);
            } 
		}
		glEnd();
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
     
};



#endif