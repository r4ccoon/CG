//
//  main.cpp
//  Assignment6
//
//  Created by Ridho, Rohan, Zeeshan
//
//  please ctrl+f HS2RGB to find the required implementatsion of the assignment

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
#define PI 3.14159
#define r360_pi 114.591559026
#define r180_pi 57.2957795131

#include <cstdio>
using namespace std;

int width = 640;
int height = 480;
const float _light = 0.5;

// a class of a generic triangle.
class Circle {
    public :
    GLint circle_points;
    GLdouble radius;
    
    Circle(GLdouble vradius, GLint circlePoint){
        radius = vradius;
        circle_points = circlePoint;
    }
    
    // draw the Circle
    void Draw(void){
        glBegin(GL_LINE_LOOP);
        
        // set color lines
        glColor3f(0,0,1);
 
        double angle = 2 * PI / circle_points ;
        double angle1 = 0.0; 
        
        glVertex2d(cos(0.0) * radius, sin(0.0) * radius);

        for (int i = 0; i < circle_points; i++){
            glVertex2d(cos(angle1) * radius, sin(angle1) * radius);
            angle1 += angle ;
        }
        
        glEnd();
    }
};


class Plane {
    public :
    GLdouble L;
    
    Plane(GLdouble vL){
        L = vL;
    }
    
    // draw the Plane
    void Draw(void){
        // set color lines
        glColor3f(0,0,1);
        
        glBegin(GL_LINE_LOOP);
        glVertex2d(-L, L);
        glVertex2d( L, L);
        glVertex2d( L, -L);
        glVertex2d( -L, -L);
        
        glEnd();
    }
    
    void color(){
        float step = L/255;
        
        glBegin(GL_POINTS);
        float i = 0;
        
        float maxAng = 0;
        float minAng = 0;
        
        for(float x = -L; x < L; x += step){
            for(float y = -L; y < L; y += step){
                int rgb[3] = {0,0,0};
                
                double sat = Plane::saturation(x, y, L);
                float rad = fabs(atan2f(y, x));
                int angle = fabs(rad * r360_pi);
                
                // for debug info
                if(maxAng < angle)
                    maxAng = angle;
                if(minAng > angle)
                    minAng = angle;
                
                HS2RGB(angle, sat, rgb);
                //glColor3b(255 ,53 ,30);
                glColor3b (rgb[0] , rgb[1] , rgb[2] );
                
                //printf("angle = %f  \n", rad);
                //printf("color = %i %i %i \n", rgb[0], rgb[1], rgb[2]);
                glVertex2f( x , y );
                
                i++;
            }
        }
        
        // for debug info
        printf("max angle = %f \n", maxAng);
        printf("min angle = %f \n", minAng);
        printf("total = %f \n", i);
        
        glEnd();
        glFlush();
    }
    
    static void HS2RGB(float h, float S, int vRGB[]){
        float r,g,b = 0.0f;
        
        float L = _light;
        float C = ( 1 - fabs( 2 * L - 1 ) ) * S;
        float X = C * ( 1 - fabs( fmod( ( h / 60 ), 2 ) - 1 ) );
        float M = L - ( C / 2 );
        
        if ( h < 60 ) {
            r = C;
            g = X;
            b = 0;
        } else if ( h < 120 ) {
            r = X;
            g = C;
            b = 0;
        } else if ( h < 180 ) {
            r = 0;
            g = C;
            b = X;
        } else if ( h < 240 ) {
            r = 0;
            g = X;
            b = C;
        } else if ( h < 300 ) {
            r = X;
            g = 0;
            b = C;
        } else {
            r = C;
            g = 0;
            b = X;
        }
        
        r = ( r + M ) * 255;
        g = ( g + M ) * 255;
        b = ( b + M ) * 255;
        
        vRGB[0] = floor( fabs(r) );
        vRGB[1] = floor( fabs(g) );
        vRGB[2] = floor( fabs(b) );
    }
    
    static float saturation(float x, float y, float Length){
        float _length = sqrt((x*x) + (y*y));
        
        float denome = Length;
        // avoid div by 0
        if(Length == 0)
            denome = 0.01f;
        
        return _length / denome;
    }
    
};

class Square{
private:
    int _x, _y;
    int _x2, _y2;
    int _mouseClick = 0;
    GLdouble L;
    const int _interpolateStep = 150;
    
    int _rgb[3];
    int _rgb2[3];
    
    float _hls[3];
    float _hls2[3];
    
    public :
    
    Square(GLdouble vL){
        L = vL;
    }
    
    void MouseClick(int x, int y){
        _mouseClick ++;
        
        if(_mouseClick > 1){
            _mouseClick = 0;
        }
        
        if(_mouseClick == 1)
            SetColorPosition(x, y);
        else
            SetColorPosition2(x, y);
    }
    
    void color(){
        color1();
        color2();
        colorInterpolateRGB();
        colorInterpolateHLS();
        line();
    }
    
private:
    void SetColorPosition(int x, int y){
        _x = x;
        _y = y;
    }
    
    void SetColorPosition2(int x, int y){
        _x2 = x;
        _y2 = y;
    }
    
    void line(){
        glColor3f( 0, 0, 0);
        glBegin(GL_LINES);
        glVertex2i(_x, _y);
        glVertex2i(_x2, _y2);
        glEnd();
    }
    
    float interpolate(int startValue, int endValue, int lastStepNumber, int stepNumber)
    {
        float t = (float)lastStepNumber / stepNumber;
        return startValue + (endValue - startValue) * t;
    }
    
    void colorInterpolateRGB(){
        glBegin(GL_POINTS);
        
        float start = - width/2;
        
        for(float x = start; x < start + L; x ++){
            int interpolateVar = 1;
            for(float y = L + 10; y < L + 10 + 150; y ++){
                int rgb[3] = {0, 0, 0};
                
                rgb[0] = interpolate(_rgb[0], _rgb2[0], interpolateVar, _interpolateStep);
                rgb[1] = interpolate(_rgb[1], _rgb2[1], interpolateVar, _interpolateStep);
                rgb[2] = interpolate(_rgb[2], _rgb2[2], interpolateVar, _interpolateStep);
                
                glColor3b (rgb[0] , rgb[1] , rgb[2] );
                glVertex2f( x , y );
                
                interpolateVar++;
            }
        }
        glEnd();
    }
    
    void colorInterpolateHLS(){
        glBegin(GL_POINTS);
        
        float start = - width/2;
        for(float x = start + L; x < start + L + L; x ++){
            int interpolateVar = 1;
            for(float y = L + 10; y < L + 10 + 150; y ++){
                float hls[3] = {0.0f, 0.0f, 0.0f};
                int rgb[3] = {0,0,0};
                
                hls[0] = interpolate(_hls[0], _hls2[0], interpolateVar, _interpolateStep);
                hls[1] = interpolate(_hls[1], _hls2[1], interpolateVar, _interpolateStep);
                hls[2] = interpolate(_hls[2], _hls2[2], interpolateVar, _interpolateStep);
                
                Plane::HS2RGB(hls[0], hls[1], rgb);
                
                glColor3b (rgb[0] , rgb[1] , rgb[2] );
                glVertex2f( x , y );
                
                interpolateVar++;
            }
        }
        printf("coord = %i %i \n", _x, _y);
        glEnd();
    }
    
    void color1(){
        glBegin(GL_POINTS);
        
        float start = - width/2;
        for(float x = start; x < start + L; x ++){
            for(float y = 0; y < L; y ++){
                int rgb[3] = {0, 0, 0};
                
                double sat = Plane::saturation(_x, _y, L);
                float rad = fabs(atan2f(_y, _x));
                float angle = fabs(rad * r360_pi);
                
                Plane::HS2RGB(angle, sat, rgb);
                
                _rgb[0] = rgb[0];
                _rgb[1] = rgb[1];
                _rgb[2] = rgb[2];
                
                _hls[0] = angle;
                _hls[1] = sat;
                _hls[2] = _light;

                glColor3b (rgb[0] , rgb[1] , rgb[2] );
                glVertex2f( x , y );
            }
        }
        printf("coord = %i %i \n", _x, _y);
        glEnd();
    }
    
    void color2(){
        glBegin(GL_POINTS);
        
        float start = - width/2;
        for(float x = start + L; x < start + L + L; x ++){
            for(float y = 0; y < L; y ++){
                int rgb[3] = {0, 0, 0};
                
                double sat = Plane::saturation(_x2, _y2, L);
                float rad = fabs(atan2f(_y2, _x2));
                float angle = fabs(rad * r360_pi);
                
                Plane::HS2RGB(angle, sat, rgb);
                
                _rgb2[0] = rgb[0];
                _rgb2[1] = rgb[1];
                _rgb2[2] = rgb[2];
                
                _hls2[0] = angle;
                _hls2[1] = sat;
                _hls2[2] = _light;
                
                glColor3b (rgb[0] , rgb[1] , rgb[2] );
                glVertex2f( x , y );
            }
        }
        
        printf("coord2 = %i %i \n", _x2, _y2);
        glEnd();
    }
};

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

// initiate the triangle that we want to draw
Circle theCircle = Circle(100, 64);
Plane thePlane = Plane(100);
Square pickedColor = Square(40);

// method to be passed to glutdisplayfunc to draw the triangle lines and colors
void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);
    
    theCircle.Draw();
    thePlane.color();
    pickedColor.color();
    
    glFlush();
}

void mouseMap(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
            pickedColor.MouseClick(x, y);
        }
	}
    
    glutPostRedisplay();
}

void mouseDrag(int x, int y)
{
	pickedColor.MouseClick(x, y);
    glutPostRedisplay();
}

int main( int argc, char* argv[] )
{
	glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(width, height);
    glutCreateWindow("Assignment 6, task 1");
    
    init();
    
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
	glutMotionFunc(mouseDrag);
    
	glutMouseFunc(mouseMap);
    
    glutMainLoop();
    
	return 0;
}

