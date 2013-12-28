 
#ifndef Assignment7_deboor_h
#define Assignment7_deboor_h

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
class Deboor{

public :
	Deboor(){
		knots[0] = 0;
		knots[1] = 0;
		knots[2] = 0; 
		knots[3] = 0; 
		knots[4] = 1; 
		knots[5] = 2; 
		knots[6] = 3; 
		knots[7] = 3; 
		knots[8] = 3; 
		knots[9] = 3;	  
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
		drawBSplines();
        glFlush();
    }
    
private:    
	int _height = 480;
	int _width = 600;

	int iter = 0;
    Point* _points[100];
    const float _interpolateStep = 0.01;  
	const int degree = 3;

	float knots[10];
    
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

	// 
	float deBoor(int n, int i, float t, float* knots)
	{
		if (n == 0)
		{
			if ((knots[i] <= t) && (t < knots[i + 1]))
				return 1;

			return 0;
		}
		else
		{
			float denominator1 = knots[i + n] - knots[i];
			float denominator2 = knots[i + n + 1] - knots[i + 1];
			float quotient1 = (denominator1 == 0) ? 0 : (t - knots[i]) / denominator1;
			float quotient2 = (denominator2 == 0) ? 0 : (knots[i + n + 1] - t) / denominator2;

			return quotient1 * deBoor(n - 1, i, t, knots) + quotient2 * deBoor(n - 1, i + 1, t, knots);
		}
	}

	void drawBSplines()
	{  
		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_STRIP);
		for (float t = 0; t <= degree; t += _interpolateStep)
		{
			Point p;
			for (int i = 0; i < iter; ++i)
			{
				float deBoorCoefficient = deBoor(degree, i, t, knots);
				p.x += _points[i]->x * deBoorCoefficient;
				p.y += _points[i]->y * deBoorCoefficient;
			}
			glVertex2f(p.x, p.y);
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