//
//  main.cpp
//  Assignment6
//
//  Created by Ridho, Rohan, Zeeshan on 6/11/2013.
//
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

#include <math.h>
#define PI 3.14159
#define r180_pi 57.2957795131

#include <cstdio>
using namespace std;

int width = 120;
int height = 120;

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
        glFlush();
    }
};

void HSL2RGB(double h, double sl, double l, GLfloat *rgb)
{
    double v;
    double r,g,b;
    
    r = l;
    g = l;
    b = l;
    
    v = (l <= 0.5) ? (l * (1.0 + sl)) : (l + sl - l * sl);
    if (v > 0)
    {
        double m;
        double sv;
        int sextant;
        double fract, vsf, mid1, mid2;
        
        m = l + l - v;
        sv = (v - m ) / v;
        h *= 6.0;
        sextant = (int)h;
        fract = h - sextant;
        vsf = v * sv * fract;
        mid1 = m + vsf;
        mid2 = v - vsf;
        switch (sextant)
        {
            case 0:
                r = v;
                g = mid1;
                b = m;
                break;
            case 1:
                r = mid2;
                g = v;
                b = m;
                break;
            case 2:
                r = m;
                g = v;
                b = mid1;
                break;
            case 3:
                r = m;
                g = mid2;
                b = v;
                break;
            case 4:
                r = mid1;
                g = m;
                b = v;
                break;
            case 5:
                r = v;
                g = m;
                b = mid2;
                break;
        }
    }
    
    rgb[0] = r;// * 255.0f;
    rgb[1] = g;// * 255.0f;
    rgb[2] = b;// * 255.0f;
}


class Plane {
    public :
    GLdouble L;
    
    Plane(GLdouble vL){
        L = vL;
    }
    
    // draw the Circle
    void Draw(void){
        // set color lines
        glColor3f(0,0,1);
        
        glBegin(GL_LINE_LOOP);
        glVertex2d(-L, L);
        glVertex2d( L, L);
        glVertex2d( L, -L);
        glVertex2d( -L, -L);
        
        glEnd();
        glFlush();
    }
    
    void color(){
        float step = 1.0f/255;
        step = 0.009;
        glBegin(GL_POINTS);
        float i = 0;
        for(float x = -L; x < L; x += step){
            for(float y = -L; y < L; y += step){
                GLfloat rgb[3] = {0,0,0};
                
                double sat = saturation(x, y);
                float rad = fabs(atan2f(y, x));
                float angle = rad * r180_pi;
                if(angle < 0)
                    angle = angle * -2;
                
                HSL2RGB(rad, sat, 0.5, rgb);
                glColor3f (rgb[0] , rgb[1] , rgb[2] );
                
                printf("angle = %f  \n", rad);
                printf("color = %f %f %f \n", rgb[0], rgb[1], rgb[2]);
                glVertex2f( x , y );
                
                i++;
            }
        }
        
        printf("total = %f \n", i);
        
        glEnd();
        glFlush();
    }
    
    float saturation(float x, float y){
        float length = sqrt((x*x) + (y*y));
        
        float denome = L;
        // avoid div by 0
        if(L == 0)
            denome = 0.01f;
        
        return length / denome;
    }
    
};

void init(void){
    glClearColor(1.0, 1.0 , 1.0, 1.0);
    glViewport (0, 0, (GLsizei) width, (GLsizei) height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float wh = (float)height/width;
    glOrtho(-1, 1, -wh, wh , -1.0f, 1.0f);
}

void reshape(int w, int h){
    width = w;
    height = h;
    
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float wh = (float)height/width;
    glOrtho(-1, 1, -wh, wh , -1.0f, 1.0f);
}

// initiate the triangle that we want to draw
Circle theCircle = Circle(0.5, 64);
Plane thePlane = Plane(0.5);

// method to be passed to glutdisplayfunc to draw the triangle lines and colors
void draw(void){
    glClear(GL_COLOR_BUFFER_BIT);
    theCircle.Draw();
    thePlane.color();
}

int main( int argc, char* argv[] )
{
	glutInit(&argc, argv);
    
    printf("anglea = %f  \n", atan2(-1, -1));

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(width, height);
    glutCreateWindow("Assignment 6, task 1");
    
    init();
    
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    glutMainLoop();
    
	return 0;
}

