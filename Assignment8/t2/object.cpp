/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 43):
 * {glenn.dwiyatcita, volkan.guenal}@rwth-aachen.de modified this file. 
 * As long as you retain this notice you can do whatever you want with this stuff. 
 * If we meet some day, and you think this stuff is worth it, you can buy us 
 * a beer in return.        Glenn Mohammad/Vo Günal
 * ----------------------------------------------------------------------------
 *
 * $Id: object.cpp, a08-t1 2012/01/17 02:00:00 g_mohammad v_günal Exp $
 */

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
	Vec3d d = r.Dir();
	dir = d - 2 * (d * n) * n;
	
	// --- Here ends your task ---

	return Ray(hit, dir);
}

Ray Object::Refract(Ray r, Vec3d hit, Vec3d n)
{
	Vec3d dir;

	// --- Here starts your task ---

	// Compute refracted ray according to surface normal and ratio kn of
	// refractive indices, i.e. kn = n2/n1. Consider the direction the ray is
	// coming from with respect to the surface normal direction (in one case 
	// there is a transition between a material with index n2 to a material with
	// index n1 and vice versa in the other case). The medium with index n1 is
	// the one in the half space defined by the normal direction.
	Vec3d d = r.Dir();
	dir = (1 / kn) * (d - n * (d * n)) - 
		n * sqrt(1 - (pow(1 / kn, 2) * (1 - pow(d * n, 2))));
	
	// --- Here ends your task ---

	return Ray(hit, dir);
}
