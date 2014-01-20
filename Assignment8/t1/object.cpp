#include "object.h"
#include<math.h>

// ============================================================================
//    REFLECT / REFRACT RAYS ABOUT THE NORMAL
// ============================================================================

Ray Object::Reflect(Ray r, Vec3d hit, Vec3d n)
{
	Vec3d dir; // direction of reflected ray

	// --- Here starts your task ---

	// Compute reflected ray according to surface normal.

	Vec3d cd = r.Dir();
	dir = cd - ( 2 * (cd * n) * n );
	
	// --- Here ends your task ---

	return Ray(hit, dir);
}

Ray Object::Refract(Ray r, Vec3d hit, Vec3d n )
{
	Vec3d dir;

	// --- Here starts your task ---

	// Compute refracted ray according to surface normal and ratio kn of
	// refractive indices, i.e. kn = n2/n1. Consider the direction the ray is
	// coming from with respect to the surface normal direction (in one case 
	// there is a transition between a material with index n2 to a material with
	// index n1 and vice versa in the other case). The medium with index n1 is
	// the one in the half space defined by the normal direction.
	Vec3d cd = r.Dir();
	dir =
        (1 / kn) *
        (cd - n * (cd * n)) -
        n * sqrt(1 - (pow(1 / kn, 2) * (1 - pow(cd * n, 2))));
	
	// --- Here ends your task ---

	return Ray(hit, dir);
}
