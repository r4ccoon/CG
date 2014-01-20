#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "vec3.h"
#include "object.h"
#include "ray.h"

class Sphere : public Object {

protected:
	Vec3d  pos;    // CENTER POSITION
	double radius; // RADIUS

public:
	// CONSTRUCTOR
	Sphere(const Vec3d p, const double r) { pos=p; radius=r; }
	Sphere(const Vec3d p, const double r,
	       const Vec3d amb, const Vec3d diff, const Vec3d spec,
	       const bool   refl,   const bool   trans, 
	       const double Kd=1.0, const double Ks=0.9, 
	       const double Kt=1.0, const double Kn=1.0 );

	// FUNCTIONS FOR INTERSECTING / SHADING
	bool findIntersection(Ray incoming, Vec3d *point, Vec3d *normal);
};

#endif
