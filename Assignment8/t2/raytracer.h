#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_

#include "vec3.h"
#include "ray.h"
#include "ppmgl2d.h"
#include "array.h"
#include "object.h"
#include "camera.h"

// MAXIMUM RECURSION DEPTH
#define MAXDEPTH 5
#define PI 3.1415926535897932384626433832795029

class RayTracer {

protected:
	Camera cam;               // CAMERA
	int    resX;              // RESOLUTION IN X-DIMENSION
	int    resY;              // RESOLUTION IN Y-DIMENSION

	Color   globalAmbient;    // GLOBAL AMBIENT COLOR OF SCENE
	Color   background;
	ppmGL2d *framebuffer;     // FRAMEBUFFER

	Array<Object*> scene;     // DYNAMIC ARRAY OF OBJECTS IN THE SCENE
	Array<Light*>  lights;    // DYNAMIC ARRAY OF LIGHTS

	void calcRay(Ray *r, int x, int y); // CALCULATE DIRECTION OF RAY

	// TRACE A RAY, RETURN ITS COLOR
	Color traceRay(Ray r, int depth);
	
	// WHITTED STYLE SHADING
	Color shadeWhitted(Ray r, int curHit, Vec3d hit, Vec3d n);

	// OPENGL STYLE SHADING
	Color shadeGL     (Ray r, int curHit, Vec3d hit, Vec3d n);

	// FIND FIRST OBJECT OF INTERSECTION
	// [in]  r      : ray
	// [out] pt     : intersection point (if found)
	// [out] normal : normal at intersection point
	// Returns index of intersected scene object if intersection found, 
	// otherwise returns -1.
	int findFirstIntersection(Ray r, Vec3d *pt, Vec3d *normal);

public:
	// CONSTRUCTOR / DESTRUCTOR
	RayTracer(const int x, const int y);
	~RayTracer();

	// SETUP THE CAMERA
	void SetCamera(const Vec3d eyept, const Vec3d look,
		             const Vec3d eyeup, const double view)
	{ cam.Eye(eyept); cam.LookAt(look); cam.Up(eyeup); cam.FOVy(view); }
	void SetCamera(const Camera c) { cam = c; }

	// CHANGE THE SCENE
	void AddObject(Object *obj)	        { scene.Add_Grow(obj,1); }
	void AddLight(Light *l)             { lights.Add_Grow(l,1); }
	void RemoveAllObjects()             { scene.Destroy();  }
	void RemoveAllLights()              { lights.Destroy(); }
	void GlobalAmbient(const Color amb) { globalAmbient = amb; }
	void SetBackground(const double r, const double g, const double b)
	{ background = Color(r, g, b); 
	 framebuffer->SetBackground((float)r,(float)g,(float)b); }

	// DRAW THE SCENE
	void Render(const char *filename);
};

#endif