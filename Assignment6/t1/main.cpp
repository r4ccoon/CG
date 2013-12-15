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
#define r360_pi 114.591559026

#include <cstdio>
using namespace std;

int width = 360;
int height = 360;

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
        //step = 0.009;
        glBegin(GL_POINTS);
        float i = 0;
        for(float x = -L; x < L; x += step){
            for(float y = -L; y < L; y += step){
                GLfloat rgb[3] = {0,0,0};
                
                double sat = saturation(x, y);
                float rad = atan2f(y, x);
                float angle = fabs(rad * r360_pi);
                
                HS2RGB(rad, sat, rgb);
                glColor3f (rgb[0] , rgb[1] , rgb[2] );
                
                //printf("angle = %f  \n", rad);
                printf("color = %f %f %f \n", rgb[0], rgb[1], rgb[2]);
                glVertex2f( x , y );
                
                i++;
            }
        }
        
        printf("total = %f \n", i);
        
        glEnd();
        glFlush();
    }
    
    void HS2RGB(float H, float S, GLfloat *rgb){
         float L = 0.5;
        
         if ( S == 0 )                       //HSL from 0 to 1
         {
             rgb[0] = L * 1;                      //RGB results from 0 to 1
             rgb[1] = L * 1;
             rgb[2] = L * 1;
         }
         else
         {
             float var_2 , var_1 = 0.0f;
             if ( L < 0.5 )
                 var_2 = L * ( 1 + S );
             else
                 var_2 = ( L + S ) - ( S * L );
         
             var_1 = 2 * L - var_2;
        
             rgb[0] = 1 * Hue_2_RGB( var_1, var_2, H + ( 1 / 3 ) );
             rgb[1] = 1 * Hue_2_RGB( var_1, var_2, H );
             rgb[2] = 1 * Hue_2_RGB( var_1, var_2, H - ( 1 / 3 ) );
         }        
    }
    
    float Hue_2_RGB( float v1, float v2, float vH )
    {
        if ( vH < 0 )
            vH += 1;
        
        if ( vH > 1 )
            vH -= 1;
        
        if ( ( 6 * vH ) < 1 )
            return ( v1 + ( v2 - v1 ) * 6 * vH );
        
        if ( ( 2 * vH ) < 1 )
            return ( v2 );
        
        if ( ( 3 * vH ) < 2 )
            return ( v1 + ( v2 - v1 ) * ( ( 2 / 3 ) - vH ) * 6 );
     
        return ( v1 );
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

