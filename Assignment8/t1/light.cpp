#include "light.h"

//----------------------------------------------------------------------------
//   CONSTRUCTOR / DESTRUCTOR
//----------------------------------------------------------------------------

Light::Light(const Vec3d p)
{
	pos = p;
	Color white(1,1,1);
	ambient = diffuse = specular = white;
	dir.Set(0,0,0);
	cutoff = 360.0;
	exponent = 1;
	kc = 1;
	kl = 1;
	kq = 0.3;
}

Light::Light(const Vec3d p,   const Vec3d d,   const Vec3d amb,
      	     const Vec3d dif, const Vec3d spec,
		     const double kconst, const double klin, const double kquad,
		     const double inten,  const double cut,    const double exp)
{ 
	pos = p;
	dir = d;
	ambient = amb; 
	diffuse = dif; 
	specular = spec;
	kc = kconst; 
	kl = klin; 
	kq = kquad; 
	cutoff = (cut <= 180 || cut == 360) ? cut : 180; // IF 180<CUTOFF<360 CLAMP TO 180; 
	exponent = exp;
}
