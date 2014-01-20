#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "vec3.h"
#include "ray.h"
#include "light.h"
#include "array.h"

// USED FOR INTERSECTION TEST
#define EPSILON 0.000001

// COLOR DEFINITION
typedef Vec3d Color;

class Object {
protected:
	Color  diffuse;      // DIFFUSE COLOR
	Color  ambient;      // AMBIENT COLOR
	Color  specular;     // SPECULAR COLOR
	Color  emission;     // EMISSION COLOR
	double kd;           // DIFFUSE REFLECTION CONSTANT
	double ks;           // SPECULAR REFLECTION CONSTANT
	double kt;           // TRANSMISSION COEFFICIENT
	double kn;           // QUOTIENT OF INDICES OF REFRACTION (DEFAULT 1.0)
	double shininess;    // SHININESS OF MATERIAL
	bool   reflective;   // REFLECTIVE? 
	bool   transparent;  // TRANSPARENT?

public:
	// QUERY OBJECT
	Color  Diffuse()     { return diffuse;  }    // DIFFUSE COLOR
	Color  Ambient()     { return ambient;  }    // AMBIENT COLOR
	Color  Specular()    { return specular; }    // SPECULAR COLOR
	Color  Emission()    { return emission; }    // MATERIAL EMISSION
	double Kd()          { return kd; }          // DIFFUSE CONSTANT
	double Ks()          { return ks; }          // SPECULAR CONSTANT
	double Kt()          { return kt; }          // REFRACTION CONSTANT
	double Kn()          { return kn; }          // INDEX OF REFRACTION
	double Shininess()   { return shininess;   } // MATERIAL SHININESS
	int    Reflective()  { return reflective;  } // IS THE SURFACE REFLECTIVE?
	int    Transparent() { return transparent; } // IS THE SURFACE TRANSPARENT?

	// SETUP OBJECT
	void Diffuse( double r, double g, double b) { diffuse.Set(r,g,b);  } // DIFFUSE COLOR
	void Ambient( double r, double g, double b) { ambient.Set(r,g,b);  } // AMBIENT COLOR
	void Specular(double r, double g, double b) { specular.Set(r,g,b); } // SPECULAR COLOR
	void Kd(double v) { kd = v; }            // DIFFUSE CONSTANT
	void Ks(double v) { ks = v; }            // SPECULAR CONSTANT
	void Kt(double v) { kt = v; }            // REFRACTION CONSTANT
	void Kn(double v) { kn = v; }            // INDEX OF REFRACTION
	void Shininess( double s ) { shininess = s; } // MATERIAL SHININESS
	void Reflective ( bool b ) { reflective  = b; }  // IS THE SURFACE REFLECTIVE?
	void Transparent( bool b ) { transparent = b; }  // IS THE SURFACE TRANSPARENT?

	// REFLECT / REFRACT RAYS ABOUT THE NORMAL
	Ray Reflect(Ray r, Vec3d intersection, Vec3d normal);
	Ray Refract(Ray r, Vec3d intersection, Vec3d normal);

	// VIRTUAL FUNCTIONS FOR INTERSECTION COMPUTATION
	// - point of intersection of incoming ray with this object
	// - surface normal at point of intersection
	virtual bool findIntersection(Ray incoming, Vec3d *point, Vec3d *normal) = 0;
};

#endif
