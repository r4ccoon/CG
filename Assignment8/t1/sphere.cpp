#include "sphere.h"

//----------------------------------------------------------------------------
//   CONSTRUCTOR / DESTRUCTOR
//----------------------------------------------------------------------------
Sphere::Sphere( const Vec3d p,   const double r,
	            const Vec3d amb, const Vec3d diff, const Vec3d spec,
	            const bool   refl, const bool trans, 
	            const double Kd,   const double Ks, 
	            const double Kt,   const double Kn)
{
	pos = p;
	radius = r;
	diffuse = diff;
	ambient = amb;
	specular = spec;
	reflective = refl;
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
bool Sphere::findIntersection(Ray incoming, Vec3d *point, Vec3d *normal)
{
	// --- Here starts your task ---
	Vec3d diff = incoming.Pos() - pos;              // we want to find t s.t.: (dist + t * incoming.Dir())^2 = radius^2
	double b = diff * incoming.Dir();               //                     <=> a*t^2 + 2*b*t + c = 0 with b and c as defined here
	double c = diff.LengthSqr() - radius * radius;  //                         and a = incoming.Dir()^2 = 1 (since incoming.Dir() is normalized)
	double d = b * b - c;                           // discrimant of the above quadratic equation
	if (d < 0)                // i.e. if line (extended ray) does not intersect sphere
		return false;
	double t = -b - sqrt(d);  // if we assume a single-sided surface (i.e. that we are looking only from outside onto the sphere), we do not need to consider the second intersection along the line (which is -B + sqrt(D))
	if (t <= EPSILON)     // exclude intersections before and at the starting point of ray (the latter is important for secondary rays during ray tracing)
		return false;
	*point = incoming.Pos() + t * incoming.Dir();
	//assert(fabs((*point - pos).Length() - radius) <= EPSILON);  //(checks that distance of point to pos is radius)
	*normal = (*point - pos) / radius;
	return true;
	// --- Here ends your task ---
}
