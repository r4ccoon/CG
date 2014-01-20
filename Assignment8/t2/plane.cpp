#include "plane.h"

#include <algorithm>
using std::min;
using std::max;

//----------------------------------------------------------------------------
//   CONSTRUCTOR / DESTRUCTOR
//----------------------------------------------------------------------------
Plane::Plane(const Vec3d p,   const Vec3d n,
             const Vec3d amb, const Vec3d diff, const Vec3d spec,
             const bool refl, const bool trans, 
             const double Kd, const double Ks,
             const double Kt, const double Kn)
{
	pos      = p;
	normal   = n;
	diffuse  = diff;
	ambient  = amb;
	specular = spec;
	reflective  = refl;
	transparent = trans;
	kd = Kd;
	ks = Ks;
	kt = Kt;
	kn = Kn;
	emission.Set(0,0,0);
	shininess = (refl) ? 100.0 : 0.0;
}

//----------------------------------------------------------------------------
//   FIND THE INTERSECTION POINT AND NORMAL OF A RAY AND OBJECT
//----------------------------------------------------------------------------
bool Plane::findIntersection(Ray incoming, Vec3d *point, Vec3d *n)
{
	// SOLVE FOR t
	double numerator   = (pos - incoming.Pos()) * normal;
	double denominator = incoming.Dir() * normal;

	if (denominator == 0)    // RAY PARALLEL TO PLANE
		return false;

	// FIND THE EXACT INTERSECTION POINT, NORMAL IS SAME AS PLANE'S NORMAL
	double t = numerator / denominator;

	// MAKE SURE POINT IS NOT THE SAME ONE WE JUST HIT
	if (t < EPSILON)
		return false;

	*point = incoming.Pos() + t*incoming.Dir();
	*n = normal;
	n->Normalize();
	if (*n*incoming.Dir() > 0)  // INVERT THE NORMAL IF DOT PRODUCT POSITIVE
		*n *= -1;

	// CUT OFF PLANE	
	//if( (pos - *point).Length() > 3 ) return false;  // disc cut off
	Vec3d delta = (pos - *point);
	if( max( abs(delta.x), max(abs(delta.y), abs(delta.z)) ) > 3 )
		return false;

	return true;
}
