#ifndef _PLANE_H_
#define _PLANE_H_

#include "vec3.h"
#include "object.h"
#include "ray.h"

class Plane : public Object {

protected:
	Vec3d pos;     // POINT ON INFINITE PLANE
	Vec3d normal;  // NORMAL

public:
	// CONSTRUCTOR
	Plane(const Vec3d p, const Vec3d n) { pos=p; normal=n; }
	Plane(const Vec3d p, const Vec3d n,
	      const Vec3d amb, const Vec3d diff, const Vec3d spec,
	      const bool refl, const bool trans,
	      const double Kd=1.0, const double Ks=0.9,
	      const double Kt=1.0, const double Kn=1.0);

	// FUNCTIONS FOR INTERSECTING / SHADING
	bool findIntersection(Ray incoming, Vec3d *point, Vec3d *normal);
};

#endif