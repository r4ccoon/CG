#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "vec3.h"

typedef Vec3d Color;

class Light {

protected:
	Vec3d  pos;         // CENTER POSITION
	Vec3d  ambient;     // AMBIENT LIGHT
	Vec3d  diffuse;     // DIFFUSE LIGHT
	Vec3d  specular;    // SPECULAR LIGHT

	Vec3d  dir;         // SPOTLIGHT DIRECTION
	double cutoff;      // SPOTLIGHT CUTOFF
	double exponent;    // SPOTLIGHT EXPONENT

	double kc;          // CONSTANT ATTENUATION
	double kl;          // LINEAR ATTENUATION
	double kq;          // QUADRATIC ATTENUATION

	double intensity;   // WHITTED STYLE NUMBER??

public:
	// CONSTRUCTOR
	Light(const Vec3d p);
	Light(const Vec3d p,   const Vec3d d,   const Vec3d amb,
		    const Vec3d dif, const Vec3d spec,
				const double kconst, const double klin, const double kquad,
				const double inten,  const double cut,    const double exp);

	// QUERY STATE
	Vec3d Pos()      { return pos; }
	Vec3d Dir()      { return dir; }
	Color Ambient()  { return ambient;  }
	Color Diffuse()  { return diffuse;  }
	Color Specular() { return specular; }
	double Kc()      { return kc;  }
	double Kl()      { return kl;  }
	double Kq()      { return kq;  }

	double Intensity() { return intensity; }
	void Intensity(const double i) { intensity = i; }
};

#endif
