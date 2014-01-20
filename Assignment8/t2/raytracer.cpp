/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 43):
 * {glenn.dwiyatcita, volkan.guenal}@rwth-aachen.de modified this file. 
 * As long as you retain this notice you can do whatever you want with this stuff. 
 * If we meet some day, and you think this stuff is worth it, you can buy us 
 * a beer in return.        Glenn Mohammad/Vo Günal **
 * **In collaboration with Alexander Kotlov/Sigit Nugroho
 * ----------------------------------------------------------------------------
 *
 * $Id: raytracer.cpp, a08-t1 2012/01/17 01:55:00 g_mohammad v_günal Exp $
 */

#include "raytracer.h"

// On Windows M_PI is not defined by default 
#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

#include <algorithm>
#include <math.h>
#include <iostream>
using std::min;
using std::max;
using std::cout;

//----------------------------------------------------------------------------
//   CONSTRUCTOR / DESTRUCTOR
//----------------------------------------------------------------------------
RayTracer::RayTracer(const int x, const int y)
{
	resX=x;  resY=y;
	framebuffer = new ppmGL2d(resX,resY);
	globalAmbient.Set(1,1,1);
}

RayTracer::~RayTracer()
{
	RemoveAllObjects();
	RemoveAllLights();
	delete framebuffer;
}

//----------------------------------------------------------------------------
//   CALCULATE THE RAY
//----------------------------------------------------------------------------
void RayTracer::calcRay(Ray *r, int x, int y)
{
	// --- Here starts your task ---

	// Compute a ray from the eyepoint through the pixel x,y.
	// The ray has to be returned by setting position and direction of the given  
	// ray pointer r using the setter functions r->Pos(...) and r->Dir(...).
	// The returned ray direction should be normalized.

	// One possible approach:
	// - first compute the 4 corner rays of the viewing frustum
	// - and then determine the ray direction for pixel (x,y) via linear interpolation
	Vec3d vectorE = cam.Eye(); // camera position e
	Vec3d vectorW = -(cam.LookAt() - cam.Eye()); // viewing direction -w
	Vec3d vectorT = cam.Up(); // a view up vector t
	Vec3d vectorU = vectorT ^ vectorW; 
	Vec3d vectorV = vectorW ^ vectorU;
	vectorW.Normalize();
	vectorU.Normalize();
	vectorV.Normalize();
	
	double d = vectorW.Length(); // distance to near plane (z-near)
	double aspect = resX / resY;
	double top = d * tan(cam.FOVy());
	double right = top * aspect;
	double bottom = -top;
	double left = bottom * aspect;
	double u = left + ((right - left) * (x + 0.5)) / resX;
	double v = bottom + ((top - bottom) * (y + 0.5)) / resY;
	
	Vec3d rayDirection = (d * -vectorW) + (u * vectorU) + (v * vectorV);
	Vec3d rayPosition = vectorE + rayDirection;
	rayDirection.Normalize();
	r->Pos(rayPosition);
	r->Dir(rayDirection);
	
	// --- Here ends your task ---
}

//----------------------------------------------------------------------------
//   TRACE A RAY THROUGH THE SCENE
//----------------------------------------------------------------------------
Color RayTracer::traceRay(Ray r, int depth)
{
	Color C;

	// --- Here starts your task ---

	// Input arguments:
	//  r       incoming ray 
	//  depth   recursion depth (increment depth in recursive call)

	// To access an intersected scene object, you can use the index returned by
	// findFirstIntersection() to address the scene object array.
	// E.g. scene[hitIndex]->Kt() for the refractive coefficient.
	C.Set(0, 0, 0);
	if (depth <= MAXDEPTH)
	{
		Vec3d hitPoint, normal;
		int hitIndex = findFirstIntersection(r, &hitPoint, &normal);
		if (hitIndex == -1)
		{
			return background;
		}
		else
		{
			Color cDirect = shadeWhitted(r, hitIndex, hitPoint, normal);
			Color reflectiveTerm = Vec3d::ZERO;
			Color refractiveTerm = Vec3d::ZERO;
			
			Object* hitObject = scene[hitIndex];
			if (hitObject->Reflective()) 
			{
				Ray reflectionRay = hitObject->Reflect(r, hitPoint, normal);
				reflectiveTerm = traceRay(reflectionRay, depth + 1);
			}
			if (hitObject->Transparent()) 
			{
				Ray refractionRay = hitObject->Refract(r, hitPoint, normal);
				refractiveTerm = traceRay(refractionRay, depth + 1);
			}
			
			C = cDirect + (hitObject->Ks() * reflectiveTerm) + (hitObject->Kt() * refractiveTerm);
		}
	}
	
	// --- Here ends your task ---

	return C;
}
//----------------------------------------------------------------------------
//   RENDER THE SCENE
//----------------------------------------------------------------------------
void RayTracer::Render(const char *filename)
{
	Ray r;
	framebuffer->ClearColor();

	int prevHit=0;

	for (int i=0; i<resY; i++) {
		printf(".", i);
		prevHit=0;
		for (int j=0; j<resX; j++) {

			// CALCULATE THE RAY DIRECTION
			calcRay(&r,j,i);

			// TRACE THE RAY
			Color color = traceRay(r, 0);

			// CLAMP COLOR VALUES
			color.x = (color.x > 1) ? 1 : (color.x < 0) ? 0 : color.x;
			color.y = (color.y > 1) ? 1 : (color.y < 0) ? 0 : color.y;
			color.z = (color.z > 1) ? 1 : (color.z < 0) ? 0 : color.z;

			// DRAW THE COLOR INTO THE FRAMEBUFFER
			framebuffer->SetForeground((float)color.x, (float)color.y, (float)color.z);
			framebuffer->SetPixel(j,resY-i-1);  // X,Y COORDINATE INVERTED IN DRAWING ROUTINE
		}
	}

	framebuffer->MakePPM(filename);
}

//----------------------------------------------------------------------------
//   SHADE AN OBJECT, TEST FOR SHADOWS  (TURNER-WHITTED STYLE SHADING)
//----------------------------------------------------------------------------
Color RayTracer::shadeWhitted(Ray r, int curHit, Vec3d hit, Vec3d n)
{
	int index;
	Vec3d p, norm, ldir, ldist;
	Object *obj = scene[curHit];

	// INITIALIZE WITH AMBIENT COLOR
	Color c = obj->Ambient();  

	// FOR EACH LIGHT...
	for (int i=0; i<lights.Length(); i++) {
		// CAST A RAY INTO LIGHT DIRECTION
		ldir  = lights[i]->Pos() - hit;
		ldist = ldir;
		ldir.Normalize();
		Ray newR(hit, ldir);

		// CAST A SHADOW FEELER TOWARDS LIGHT
		index = findFirstIntersection(newR, &p, &norm);
		Vec3d dist = p - hit;
		if (  dist.Length() > ldist.Length() // hit not between p and light
			|| index==-1 ) 
		{
			// LAMBERT SHADING
			Color cObj = obj->Kd() * obj->Diffuse() * max(0.0, n * ldir);
			
			// ADD SPECULAR TERM IF OBJECT IS REFLECTIVE
			if( obj->Reflective() )
			{
				// HALF WAY VECTOR
				Vec3d h = (ldir-r.Dir()).Normalize();
				// PHONG SHADING
				cObj += obj->Ks() * obj->Specular() 
				     * pow(max(0.0, n * h), obj->Shininess());
			}

			// ADD COLOR CONTRIBUTION
			c += lights[i]->Intensity() * cObj;
		}
	}

	return c;
}

//----------------------------------------------------------------------------
//   FIND THE FIRST INTERSECTION & NORMAL
//----------------------------------------------------------------------------
int RayTracer::findFirstIntersection(Ray r, Vec3d *pt, Vec3d *normal)
{
	Vec3d point, n, tmp1, tmp2;
	tmp2 = r.Pos();                               // INITIALIZE TO RAY ORIGIN
	int index = -1;                               // NO HITS YET
  
	// FOR EACH OBJECT IN THE SCENE...
	for (int i=0; i<scene.Length(); i++) {
		if (scene[i]->findIntersection(r, &point, &n)) {
			tmp1 = point - r.Pos();

			// FIND CLOSEST INTERSECTION
			if (tmp1.Length() < tmp2.Length() || index==-1) {
				*pt = point;
				*normal = n;
				index = i;
			  tmp2 = *pt - r.Pos();
			}
		}
	}

	return index;
}
